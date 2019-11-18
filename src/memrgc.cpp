#include <stdint.h>
#include <stdio.h>
# include <cstdlib>
# include <iostream>
# include <fstream>
# include <ctime>
# include <sys/time.h>
# include <cmath>
# include <vector>
# include <algorithm>
# include <map>
# include <tuple>
# include <queue>
# include <climits>
# include <cstdint>
# include <cstring>
# include <thread>
# include <string>
# include <utility>
# include <unistd.h>
# include <chrono>
# include <unordered_map>
# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>
# include "kvec.h"
# include "libbsc/bsc.h"

using namespace std;

typedef std::tuple<char*, char*, size_t*> Chromosome;
typedef std::unordered_map<std::string, std::vector<uint32_t> > StrMap;
typedef struct { size_t n, m; uint32_t *a; } uint32_v;

typedef struct match_t {
	size_t len;
	char *tarleft;
	uint32_t refleftidx;
	match_t(){}
	match_t(uint32_t _refleftidx, char *_tarleft, size_t _len): refleftidx(_refleftidx), tarleft(_tarleft), len(_len) {}
	friend bool operator < (const match_t &a, const match_t &b) {
		return a.len > b.len;
	}

	friend bool operator == (const match_t &a, const match_t &b) {
		return a.refleftidx == b.refleftidx && a.tarleft == b.tarleft && a.len == b.len;
	}

} match_t;

typedef struct { size_t n, m; match_t *a; } match_v;

Chromosome readChr(string fn, const char paddingChar = 123) {
	// const char terminatorChar = 0;
	// const char paddingChar = 125;
	const char eolChar1 = 10;
	const char eolChar2 = 13;
	const char beginChar = '>';

	ifstream f(fn, std::ios::ate | std::ios::binary);
	size_t N = f.tellg();
	char *buf1 = new char[N + 10];
	if (buf1 == nullptr) {
		cerr << "new `char *buf1` failed.\n";
		exit(1);
	}
	f.seekg(0, std::ios::beg);
	f.read(buf1, N);
	memset(buf1 + N, 0, 10);
	f.close();

	char *gen = buf1, *src = buf1, *dst = buf1;
	char *lastChar = gen + N;

	if (*src != beginChar) {
		cerr << fn << " is an invalid fasta file\n";
		exit(1);
	}

	char *meta_data = new char[1024];
	size_t idx = 0;
	while (*src != eolChar1 && *src != eolChar2 && src != lastChar) { //reading header line
		meta_data[idx] = *src++;
		++idx;
	}
	meta_data[idx] = 0;

	while (*src != eolChar1 && *src != eolChar2) //search for EOL after header
			src++;
	char *startPtr = dst;
	*dst++ = paddingChar;  //padding char at the begin to make indexing matches from 1

	while (1) { //scanning the sequence
		while (*src == eolChar1 || *src == eolChar2) {
			if (src == lastChar)
				break;
			++src;
		}
		if (src == lastChar)
			break;

		uint64_t temp2; //scan 8 bytes at once
		memcpy(&temp2, src, 8);
		while (((~temp2) & 0x4040404040404040) == 0) {
			// temp2 = temp2 & 0xDFDFDFDFDFDFDFDF;
			memcpy(dst, &temp2, 8);
			dst += 8;
			src += 8;
			memcpy(&temp2, src, 8);
		}
		while (((~(*src)) & (char)0x40) == 0) {
			// *dst++ = (*src++) & (char)0xDF;
			*dst++ = (*src++);
		}
	}
	*dst = paddingChar;
	size_t *seqSize = new size_t;
	*seqSize = dst - startPtr;
	memset(dst, paddingChar, N - *seqSize + 1);

	return {meta_data, startPtr, seqSize};
}

inline int getLineLength(string fn) {
	char *buf = new char[1024];
	FILE *fp = fopen(fn.c_str(), "r");
	fgets(buf, 1024, fp);
	// cout << buf;
	fgets(buf, 1024, fp);
	// cout << buf;
	fclose(fp);
	int len = strlen(buf) - 1;
	delete[] buf;
	// cout << "len: " << len << endl;
	return len;
}

inline void deleteChr(Chromosome & r) {
	delete[] (std::get<0>(r));
	delete[] (std::get<1>(r));
	delete[] (std::get<2>(r));
}

inline void toUpperCase(Chromosome *chr) {
	char *src = std::get<1>(*chr) + 1;
	const char paddingChar1 = 123;
	const char paddingChar2 = 125;
	while (true) {
		if (*src == paddingChar1 || *src == paddingChar2) break;
		*src = (*src) & (char)0xDF;
		++ src;
	}
}

inline void addStrMap(StrMap *smap, string bases, uint32_t refidx) {
	StrMap::iterator iter = smap->find(bases);
	if (iter != smap->end()) {
		iter->second.push_back(refidx);
	} else {
		vector<uint32_t> newvec;
		newvec.push_back(refidx);
		pair<StrMap::iterator, bool> res = smap->insert(make_pair(bases, newvec));
		if (!res.second) {
			res.first->second.push_back(refidx);
		}
	}
}

/*inline void delStrMap(StrMap *smap) {
	StrMap::iterator iter = smap->begin();
	vector<uint32_t> empty_vec;
	StrMap empty_smap;
	while (iter != smap->end()) {
		iter->second.swap(empty_vec);
		iter->second.clear();
		++ iter;
	}
	smap->swap(empty_smap);
	smap->clear();
}
*/

inline void delStrMap(StrMap *smap) {
	StrMap::iterator iter = smap->begin();
	// vector<uint32_t> empty_vec;
	// StrMap empty_smap;
	while (iter != smap->end()) {
		// iter->second.swap(empty_vec);
		iter->second.clear();
		++ iter;
	}
	// smap->swap(empty_smap);
	smap->clear();
}

inline void constrctStrMap(Chromosome *chr, StrMap *smap, size_t step, int K) {
	char *gen = std::get<1>(*chr) + 1, *src, *ori = gen;
	uint32_t pos;
	size_t *seqSize = std::get<2>(*chr);
	char *ends = gen + *seqSize - K + 1;
	size_t num = 0;
	int numberOfN;

	gen += step;
	while (gen <= ends) {
		string kmer;
		src = gen;
		gen += step;
		pos = (uint32_t)(src - ori);
		numberOfN = 0;
		for (size_t j = 0; j < K; ++j) {
			if (*src == 0x4E) 
				++numberOfN;
			kmer += (*src ++);
		}
		if (numberOfN <= K - 10) {
			++ num;
			addStrMap(smap, kmer, pos);
		}
	}
	// cout << "number of sampled k-mers from reference: " << num << endl;
}

inline void findMEMs(uint32_t *v, Chromosome *ref, Chromosome *tar, StrMap *smap, match_v *mh, size_t step, size_t minlen, int K) {
	char *targen = std::get<1>(*tar) + 1, *tarsrc, *tarpos, *tarleft, *tarright;
	char *refgen = std::get<1>(*ref) + 1, *tarbeg = targen;
	char *refpos, *refsrc, *refleft, *refright;
	char *frefleft, *ftarleft;
	size_t *tarSeqSize = std::get<2>(*tar);
	size_t *refSeqSize = std::get<2>(*ref);

	char *tarend = targen + *tarSeqSize - 1;
	char *refend = refgen + *refSeqSize - 1;
	size_t len, maxlen;
	char *ends = targen + *tarSeqSize - K + 1;
		
	kv_init(*mh);
	kv_resize(match_t, *mh, 1024);

	match_t topmh;
	int numberOfN;

	targen += step;
	bool isnext;
	while (targen < ends) {
		isnext = true;
		string kmer;
		tarsrc = targen;
		tarpos = tarsrc;
		numberOfN = 0;
		for (size_t j = 0; j < K; ++j) {
			if (v[tarsrc - tarbeg] != 0) {
				isnext = false;
				break;
			}
			if (*tarsrc == 0x4E)
				// || *tarsrc == 0x6e) 
				++numberOfN;
			kmer += (*tarsrc ++);
		}
		
		if (!isnext) {
			// targen = tarsrc;
			// while (v[tarsrc - tarbeg] != 0) {
			// 	++ tarsrc;
			// }
			targen += step;
			continue;
		}

		if (numberOfN > K - 10) {
			// targen = tarsrc;
			// while (*tarsrc == 0x4E || v[tarsrc - tarbeg] != 0) {
			// 	++ tarsrc;
			// }
			targen += step;
			continue;
		}

		targen += step;

		maxlen = 0;
		StrMap::iterator iter = smap->find(kmer);
		if (iter != smap->end()) {
			for (size_t j = 0; j < iter->second.size(); ++j) {
				refpos = refgen + iter->second[j];
				// extend lef and right
				tarleft = tarpos;
				refleft = refpos;
				while ((*tarleft) == (*refleft) && v[tarleft - tarbeg] == 0) {
					-- tarleft, --refleft;
				}
				++ refleft;
				++ tarleft;

				tarright = tarpos;
				refright = refpos;
				while ((*tarright) == (*refright) && v[tarright - tarbeg] == 0) {
					++ tarright;
					++ refright;
				}

				len = refright - refleft;
				if (len > maxlen && len >= minlen) {
					maxlen = len;
					frefleft = refleft;
					ftarleft = tarleft;
				}
			}
		}

		if (maxlen >= minlen) {
			if (mh->n == 0) {
				kv_push(match_t, *mh, match_t(frefleft - refgen, ftarleft, maxlen));
			} else {
				topmh = mh->a[mh->n - 1];
				if (topmh.refleftidx != frefleft - refgen || topmh.tarleft != ftarleft || topmh.len != maxlen) {
					kv_push(match_t, *mh, match_t(frefleft - refgen, ftarleft, maxlen));
				}
			}
		}
	}
}

inline void travelMEMs(Chromosome *tar, uint32_t *v, match_v *mh) {
	char *targen = std::get<1>(*tar) + 1;

	size_t taridx, taridxend;

	for (size_t i = 0; i < mh->n; ++i) {
		if (i == 0 || (!(mh->a[i-1] == mh->a[i]))) {
			match_t tmh = mh->a[i];

			taridx = tmh.tarleft - targen;
			taridxend = taridx + tmh.len;
			bool flag = true;
			while (taridx < taridxend) {
				if (v[taridx] > 0) flag = false;
				++ taridx;
			}

			if (flag) {
				taridx = tmh.tarleft - targen;

				if (v[taridxend] == tmh.refleftidx + 1) {
					-- taridxend;
				}
				if (v[taridx - 1] == tmh.refleftidx + 1) {
					++ taridx;
					++ tmh.refleftidx;
				}

				while (taridx < taridxend) {
					v[taridx] = tmh.refleftidx + 1;
					++ taridx;
				}
			} 
		}
	}
}

inline size_t countMEMBases(Chromosome *tar, uint32_t *v) {
	size_t tarSeqSize = *(std::get<2>(*tar));
	size_t membases = 0;
	for (size_t i = 0; i < tarSeqSize; ++i) {
		if (v[i] > 0) {
			++ membases;
		} 
	}
	return tarSeqSize - membases;
}

inline void MEMsExtend(uint32_t *v, Chromosome *ref, Chromosome *tar) {
	char *targen = std::get<1>(*tar) + 1, *tarsrc, *tarend;
	char *refgen = std::get<1>(*ref) + 1, *refsrc;
	char *tarleft, *tarright, *refleft, *refright;
	char *newtarbeg, *newrefbeg, *newtarend, *newrefend;

	size_t *tarSeqSize = std::get<2>(*tar), tempMatchLength;
	size_t refleftidx, tempidx, idx;
	uint32_t tarSize = *tarSeqSize - 1;
	uint32_t i = 3, beg, end, j;
	int times = 0;
	int mismatchnum = 0;
	bool isleftextend, isrightextend;
	isleftextend = isrightextend = false;

	while (i < tarSize) {
		if (v[i-1] == 0 && v[i-1] != v[i]) {
			isleftextend = true;
		}

		if (isleftextend) {
			isleftextend = false;

			tarsrc = targen + i;
			refsrc = refgen + v[i] - 1;
			-- tarsrc;
			-- refsrc;

			j = i - 1;
			mismatchnum = 0;
			while (j > 0 && mismatchnum < 20 && refsrc > refgen && (*tarsrc) != (*refsrc) && v[j] == 0) {
				-- tarsrc;
				-- refsrc;
				-- j;
				++ mismatchnum;
			}
			// if (mismatchnum == 0) continue;
			tarright = tarsrc;
			tempidx = j;
			while (j > 0 && refsrc > refgen && (*tarsrc) == (*refsrc) && v[j] == 0) {
				-- tarsrc;
				-- refsrc;
				-- j;
			}
			// tarsrc != refsrc
			++ tarsrc;
			++ refsrc;
			tempMatchLength = tarright - tarsrc + 1;
			if (tempMatchLength >= 5) {
				refleftidx = refsrc - refgen + 1;

				if (refleftidx == v[j]) {
					++ tarsrc;
					++ refleftidx;
					++ j;
				}
				++ j;
				while (j <= tempidx) {
					v[j ++] = refleftidx;
				}
			}
		}

		if (v[i-1] != v[i] && v[i] > 0) {
			isrightextend = true;
		}

		if (isrightextend) {
			isrightextend = false;

			beg = i;
			while (i < tarSize && v[beg] == v[i]) { // find the end of a match
				++ i;
			}
			if (i >= tarSize - 5) break;

			if (v[i] > 0) continue; // two close MEM 
			// else v[i] == 0
			end = i - 1;

			tarleft = targen + beg;
			tarright = tarleft + (end - beg + 1);
			refleft = refgen + v[beg] - 1;
			refright = refleft + (end - beg + 1);

			j = i;
			// right side extension
			tarsrc = tarright;
			refsrc = refright;

			mismatchnum = 0;
			while (j < tarSize && mismatchnum < 20 && (*tarsrc) && (*refsrc) 
				   && (*tarsrc) != (*refsrc) && v[j] == 0) {
				++ tarsrc;
				++ refsrc;
				++ j;
				++ mismatchnum;

			}
			if (mismatchnum == 0) continue;

			newtarbeg = tarsrc;
			newrefbeg = refsrc;
			idx = tempidx = j;

			while (j < tarSize && (*tarsrc) && (*refsrc) && (*tarsrc) == (*refsrc) && v[j] == 0) {
				++ tarsrc;
				++ refsrc;
				++ j;
			}
			tempMatchLength = refsrc - newrefbeg;

			if (tempMatchLength >= 5) {
				refleftidx = newrefbeg - refgen + 1;

				if (refleftidx == v[j]) {
					-- j;
				}

				while (tempidx < j) {
					v[tempidx ++] = refleftidx;
				}
				++ times;
			}
		}
		++ i;
	}
}

// ref and tar are UpperCase seqs
inline void getLowerCases(Chromosome *tar, string &eBuffer) {
	const char paddingChar = 125;
	uint32_v low;
	kv_init(low);
	kv_resize(uint32_t, low, 1024);

	char *gen = std::get<1>(*tar);
	char *src = gen + 1;
	uint32_t len;
	while (true) {
		if (*src == paddingChar) break;

		len = 0;
		while (*src != paddingChar) {
			if (isupper(*src)) {
			// if (islower(*src)) {
				++ len;
				// *src = toupper(*src);
			} else { // islower
				break;
			}
			++ src;
		}
		kv_push(uint32_t, low, len);

		len = 0;
		while (*src != paddingChar) {
			if (islower(*src)) {
				// cout << *src << endl;
				*src = (*src) & (char)0xDF;
				// cout << *src << endl;
				// cout << "-----" << endl;
				++ len;
			} else {
				break;
			}
			++ src;
		}
		kv_push(uint32_t, low, len);
	}
	// FILE *fp = fopen("lowcase.txt", "w");
	// fprintf(fp, "low.size(): %lu\n", low.n);
	eBuffer.append(std::to_string(low.n));
	for (size_t i = 0; i < low.n; ++i) {
		eBuffer.append(" " + std::to_string(low.a[i]));
		// fprintf(fp, "%lu\n", low.a[i]);
	}
	eBuffer.append("\n");
	kv_destroy(low);
}

inline void encodeByUpperCases(Chromosome *ref, Chromosome *tar, uint32_t *v, string &eBuffer) {
	char *targen = std::get<1>(*tar) + 1, *tarsrc, *tarend;
	char *refgen = std::get<1>(*ref) + 1, *refsrc;
	size_t *tarSeqSize = std::get<2>(*tar);
	*tarSeqSize = *tarSeqSize - 1;
	uint32_t ctmp;

	// FILE *fp = fopen("encode.txt.new", "w");

	size_t i = 0;
	uint32_t sglen,len, prepos = 0, numberOfN;
	uint32_v sgv;
	uint32_t mismatchlen = 0, previousmismatchlen;
	// bool ispreprint;
	while (i < *tarSeqSize) {
		previousmismatchlen = 0;
		if (v[i] == 0) {
			tarsrc = targen + i;
			
			while (i < *tarSeqSize && v[i] == 0) {
				string mismatch;

				numberOfN = 0;
				while (i < *tarSeqSize && v[i] == 0) {
					if (*tarsrc == 0x4E) {
						++ numberOfN;
					} else {
						numberOfN = 0;
					}
					if (numberOfN >= 3) {
						mismatch.erase(mismatch.length() - 2);
						i -= 2;
						tarsrc -= 2;
						break;
					}
					mismatch += *tarsrc ++;
					++ i;
				}
				// fprintf(fp, "%s\n", mismatch.c_str());
				if (mismatch.length() > 0) {
					eBuffer.append(mismatch + "\n");
					previousmismatchlen = mismatch.length();
				}

				if (numberOfN >= 3) { // a string `N'
					numberOfN = 0;
					while (i < *tarSeqSize && v[i] == 0 && *tarsrc == 0x4E) {
						++ numberOfN;
						++ i;
						++ tarsrc;
					}
					eBuffer.append("N" + to_string(numberOfN) + "\n");
					previousmismatchlen = numberOfN;
				}
			}
			// mismatchlen += mismatch.length();
		}

		if (i < *tarSeqSize) { // a match
			tarsrc = targen + i;
			refsrc = refgen + v[i] - 1;
			ctmp = v[i];
			len = 0;
			while (i < *tarSeqSize && v[i] == ctmp) {
				++ len;
				++ i;
			}
			tarend = targen + i;
			kv_init(sgv);
			while (tarsrc < tarend) {
				sglen = 0;
				while (tarsrc < tarend && (*tarsrc) == (*refsrc)) { // exactly match
					++ sglen;
					++ tarsrc;
					++ refsrc;
				}
				kv_push(uint32_t, sgv, sglen);
				sglen = 0;
				while (tarsrc < tarend && (*tarsrc) != (*refsrc)) { // unmatched due to case-sensitive
					++ sglen;
					++ tarsrc;
					++ refsrc;
				}
				if (sglen > 0) {
					kv_push(uint32_t, sgv, sglen);
				}
			}
			// fprintf(fp, "%lu %lu\n", ctmp - refgen - prepos, len);
			
			-- ctmp;
			if (ctmp >= prepos) {
				if (previousmismatchlen != 0 && ctmp - prepos == previousmismatchlen) {
					// fprintf(fp, " "); //do nothing
					eBuffer.append(" ");
				} else {
					// fprintf(fp, "%lu %lu\n", ctmp - refgen - prepos, len);
					// fprintf(fp, "%u", ctmp - prepos);
					eBuffer.append(std::to_string(ctmp - prepos));
				}
				// fprintf(fp, "%u", ctmp - prepos);
			} else {
				// fprintf(fp, " %u", prepos - ctmp);
				eBuffer.append(" " + std::to_string(prepos - ctmp));
			}
			prepos = ctmp + len;

			// fprintf(fp, " %u\n", len);
			eBuffer.append(" " + std::to_string(len) + "\n");

			/*for (size_t j = 0; j < sgv.n; ++j) {
				// if (ispreprint) fprintf(fp, " ");
				fprintf(fp, " %u", sgv.a[j]);
				// ispreprint = true;
			}
			fprintf(fp, "\n");*/

			kv_destroy(sgv);
			// fprintf(stderr, "%lu %lu\n", ctmp - refgen, len);
		}
	}
	// fclose(fp);
	// fprintf(stderr, "mismatchlen: %lu\n", mismatchlen);
}

inline void encodeByOriSeq(Chromosome *ref, Chromosome *tar, uint32_t *v, string &eBuffer) {
	char *targen = std::get<1>(*tar) + 1, *tarsrc, *tarend;
	char *refgen = std::get<1>(*ref) + 1, *refsrc;
	size_t *tarSeqSize = std::get<2>(*tar);
	*tarSeqSize = *tarSeqSize - 1;
	uint32_t ctmp;

	size_t i = 0;
	uint32_t sglen,len, prepos = 0, numOfN, numOfn;
	uint32_v sgv;
	uint32_t mismatchlen = 0, previousmismatchlen;
	// bool ispreprint;
	while (i < *tarSeqSize) {
		previousmismatchlen = 0;
		if (v[i] == 0) {
			tarsrc = targen + i;

			while (i < *tarSeqSize && v[i] == 0) {
				string mismatch;

				numOfN = 0;
				numOfn = 0;
				while (i < *tarSeqSize && v[i] == 0) {
					if (*tarsrc == 0x4E) {
						++ numOfN;
						numOfn = 0;
					} else 
					if (*tarsrc == 0x6e) {
						++ numOfn;
						numOfN = 0;
					} else {
						numOfN = 0;
						numOfn = 0;
					}

					if (numOfN >= 3 || numOfn >= 3) {
						mismatch.erase(mismatch.length() - 2);
						i -= 2;
						tarsrc -= 2;
						break;
					}

					mismatch += *tarsrc ++;
					++ i;
				}
				// fprintf(fp, "%s\n", mismatch.c_str());

				if (mismatch.length() > 0) {
					eBuffer.append(mismatch + "\n");
					previousmismatchlen = mismatch.length();
				}

				if (numOfN >= 3) { // a string `N'
					numOfN = 0;
					while (i < *tarSeqSize && v[i] == 0 && *tarsrc == 0x4E) {
						++ numOfN;
						++ i;
						++ tarsrc;
					}
					eBuffer.append("N" + to_string(numOfN) + "\n");
					previousmismatchlen = numOfN;
				}

				if (numOfn >= 3) { // a string `N'
					numOfn = 0;
					while (i < *tarSeqSize && v[i] == 0 && *tarsrc == 0x6E) {
						++ numOfn;
						++ i;
						++ tarsrc;
					}
					eBuffer.append("n" + to_string(numOfn) + "\n");
					previousmismatchlen = numOfn;
				}
				// mismatchlen += mismatch.length();
			}
		}

		if (i < *tarSeqSize) { // a match
			tarsrc = targen + i;
			refsrc = refgen + v[i] - 1;
			ctmp = v[i];
			len = 0;
			while (i < *tarSeqSize && v[i] == ctmp) {
				++ len;
				++ i;
			}
			tarend = targen + i;
			kv_init(sgv);
			while (tarsrc < tarend) {
				sglen = 0;
				while (tarsrc < tarend && (*tarsrc) == (*refsrc)) { // exactly match
					++ sglen;
					++ tarsrc;
					++ refsrc;
				}
				kv_push(uint32_t, sgv, sglen);
				sglen = 0;
				while (tarsrc < tarend && (*tarsrc) != (*refsrc)) { // unmatched due to case-sensitive
					++ sglen;
					++ tarsrc;
					++ refsrc;
				}
				if (sglen > 0) {
					kv_push(uint32_t, sgv, sglen);
				}
			}
			// fprintf(fp, "%lu %lu\n", ctmp - refgen - prepos, len);
			
			-- ctmp;
			if (ctmp >= prepos) {
				if (previousmismatchlen != 0 && ctmp - prepos == previousmismatchlen) {
					// fprintf(fp, " "); //do nothing
					eBuffer.append(" ");
				} else {
					// fprintf(fp, "%lu %lu\n", ctmp - refgen - prepos, len);
					// fprintf(fp, "%u", ctmp - prepos);
					eBuffer.append(std::to_string(ctmp - prepos));
				}
				// fprintf(fp, "%u", ctmp - prepos);
			} else {
				// fprintf(fp, " %u", prepos - ctmp);
				eBuffer.append(" " + std::to_string(prepos - ctmp));
			}
			prepos = ctmp + len;

			// fprintf(fp, " %u\n", len);
			// eBuffer.append(" " + std::to_string(len) + "\n");

			for (size_t j = 0; j < sgv.n; ++j) {
				// if (ispreprint) fprintf(fp, " ");
				// fprintf(fp, " %u", sgv.a[j]);
				eBuffer.append(" " + std::to_string(sgv.a[j]));
				// ispreprint = true;
			}
			// fprintf(fp, "\n");
			eBuffer.append("\n");

			kv_destroy(sgv);
			// fprintf(stderr, "%lu %lu\n", ctmp - refgen, len);
		}
	}
	// fclose(fp);
	// fprintf(stderr, "mismatchlen: %lu\n", mismatchlen);
}

void compressChr(string reffn, string tarfn, string objfn) {
	std::ofstream f;
	f.open(objfn);
	if (f.fail()) {
		fprintf(stderr, "The output file '%s' can not be created when '%s' as reference and '%s' as target. IGNORED!\n", objfn.c_str(), reffn.c_str(), tarfn.c_str());
		return;
	}
	f.close();
	int K;

	Chromosome ref = readChr(reffn, 123);

	Chromosome tar = readChr(tarfn, 125);

	size_t refSeqSize = *(std::get<2>(ref));
	size_t tarSeqSize = *(std::get<2>(tar));

	char *refgen = std::get<1>(ref) + 1;
	char *targen = std::get<1>(tar) + 1;

	if (refSeqSize == tarSeqSize && memcmp((void*)refgen, (void*)targen, refSeqSize - 1) == 0) {
		// cout << "The same\n";
		string comstr;
		comstr.reserve((1<<8));
		if (strcmp(std::get<0>(tar), std::get<0>(ref)) == 0) {
			comstr.append("0\n"); // meta data is the same
		} else 
			comstr.append(std::string(std::get<0>(tar)) + "\n");

		int lineLength = getLineLength(tarfn);	
		if (lineLength == getLineLength(reffn)) {
			comstr.append("0\n");
		} else 
			comstr.append(to_string(lineLength) + "\n");
		comstr.append("3\n");

		std::ofstream fres;
		fres.open(objfn);
		fres << comstr;
		fres.close();
		return;
	}

	toUpperCase(&ref);
	string upperCaseString;
	upperCaseString.reserve((1<<16));

	getLowerCases(&tar, upperCaseString); // also changed to uppercase

	uint32_t *v = new uint32_t[tarSeqSize + 100];
	memset(v, 0, sizeof(uint32_t)*(tarSeqSize + 100));

	/////////////////////////////////////////////
	StrMap smap;
	match_v mh;
	size_t step;

	// 134217728
	if (tarSeqSize > (1UL<<27) || (*(std::get<2>(ref)) > (1UL<<27))) {
		K = 90;
		step = 1000;
		// first find very long matches 
		constrctStrMap(&ref, &smap, step, K);

		findMEMs(v, &ref, &tar, &smap, &mh, 999, 999*step + K - 1, K); //10149
		sort(mh.a, mh.a + mh.n);
		travelMEMs(&tar, v, &mh);
		kv_destroy(mh);
		MEMsExtend(v, &ref, &tar);

		findMEMs(v, &ref, &tar, &smap, &mh, 499, 499*1000 + K - 1, K); // 499089
		sort(mh.a, mh.a + mh.n);
		travelMEMs(&tar, v, &mh);
		kv_destroy(mh);
		MEMsExtend(v, &ref, &tar);

		findMEMs(v, &ref, &tar, &smap, &mh, 49, 49*step + K - 1, K); // 49089
		sort(mh.a, mh.a + mh.n);
		travelMEMs(&tar, v, &mh);
		kv_destroy(mh);
		MEMsExtend(v, &ref, &tar);

		// smap.clear();
		delStrMap(&smap);	
	} else 
	if (tarSeqSize > (1UL<<21)) {
		K = 90;
		step = 500;
		// first find very long matches 
		constrctStrMap(&ref, &smap, step, K);

		findMEMs(v, &ref, &tar, &smap, &mh, 499, 499*step + K - 1, K); //10149
		sort(mh.a, mh.a + mh.n);
		travelMEMs(&tar, v, &mh);
		kv_destroy(mh);
		MEMsExtend(v, &ref, &tar);

		findMEMs(v, &ref, &tar, &smap, &mh, 49, 49*step + K - 1, K); // 499089
		sort(mh.a, mh.a + mh.n);
		travelMEMs(&tar, v, &mh);
		kv_destroy(mh);
		MEMsExtend(v, &ref, &tar);

		findMEMs(v, &ref, &tar, &smap, &mh, 9, 9*step + K - 1, K); // 49089
		sort(mh.a, mh.a + mh.n);
		travelMEMs(&tar, v, &mh);
		kv_destroy(mh);
		MEMsExtend(v, &ref, &tar);

		delStrMap(&smap);
	}
	
	// cout << "tarSeqSize: " << tarSeqSize << endl;
	// cout << "smap.size(): " << smap.size() << endl;
	// #ifdef false
	if (tarSeqSize > (1UL<<21)) {
		do {
			// 2^14 = 16384
			if (countMEMBases(&tar, v) < (1UL<<14)) break;
			K = 30; ///????
			step = 51;
			constrctStrMap(&ref, &smap, step, K);

			findMEMs(v, &ref, &tar, &smap, &mh, 49, 49*step + K - 1, K); // 2528
			sort(mh.a, mh.a + mh.n);
			travelMEMs(&tar, v, &mh);
			kv_destroy(mh);
			MEMsExtend(v, &ref, &tar);

			if (countMEMBases(&tar, v) < (1UL<<14)) break;

			findMEMs(v, &ref, &tar, &smap, &mh, 16, 16*step + K - 1, K); // 845
			sort(mh.a, mh.a + mh.n);
			travelMEMs(&tar, v, &mh);
			kv_destroy(mh);
			MEMsExtend(v, &ref, &tar);

			if (countMEMBases(&tar, v) < (1UL<<14)) break;

			findMEMs(v, &ref, &tar, &smap, &mh, 7, 7*step + K - 1, K); // 386
			sort(mh.a, mh.a + mh.n);
			travelMEMs(&tar, v, &mh);
			kv_destroy(mh);
			MEMsExtend(v, &ref, &tar);

			if (countMEMBases(&tar, v) < (1UL<<14)) break;

			findMEMs(v, &ref, &tar, &smap, &mh, 1, 1*step + K - 1, K); // 80
			sort(mh.a, mh.a + mh.n);
			travelMEMs(&tar, v, &mh);
			kv_destroy(mh);
			MEMsExtend(v, &ref, &tar);

			delStrMap(&smap);
		} while(0);
	} else {
		K = 30; ///????
		step = 51;
		constrctStrMap(&ref, &smap, step, K);

		findMEMs(v, &ref, &tar, &smap, &mh, 40, 40*step + K - 1, K); // 2528
		sort(mh.a, mh.a + mh.n);
		// cout << "mh.n: " << mh.n << endl;
		travelMEMs(&tar, v, &mh);
		kv_destroy(mh);
		// MEMsExtend(v, &ref, &tar);

		findMEMs(v, &ref, &tar, &smap, &mh, 13, 13*step + K - 1, K); // 845
		sort(mh.a, mh.a + mh.n);
		// cout << "mh.n: " << mh.n << endl;
		travelMEMs(&tar, v, &mh);
		kv_destroy(mh);
		// MEMsExtend(v, &ref, &tar);

		findMEMs(v, &ref, &tar, &smap, &mh, 1, 1*step + K - 1, K); // 845
		sort(mh.a, mh.a + mh.n);
		// cout << "mh.n: " << mh.n << endl;
		travelMEMs(&tar, v, &mh);
		kv_destroy(mh);
		MEMsExtend(v, &ref, &tar);

		delStrMap(&smap);

		K = 20; ///????
		step = 7;
		constrctStrMap(&ref, &smap, step, K);

		findMEMs(v, &ref, &tar, &smap, &mh, 5, 5*step + K - 1, K); // 386
		sort(mh.a, mh.a + mh.n);
		// cout << "mh.n: " << mh.n << endl;
		travelMEMs(&tar, v, &mh);
		kv_destroy(mh);
		// MEMsExtend(v, &ref, &tar);

		findMEMs(v, &ref, &tar, &smap, &mh, 1, 1*step + K - 1, K); // 386
		sort(mh.a, mh.a + mh.n);
		// cout << "mh.n: " << mh.n << endl;
		travelMEMs(&tar, v, &mh);
		kv_destroy(mh);
		// MEMsExtend(v, &ref, &tar);

		delStrMap(&smap);
	}


	// 262144
	size_t cntbases = countMEMBases(&tar, v);
	// if (cntbases >= (1UL<<18) || (*std::get<2>(tar)) < (1Ul<<26)) {
	if (cntbases >= (1UL<<18) || (*std::get<2>(tar)) < 50000000) {
		K = 20;
		step = 35;
		
		// if ((*std::get<2>(tar)) < (1Ul<<26)) {
		if ((*std::get<2>(tar)) < 50000000) {
			K = 15;
			step = 5;
		}

		// if (tarSeqSize <= (1UL << 21)) {
		// 	K = 15, step = 5;
		// }
		// cout << "K: " << K << "; step: " << step << endl;

		constrctStrMap(&ref, &smap, step, K);

		findMEMs(v, &ref, &tar, &smap, &mh, 1, 1*step + K - 1, K); // 54
		// cout << "mh.n: " << mh.n << endl;
		sort(mh.a, mh.a + mh.n);
		travelMEMs(&tar, v, &mh);
		kv_destroy(mh);
		MEMsExtend(v, &ref, &tar);

		delStrMap(&smap);

	}

	string e0;
	e0.reserve((1UL<<22));
	encodeByUpperCases(&ref, &tar, v, e0);

	deleteChr(ref);
	deleteChr(tar);

	ref = readChr(reffn, 123);
	tar = readChr(tarfn, 125);

	int lineLength = getLineLength(tarfn);
	
	string comstr;
	comstr.reserve((1<<14));

	if (strcmp(std::get<0>(tar), std::get<0>(ref)) == 0) {
		// cout << "meta data is the same\n";
		comstr.append("0\n"); // meta data is the same
	} else 
		comstr.append(std::string(std::get<0>(tar)) + "\n");
	// cout << "comstr: " << comstr << endl;

	string e1;
	e1.reserve((1UL<<22));
	encodeByOriSeq(&ref, &tar, v, e1);

	std::ofstream fres;
	fres.open(objfn);

	if (lineLength == getLineLength(reffn)) {
		comstr.append("0\n");
	} else 
		comstr.append(to_string(lineLength) + "\n");
	// cout << "lineLength: " << lineLength << endl;

	if (upperCaseString.size() + e0.size() < e1.size()) { 
		// cout << "first method\n";
		comstr.append("0\n");
		fres << comstr << upperCaseString << e0;
	} else { // new method
		// cout << "second method\n";
		comstr.append("1\n");
		fres << comstr << e1;
	}
	fres.close();

	comstr.clear();
	upperCaseString.clear();
	e0.clear();
	e1.clear();

	delete[] v;
	deleteChr(ref);
	deleteChr(tar);
	// cout << "-----------------------\n";
	// cout << "Time of total = " << allstopwatch.stop() << std::endl;
}

int decompressChr(string reffn, string tarfn, string objfn) {
	const char eolChar1 = 10;
	const char eolChar2 = 13;

	Chromosome ref = readChr(reffn, 123);
	const size_t maxnum = 1UL<<28;
	char *tarseq = new char[maxnum], *tarpos = tarseq;
	char *line = new char[maxnum], *tc;

	char *refgen = std::get<1>(ref) + 1, *refpos, *lineend;
	uint32_t prepos = 0, curpos, len, totlen, premismatchlen = 0;
	FILE *fpout = fopen(objfn.c_str(), "w");

	FILE *fp = fopen(tarfn.c_str(), "r");

	fgets(line, maxnum, fp);
	if (line[0] == '0') {
		fprintf(fpout, "%s\n", std::get<0>(ref));
	} else 
		fprintf(fpout, "%s", line);
	// cout << "line: " << line << endl;

	int lineLength, method;
	fscanf(fp, "%d", &lineLength);
	if (lineLength == 0) {
		lineLength = getLineLength(reffn);
	}
	// cout << "lineLength: " << lineLength << endl;
	fscanf(fp, "%d", &method);
	// cout << "method: " << method << endl;

	uint32_t tmp;

	if (method == 0) {
		uint32_v low;
		kv_init(low);
		kv_resize(uint32_t, low, 1024);

		uint32_t num;
		fscanf(fp, "%u", &num);
		for (uint32_t i = 0; i < num; ++i) {
			fscanf(fp, "%u", &tmp);
			kv_push(uint32_t, low, tmp);
		}

		uint32_t numOfN;
		toUpperCase(&ref);
		while (fgets(line, maxnum, fp) != NULL) {
			// fprintf(stderr, "%s\n", line);
			if (line[0] == eolChar1 || line[0] == eolChar2) continue;
			if (line[0] > 0x40) { // mismatch string
				tc = line;
				if (tc[0] == 'N' && tc[1] <= 0x39 && tc[1] >= 0x30) {
					++ tc;
					sscanf(tc, "%u", &numOfN);
					for (uint32_t w = 0; w < numOfN; ++w) {
						*tarpos = 0x4E;
						++ tarpos;
					}
					premismatchlen = numOfN;
				} else {
					premismatchlen = strlen(line) - 1;
					lineend = line + premismatchlen;
					while (tc < lineend) {
						// *tarpos ++ = *tc ++;
						*tarpos = *tc;
						++ tarpos;
						++ tc;
					}
				}
			} else {
				tc = line;
				// if (line[0] == 0x30 && line[1] != 0x20) { // line[0] == '0' && line[1] != ' '
				if (line[0] == 0x20 && line[1] != 0x20) { // line[0] == '0' && line[1] != ' '
					++ tc;
					sscanf(tc, "%u", &curpos);
					curpos = prepos - curpos;
				} else {
					if (line[0] == ' ') {
						curpos = premismatchlen;
					} else {
						sscanf(tc, "%u", &curpos);
					}
					curpos += prepos;
				}
				++ tc;
				while (*tc != eolChar1 && *tc != eolChar2 && *tc && *tc != 0x20) {
					++ tc;
				}
				totlen = 0;
				refpos = refgen + curpos;

				sscanf(tc, "%u", &len);
				for (size_t i = 0; i < len; ++i) {
					*tarpos = *refpos;
					++ tarpos;
					++ refpos;
				}
				// cout << curpos << ":" << len << endl;
				prepos = curpos + len;
				premismatchlen = 0;
			}
			*tarpos = '\0';
			// cout << tarseq << endl;

		}
		*tarpos = '\0';

		tarpos = tarseq;
		for (uint32_t i = 1; i < num; i += 2) {
			tarpos += low.a[i-1];
			for (uint32_t j = 0; j < low.a[i]; ++j) {
				*tarpos = (*tarpos) | (char)0x20; // to lowercase
				++ tarpos;
			}
		}
	} else 
	if (method == 1) {
		uint32_t numOfN;
		while (fgets(line, maxnum, fp) != NULL) {
			// fprintf(stderr, "%s\n", line);
			if (line[0] == eolChar1 || line[0] == eolChar2) continue;
			if (line[0] > 0x40) { // mismatch string
				tc = line;
				if ((tc[0] == 0x4E || tc[0] == 0x6E) && tc[1] <= 0x39 && tc[1] >= 0x30) {
					++ tc;
					sscanf(tc, "%u", &numOfN);
					for (uint32_t w = 0; w < numOfN; ++w) {
						*tarpos = line[0];
						++ tarpos;
					}
					premismatchlen = numOfN;
				} else {
					premismatchlen = strlen(line) - 1;
					lineend = line + premismatchlen;
					while (tc < lineend) {
						// *tarpos ++ = *tc ++;
						*tarpos = *tc;
						++ tarpos;
						++ tc;
					}
				}
			} else {
				tc = line;
				// if (line[0] == 0x30 && line[1] != 0x20) { // line[0] == '0' && line[1] != ' '
				if (line[0] == 0x20 && line[1] != 0x20) { // line[0] == '0' && line[1] != ' '
					++ tc;
					sscanf(tc, "%u", &curpos);
					curpos = prepos - curpos;
				} else {
					if (line[0] == ' ') {
						curpos = premismatchlen;
					} else {
						sscanf(tc, "%u", &curpos);
					}
					curpos += prepos;
				}
				++ tc;
				while (*tc != eolChar1 && *tc != eolChar2 && *tc && *tc != 0x20) {
					++ tc;
				}
				totlen = 0;
				refpos = refgen + curpos;
				while (*tc != eolChar1 && *tc != eolChar2 && *tc) {
					sscanf(tc, "%u", &len); // exactly matches
					totlen += len;
					for (size_t i = 0; i < len; ++i) {
						*tarpos = *refpos;
						++ tarpos;
						++ refpos;
					}

					++ tc;
					while (*tc != eolChar1 && *tc != eolChar2 && *tc && *tc != 0x20) {
						++ tc;
					}
					if (*tc != eolChar1 && *tc != eolChar2 && *tc) {
						sscanf(tc, "%u", &len); // matches
						totlen += len;
						for (size_t i = 0; i < len; ++i) {
							*tarpos = (*refpos) ^ (char)0x20;
							++ tarpos;
							++ refpos;
						}

						++ tc;
						while (*tc != eolChar1 && *tc != eolChar2 && *tc && *tc != 0x20) {
							++ tc;
						}
					}
				}

				// cout << curpos << ":" << len << endl;
				prepos = curpos + totlen;
				premismatchlen = 0;
			}
			*tarpos = '\0';
			// cout << tarseq << endl;

		}
		*tarpos = '\0';
	} else 
	if (method == 3) { // exactly match
		refpos = refgen;
		while (*refpos != 123 && *refpos) {
			*tarpos = *refpos;
			++ refpos;
			++ tarpos;
		}
		*tarpos = '\0';
	}

	fclose(fp);
	deleteChr(ref);

	// fprintf(stderr, "tarlen: %lu\n", strlen(tarseq));
	// fprintf(stderr, "%s\n", tarseq);
	tarpos = tarseq;

	len = 0;
	while (*tarpos) {
		fprintf(fpout, "%c", *tarpos);
		++ len;
		if (len == lineLength) {
			fprintf(fpout, "\n");
			len = 0;
		}
		++ tarpos;
	}
	fprintf(fpout, "\n");
	fclose(fpout);

	delete[] tarseq;
	delete[] line;
}

inline void show_usage(const char* prog) {
	printf("memrgc v0.1, by Yuansheng Liu, November 2019.\n");
	printf("Usage: %s <e|d> -m <mode> -r <reference> -t <target> -o <output> [option parameters]\n", prog);
	// printf("\t options:\n \t\t -f <.fastq> -t <threads>\n\n");
	// printf("-----------\n");
	printf("  -m mode; `file' compress a single file; `genome' compress a genome; `set' compress a set of genome\n");
	printf("  -r reference file or genome\n");
	printf("  -t target file or genome\n");
	printf("  -o the output file\n");
	printf("  -f use to set the file name; each line contain two file names\n");
	printf("  -n the number of threads\n");
	printf("  -h print help message\n");

	printf("\nExample:\n");
	printf("\n");
	printf("./memrgc e -m file -r HG38/chr1.fa -t HG17/chr1.fa -o HG17chr1_ref_HG38chr1.memrgc\n");
	printf("./memrgc e -m genome -r HG38 -t HG17 -o HG17_ref_HG38.memrgc\n");
	printf("./memrgc e -m set -r HG38 -t genome50.txt -o genome50_ref_HG38.memrgc\n");
	printf("./memrgc d -m file -r HG38/chr1.fa -t HG17chr1_ref_HG38chr1.memrgc -o HG17_chr1_dec.fa\n");
	printf("./memrgc d -m genome -r HG38 -t HG17_ref_HG38.memrgc -o HG17_dec\n");
	printf("./memrgc d -m set -r HG38 -t genome50_ref_HG38.memrgc -o genome50_dec\n\n");
}

vector<string> dnlref = {"chr1.fa", "chr2.fa", "chr3.fa", "chr4.fa", //default chr name list
                    "chr5.fa", "chr6.fa", "chr7.fa", "chr8.fa", "chr9.fa", "chr10.fa", 
                    "chr11.fa", "chr12.fa", "chr13.fa", "chr14.fa", "chr15.fa", "chr16.fa", "chr17.fa", 
                    "chr18.fa", "chr19.fa", "chr20.fa", "chr21.fa", "chr22.fa", "chrX.fa", "chrY.fa"};

// vector<string> dnlref = {"chr1.fa", "chr2.fa"};

vector<string> dnltar;
int nthreads = 1;
bool *iscomp, *isdecomp;
int aid, dnlrefsize;
string reffd, tarfd, objfd;
vector<string> tarsets;

bool getList(string &list_file, vector<string> &name_list) {
	FILE *fp = fopen(list_file.c_str(), "r");
	if (fp == NULL) {
		printf("%s open fail!\n", list_file);
		return false;
	}
	char str[1024];
	while (fscanf(fp, "%s", str) != EOF) {
		name_list.push_back(string(str));
	}
	fclose(fp);
	if (name_list.size() == 0) {
		printf("%s is empty!\n", list_file);
		return false;
	}
	return true;
}

void multiTheradsCompressFun() {
	string reffn, tarfn, objfn;
	while (true) {
		int i = __sync_fetch_and_add(&aid, 1);
		if (i >= dnlrefsize) break;
		if (!iscomp[i]) continue;

		reffn = reffd + "/" + dnlref[i];
		tarfn = tarfd + "/" + dnltar[i];
		objfn = objfd + "/" + dnltar[i];
		compressChr(reffn, tarfn, objfn);
	}
}

inline void multiTheradsCompress() {
	aid = 0;
	std::vector<thread> threadVec;
	if (dnlrefsize < nthreads) {
		nthreads = dnlrefsize;
	}
	for (int i = 0; i < nthreads; ++i) {
		threadVec.push_back(std::thread(multiTheradsCompressFun));
	}
	std::for_each(threadVec.begin(), threadVec.end(), [](std::thread & thr) {
		thr.join();
	});
	threadVec.clear();
}

void multiTheradsCompressSetFun() {
	string reffn, tarfn, objfn;
	while (true) {
		int i = __sync_fetch_and_add(&aid, 1);
		if (i >= dnlrefsize) break;
		if (!iscomp[i]) continue;

		reffn = reffd + "/" + dnlref[i];
		tarfn = tarfd + "/" + dnltar[i];
		objfn = objfd + "/" + dnltar[i] + "/" + tarfd;
		compressChr(reffn, tarfn, objfn);
	}
}

inline void multiTheradsCompressSet() {
	aid = 0;
	std::vector<thread> threadVec;
	if (dnlrefsize < nthreads) {
		nthreads = dnlrefsize;
	}
	for (int i = 0; i < nthreads; ++i) {
		threadVec.push_back(std::thread(multiTheradsCompressSetFun));
	}
	std::for_each(threadVec.begin(), threadVec.end(), [](std::thread & thr) {
		thr.join();
	});
	threadVec.clear();
}

static const char alphanum[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
inline std::string generateString(const std::string &chr, int length = 5) {
	srand(time(0));
	string res = chr + "_";
	for (int i = 0; i < length; ++i) {
		res += alphanum[rand() % 62];
	}
	return res;
}

#define MODE (S_IRWXU | S_IRWXG | S_IRWXO)

int compress(int argc, char *argv[]) {
	string mode, reffn, tarfn, objfn, namefn, fobjfn;
	int oc;

	if ((oc = getopt(argc, argv, "m:")) >= 0) {
		mode = optarg;
	} else {
		show_usage(argv[0]);
		return 0;
	}

	std::ifstream f;
	bool isnamefn = false;
	bool isref = false, istar = false, isobj = false;
	if (mode == "file") {
		while ((oc = getopt(argc, argv, "er:t:o:h")) >= 0) {
			switch(oc) {
				case 'e':
					break;
				case 'r':
					reffn = optarg;
					isref = true;
					break;
				case 't':
					tarfn = optarg;
					istar = true;
					break;
				case 'o':
					objfn = optarg;
					isobj = true;
					break;
				case 'h':
					show_usage(argv[0]);
					exit(0);
				case '?':
					fprintf(stderr, "Error parameters!\n");
					exit(1);
			}
		}

		if (!isref || !istar || !isobj) {
			fprintf(stderr, "Required parameters are not provided!\n");
			exit(1);
		}

		f.open(reffn);
		if (f.fail()) {
			fprintf(stderr, "Reference file '%s' does not exist.\n", reffn.c_str());
			exit(1);
		}
		f.close();

		f.open(tarfn);
		if (f.fail()) {
			fprintf(stderr, "Target file '%s' does not exist.\n", tarfn.c_str());
			exit(1);
		}
		f.close();

		std::ofstream fo;
		fo.open(objfn);
		if (fo.fail()) {
			fprintf(stderr, "The output file '%s' can not be created.\n", objfn.c_str());
			exit(1);
		}
		fo.close();

		compressChr(reffn, tarfn, objfn + "tmp");

		memrgc::bsc::BSC_compress((objfn + "tmp").c_str(), objfn.c_str(), 64);

		string cmd = "rm -rf " + objfn + "tmp";	
		system(cmd.c_str());
	} else 
	if (mode == "genome") {
		while ((oc = getopt(argc, argv, "er:t:o:f:n:h")) >= 0) {
			switch(oc) {
				case 'e':
					break;
				case 'r':
					reffd = optarg;
					isref = true;
					break;
				case 't':
					tarfd = optarg;
					istar = true;
					break;
				case 'o':
					fobjfn = optarg;
					isobj = true;
					break;
				case 'f':
					namefn = optarg;
					isnamefn = true;
					break;
				case 'n':
					nthreads = atoi(optarg);
					break;
				case 'h':
					show_usage(argv[0]);
					exit(0);
				case '?':
					fprintf(stderr, "Error parameters!\n");
					exit(1);
			}
		}

		if (!isref || !istar || !isobj) {
			fprintf(stderr, "Required parameters are not provided!\n");
			exit(1);
		}

		// check the folder
		DIR *tmpdir = opendir(reffd.c_str());
		if (NULL == tmpdir) {
			fprintf(stderr, "Reference folder '%s' does not exist.\n", reffd.c_str());
			exit(1);
		}
		closedir(tmpdir);

		tmpdir = opendir(tarfd.c_str());
		if (NULL == tmpdir) {
			fprintf(stderr, "Target folder '%s' does not exist.\n", tarfd.c_str());
			exit(1);
		}
		closedir(tmpdir);

		if (isnamefn) {
			dnlref.clear();
			char *str0 = new char[1024], *str1 = new char[1024];
			FILE *fpn = fopen(namefn.c_str(), "r");
			while (fscanf(fpn, "%s%s", str0, str1) != EOF) {
				dnlref.push_back(str0);
				dnltar.push_back(str1);
			}
			fclose(fpn);
			delete[] str0;
			delete[] str1;
		} else {
			for (size_t i = 0; i < dnlref.size(); ++i) {
				dnltar.push_back(dnlref[i]);
			}
		}
		
		iscomp = new bool[dnlref.size()];
		int numcomp = 0;
		// check all files
		for (size_t i = 0; i < dnlref.size(); ++i) {
			iscomp[i] = true;
			reffn = reffd + "/" + dnlref[i];
			f.open(reffn);
			if (f.fail()) {
				fprintf(stdout, "The reference file '%s' does not exist. This chromosome is ignored.\n", reffn.c_str());
				iscomp[i] = false;
			} else {
				f.close();
			}
			if (iscomp[i]) {
				tarfn = tarfd + "/" + dnltar[i];
				f.open(tarfn);
				if (f.fail()) {
					fprintf(stdout, "The target file '%s' does not exist. This chromosome is ignored.\n", tarfn.c_str());
					iscomp[i] = false;
				} else {
					f.close();
				}
			}
			if (iscomp[i]) ++ numcomp;
		}

		if (numcomp == 0) {
			fprintf(stdout, "No files exist. Compress nothing.\n", tarfn.c_str());
			exit(0);
		}

		tmpdir = opendir(objfn.c_str());
		if (NULL != tmpdir) {
			fprintf(stderr, "The output file '%s' can not be created.\n");
			exit(1);
		}
		closedir(tmpdir);

		std::ofstream fo;
		fo.open(fobjfn);
		if (fo.fail()) {
			fprintf(stderr, "The output file '%s' can not be created.\n", fobjfn.c_str());
			exit(1);
		}
		fo.close();

		objfd = generateString("memrgc", 10);
		// cout << objfd << endl;

		int ret = mkdir(objfd.c_str(), MODE);//创建目录
	    if (ret != 0) {
			fprintf(stderr, "Create template folder failed!\n");
			exit(1);
	    }

	    dnlrefsize = dnlref.size();
		if (nthreads == 1) {
			for (size_t i = 0; i < dnlrefsize; ++i) {
				if (iscomp[i]) {
					// objfn
					reffn = reffd + "/" + dnlref[i];
					tarfn = tarfd + "/" + dnltar[i];
					objfn = objfd + "/" + dnltar[i];
					compressChr(reffn, tarfn, objfn);
				}
			}
		} else {
			multiTheradsCompress();
		}
		
		string tarcmd = "tar -cf " + objfd + ".tar -C " + objfd + " . ";
		system(tarcmd.c_str());

		string cmd = "rm -rf " + objfd;	
		system(cmd.c_str());

		memrgc::bsc::BSC_compress((objfd + ".tar").c_str(), fobjfn.c_str(), 64);

		cmd = "rm -rf " + objfd + ".tar";	
		system(cmd.c_str());
	} 
	if (mode == "set") {
		while ((oc = getopt(argc, argv, "er:t:o:f:n:h")) >= 0) {
			switch(oc) {
				case 'e':
					break;
				case 'r':
					reffd = optarg;
					isref = true;
					break;
				case 't':
					tarfn = optarg;
					istar = true;
					break;
				case 'o':
					fobjfn = optarg;
					isobj = true;
					break;
				case 'f':
					namefn = optarg;
					isnamefn = true;
					break;
				case 'n':
					nthreads = atoi(optarg);
					break;
				case 'h':
					show_usage(argv[0]);
					exit(0);
				case '?':
					fprintf(stderr, "Error parameters!\n");
					exit(1);
			}
		}

		if (!isref || !istar || !isobj) {
			fprintf(stderr, "Required parameters are not provided!\n");
			exit(1);
		}

		// check the folder
		DIR *tmpdir = opendir(reffd.c_str());
		if (NULL == tmpdir) {
			fprintf(stderr, "Reference folder '%s' does not exist.\n", reffd.c_str());
			exit(1);
		}
		closedir(tmpdir);

		if (!getList(tarfn, tarsets)) {
			fprintf(stderr, "Open the target set file '%s' fail (not exist or empty file).\n", tarfn.c_str());
			exit(1);
		}

		if (isnamefn) {
			dnlref.clear();
			char *str0 = new char[1024], *str1 = new char[1024];
			FILE *fpn = fopen(namefn.c_str(), "r");
			while (fscanf(fpn, "%s%s", str0, str1) != EOF) {
				dnlref.push_back(str0);
				dnltar.push_back(str1);
			}
			fclose(fpn);
			delete[] str0;
			delete[] str1;
		} else {
			for (size_t i = 0; i < dnlref.size(); ++i) {
				dnltar.push_back(dnlref[i]);
			}
		}


		tmpdir = opendir(objfn.c_str());
		if (NULL != tmpdir) {
			fprintf(stderr, "The output file '%s' can not be created.\n");
			exit(1);
		}
		closedir(tmpdir);

		std::ofstream fo;
		fo.open(fobjfn);
		if (fo.fail()) {
			fprintf(stderr, "The output file '%s' can not be created.\n", fobjfn.c_str());
			exit(1);
		}
		fo.close();

		objfd = generateString("memrgc", 10);
		// cout << objfd << endl;

		int ret = mkdir(objfd.c_str(), MODE);//
	    if (ret != 0) {
			fprintf(stderr, "Create template folder failed!\n");
			exit(1);
	    }

		for (size_t i = 0; i < dnltar.size(); ++i) {
			int ret = mkdir((objfd + "/" + dnltar[i]).c_str(), MODE);//
		    if (ret != 0) {
				fprintf(stderr, "Create template folder failed!\n");
				exit(1);
		    }
		}

		FILE *fplist = fopen((objfd + "/list").c_str(), "w");

		iscomp = new bool[dnlref.size()];
		for (size_t t = 0; t < tarsets.size(); ++t) {
			tarfd = tarsets[t];
			fprintf(fplist, "%s\n", tarfd.c_str());

			tmpdir = opendir(tarfd.c_str());
			if (NULL == tmpdir) {
				fprintf(stderr, "Target folder '%s' does not exist. It is ignored.\n", tarfd.c_str());
				continue;
			}
			closedir(tmpdir);

			int numcomp = 0;
			// check all files
			for (size_t i = 0; i < dnlref.size(); ++i) {
				iscomp[i] = true;
				reffn = reffd + "/" + dnlref[i];
				f.open(reffn);
				if (f.fail()) {
					fprintf(stdout, "The reference file '%s' does not exist. This chromosome is ignored.\n", reffn.c_str());
					iscomp[i] = false;
				} else {
					f.close();
				}
				if (iscomp[i]) {
					tarfn = tarfd + "/" + dnltar[i];
					f.open(tarfn);
					if (f.fail()) {
						fprintf(stdout, "The target file '%s' does not exist. This chromosome is ignored.\n", tarfn.c_str());
						iscomp[i] = false;
					} else {
						f.close();
					}
				}
				if (iscomp[i]) ++ numcomp;
			}

		    dnlrefsize = dnlref.size();
			if (nthreads == 1) {
				for (size_t i = 0; i < dnlrefsize; ++i) {
					if (iscomp[i]) {
						// objfn
						reffn = reffd + "/" + dnlref[i];
						tarfn = tarfd + "/" + dnltar[i];
						objfn = objfd + "/" + dnltar[i] + "/" + tarfd;
						compressChr(reffn, tarfn, objfn);
					}
				}
			} else {
				multiTheradsCompressSet();
			}
		}
		fclose(fplist);
		
		string tarcmd = "tar -cf " + objfd + ".tar -C " + objfd + " . ";
		system(tarcmd.c_str());

		string cmd = "rm -rf " + objfd;	
		system(cmd.c_str());

		memrgc::bsc::BSC_compress((objfd + ".tar").c_str(), fobjfn.c_str(), 256);

		cmd = "rm -rf " + objfd + ".tar";	
		system(cmd.c_str());
	}
	else {
		fprintf(stderr, "the value of m is not correct. only `file', `genome' and `set' can be set.\n");
		exit(1);
	}
	return 0;
}

int decompress(int argc, char *argv[]) {
	string mode, reffn, tarfn, objfn, namefn, otarfn;
	int oc;

	if ((oc = getopt(argc, argv, "m:")) >= 0) {
		mode = optarg;
	} else {
		show_usage(argv[0]);
		return 0;
	}
 	// cout << "xxxx\n";

	std::ifstream f;
	bool isnamefn = false;
	if (mode == "file") {
		while ((oc = getopt(argc, argv, "dr:t:o:h")) >= 0) {
			switch(oc) {
				case 'd':
					break;
				case 'r':
					reffn = optarg;
					break;
				case 't':
					tarfn = optarg;
					break;
				case 'o':
					objfn = optarg;
					break;
				case 'h':
					show_usage(argv[0]);
					exit(0);
				case '?':
					fprintf(stderr, "Error parameters!\n");
					exit(1);
			}
		}

		f.open(reffn);
		if (f.fail()) {
			fprintf(stderr, "Reference file '%s' does not exist.\n", reffn.c_str());
			exit(1);
		}
		f.close();

		f.open(tarfn);
		if (f.fail()) {
			fprintf(stderr, "Target file '%s' does not exist.\n", tarfn.c_str());
			exit(1);
		}
		f.close();

		std::ofstream fo;
		fo.open(objfn);
		if (fo.fail()) {
			fprintf(stderr, "The output file '%s' can not be created.\n", objfn.c_str());
			exit(1);
		}
		fo.close();

		memrgc::bsc::BSC_decompress(tarfn.c_str(), (tarfn + "tmp").c_str());

		decompressChr(reffn, tarfn + "tmp", objfn);

		string delcmd = "rm -rf " + tarfn + "tmp";
		system(delcmd.c_str());
	} else 
	if (mode == "genome") {
		while ((oc = getopt(argc, argv, "dr:t:o:f:h")) >= 0) {
			switch(oc) {
				case 'd':
					break;
				case 'r':
					reffd = optarg;
					// cout << reffd << endl;
					break;
				case 't':
					otarfn = optarg;
					break;
				case 'o':
					objfd = optarg;
					break;
				case 'f':
					namefn = optarg;
					isnamefn = true;
					break;
				case 'h':
					show_usage(argv[0]);
					exit(0);
				case '?':
					fprintf(stderr, "Error parameters!\n");
					exit(1);
			}
		}
		// check the folder
		DIR *tmpdir = opendir(reffd.c_str());
		if (NULL == tmpdir) {
			fprintf(stderr, "Reference folder '%s' does not exist.\n", reffd.c_str());
			exit(1);
		}
		closedir(tmpdir);

		f.open(otarfn);
		if (f.fail()) {
			fprintf(stderr, "Target file '%s' does not exist.\n", otarfn.c_str());
			exit(1);
		}
		f.close();

		if (isnamefn) {
			dnlref.clear();
			char *str0 = new char[1024], *str1 = new char[1024];
			FILE *fpn = fopen(namefn.c_str(), "r");
			while (fscanf(fpn, "%s%s", str0, str1) != EOF) {
				dnlref.push_back(str0);
				dnltar.push_back(str1);
			}
			fclose(fpn);
			delete[] str0;
			delete[] str1;
		} else {
			for (size_t i = 0; i < dnlref.size(); ++i) {
				dnltar.push_back(dnlref[i]);
			}
		}
		
		isdecomp = new bool[dnlref.size()];
		int numdecomp = 0;
		// check all files
		for (size_t i = 0; i < dnlref.size(); ++i) {
			isdecomp[i] = true;
			reffn = reffd + "/" + dnlref[i];
			f.open(reffn);
			if (f.fail()) {
				fprintf(stdout, "The reference file '%s' does not exist. This chromosome is ignored.\n", reffn.c_str());
				isdecomp[i] = false;
			} else {
				f.close();
			}
			if (isdecomp[i]) ++ numdecomp;
		}

		if (numdecomp == 0) {
			fprintf(stdout, "No files exist. Decompress nothing.\n");
			exit(0);
		}

		int ret = mkdir(objfd.c_str(), 0777);//
	    if (ret != 0) {
			fprintf(stderr, "Create the folder '%s' failed!\n", objfd.c_str());
			exit(1);
	    }

		memrgc::bsc::BSC_decompress(otarfn.c_str(), (otarfn + ".tar").c_str());

		tarfd = generateString("memrgcdec", 10);
		ret = mkdir(tarfd.c_str(), MODE);//创建目录
	    if (ret != 0) {
			fprintf(stderr, "Create template folder failed!\n");
			exit(1);
	    }

	    // cmd = "tar -xf " + string(argv[1]) + " -C " + folder;
	    string tarcmd = "tar -xf " + (otarfn + ".tar") + " -C " + tarfd;
	    system(tarcmd.c_str());

	    numdecomp = 0;
		for (size_t i = 0; i < dnlref.size(); ++i) {
			if (isdecomp[i]) {
				tarfn = tarfd + "/" + dnltar[i];
				f.open(tarfn);
				if (f.fail()) {
					fprintf(stdout, "The compressed file '%s' does not exist. This chromosome is ignored.\n", tarfn.c_str());
					isdecomp[i] = false;
				} else {
					f.close();
				}
			}
			if (isdecomp[i]) ++ numdecomp;
		}

		for (size_t i = 0; i < dnlref.size(); ++i) {
			// objfn
			reffn = reffd + "/" + dnlref[i];
			tarfn = tarfd + "/" + dnltar[i];
			objfn = objfd + "/" + dnltar[i];
			decompressChr(reffn, tarfn, objfn);
		}
		
		string cmd = "rm -rf " + otarfn + ".tar " +  tarfd;	
		system(cmd.c_str());

	} else 
	if (mode == "set") {
		while ((oc = getopt(argc, argv, "dr:t:o:f:h")) >= 0) {
			switch(oc) {
				case 'd':
					break;
				case 'r':
					reffd = optarg;
					break;
				case 't':
					otarfn = optarg;
					break;
				case 'o':
					objfd = optarg;
					break;
				case 'f':
					namefn = optarg;
					isnamefn = true;
					break;
				case 'h':
					show_usage(argv[0]);
					exit(0);
				case '?':
					fprintf(stderr, "Error parameters!\n");
					exit(1);
			}
		}
		// check the folder
		DIR *tmpdir = opendir(reffd.c_str());
		if (NULL == tmpdir) {
			fprintf(stderr, "Reference folder '%s' does not exist.\n", reffd.c_str());
			exit(1);
		}
		closedir(tmpdir);

		f.open(otarfn);
		if (f.fail()) {
			fprintf(stderr, "Target file '%s' does not exist.\n", otarfn.c_str());
			exit(1);
		}
		f.close();

		if (isnamefn) {
			dnlref.clear();
			char *str0 = new char[1024], *str1 = new char[1024];
			FILE *fpn = fopen(namefn.c_str(), "r");
			while (fscanf(fpn, "%s%s", str0, str1) != EOF) {
				dnlref.push_back(str0);
				dnltar.push_back(str1);
			}
			fclose(fpn);
			delete[] str0;
			delete[] str1;
		} else {
			for (size_t i = 0; i < dnlref.size(); ++i) {
				dnltar.push_back(dnlref[i]);
			}
		}
		
		// if (numdecomp == 0) {
		// 	fprintf(stdout, "No files exist. Decompress nothing.\n");
		// 	exit(0);
		// }

		int ret = mkdir(objfd.c_str(), 0777);//
	    if (ret != 0) {
			fprintf(stderr, "Create the folder '%s' failed!\n", objfd.c_str());
			exit(1);
	    }

		memrgc::bsc::BSC_decompress(otarfn.c_str(), (otarfn + ".tar").c_str());

		tarfd = generateString("memrgcdec", 10);
		ret = mkdir(tarfd.c_str(), MODE); //
	    if (ret != 0) {
			fprintf(stderr, "Create template folder failed!\n");
			exit(1);
	    }

	    // cmd = "tar -xf " + string(argv[1]) + " -C " + folder;
	    string tarcmd = "tar -xf " + (otarfn + ".tar") + " -C " + tarfd;
	    system(tarcmd.c_str());

	    vector<string> tarsets;
	    string listfn = tarfd + "/list";
	    getList(listfn, tarsets);

	    isdecomp = new bool[dnlref.size()];
		int numdecomp = 0;
		// check all files
		for (size_t i = 0; i < dnlref.size(); ++i) {
			isdecomp[i] = true;
			reffn = reffd + "/" + dnlref[i];
			f.open(reffn);
			if (f.fail()) {
				fprintf(stdout, "The reference file '%s' does not exist. This chromosome is ignored.\n", reffn.c_str());
				isdecomp[i] = false;
			} else {
				f.close();
			}
			if (isdecomp[i]) ++ numdecomp;
		}
		string objfd1;
		for (size_t t = 0; t < tarsets.size(); ++t) {
			objfd1 = objfd + "/" + tarsets[t];
			ret = mkdir(objfd1.c_str(), MODE); //
		    if (ret != 0) {
				fprintf(stderr, "Create folder failed!\n");
				exit(1);
		    }

			for (size_t i = 0; i < dnlref.size(); ++i) {
				if (isdecomp[i]) {
					tarfn = tarfd + "/" + dnltar[i] + "/" + tarsets[t];
					f.open(tarfn);
					if (f.fail()) {
						fprintf(stdout, "The compressed file '%s' does not exist. This chromosome is ignored.\n", tarfn.c_str());
					} else {
						f.close();
					}
					reffn = reffd + "/" + dnlref[i];
					objfn = objfd1 + "/" + dnltar[i];
					decompressChr(reffn, tarfn, objfn);
				}
			}

		}
		
		string cmd = "rm -rf " + otarfn + ".tar " +  tarfd;	
		system(cmd.c_str());

	} else {
		fprintf(stderr, "the value of m is not correct. only `file', `genome' and `set' can be set.\n");
		exit(1);
	}
	return 0;
}

int main(int argc, char *argv[]) {
	// cout << "argc: " << argc << endl;
	if (argc < 10) {
		show_usage(argv[0]);
		exit(0);
	}

	if (strcmp(argv[1], "e") == 0) {
		// cout << "compress \n";
		compress(argc, argv);
	} else 
	if (strcmp(argv[1], "d") == 0) {
		// cout << "decompress \n";
		decompress(argc, argv);
	} else {
		fprintf(stderr, "Parameter ERROR!\n");
		exit(1);
	}
	return 0;
}

