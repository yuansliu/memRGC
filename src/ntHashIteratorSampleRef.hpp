/* changed by Yuansheng Liu from https://github.com/bcgsc/ntHash/blob/master/ntHashIterator.hpp
 * Add the sampling k-mers, i.e., only calculate the hash values of the sampled k-mers
 * The sampling step is m_step
 * 
 */
/* 
 * Author of ntHashIterator.hpp: Hamid Mohamadi
 * Genome Sciences Centre,
 * British Columbia Cancer Agency
 */
/*
    MIT License

    Copyright (c) 2018 Hamid Mohamadi

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/

#ifndef NTHASH__SAMPLE_REF__ITERATOR_H
#define NTHASH__SAMPLE_REF__ITERATOR_H 1

#include <string>
#include <limits>
#include "nthash.hpp"

/**
 * Iterate over hash values for k-mers in a
 * given DNA sequence.
 *
 * This implementation uses ntHash
 * function to efficiently calculate
 * hash values for successive k-mers.
 */

class ntHashIteratorSampleRef
{

public:

    /**
     * Default constructor. Creates an iterator pointing to
     * the end of the iterator range.
    */
    ntHashIteratorSampleRef():
        m_hVec(NULL),
        m_pos(std::numeric_limits<std::size_t>::max())
    {}

    /**
     * Constructor.
     * @param seq address of DNA sequence to be hashed
     * @param k k-mer size
     * @param h number of hashes
     * @param s sampling step
    */
    // ntHashIteratorSampleRef(const std::string& seq, unsigned h, unsigned k): length of seq
    ntHashIteratorSampleRef(const char *seq, unsigned h, unsigned k, unsigned s, size_t N):
        m_seq(seq), m_seq_length(N), m_h(h), m_k(k), m_hVec(new uint64_t[h]), m_step(s), m_pos(0)
    {   
        last_pos = m_seq_length - m_k + 1; 
        // m_step = m_w - m_L; //119-100=19
        // fprintf(stderr, "m_w: %u\n", m_w); //each time, process a substring of length m_L without non-ATGC.
        if (m_k > m_seq_length) {
            m_pos = std::numeric_limits<std::size_t>::max();
        }
        init();
        // cout << "over init()\n";
    }

    // ntHashIteratorSampleRef(const char *seq, unsigned h, unsigned L, unsigned k, size_t N, uint32_t *_v):
    //     m_seq(seq), m_seq_length(N), m_h(h), m_k(k), m_hVec(new uint64_t[h]), m_L(L), v(_v), m_pos(0)
    // {   
    //     last_pos = m_seq_length - m_k + 1; 
    //     m_w = m_L + m_L - k; // 119 length of substring processed by each time
    //     m_step = m_w - m_L; //119-100=19
    //     // fprintf(stderr, "m_w: %u\n", m_w); //each time, process a substring of length m_L without non-ATGC.
    //     if (m_k > m_seq_length) {
    //         m_pos = std::numeric_limits<std::size_t>::max();
    //     }
    //     init();
    // }

    inline void calcCurPos() {
        int numberOfN;
        // cout << m_pos << endl;
        // cout << m_k << endl;
        while (true) {
            m_pos += m_step;
            
            if (m_pos > last_pos) {
                m_pos = std::numeric_limits<std::size_t>::max();
                return;
            }
            numberOfN = 0;
            for (size_t j = 0; j < m_k; ++j) {
                if (m_seq[m_pos + j] == 0x4E)
                    ++numberOfN;
            }
            if (numberOfN <= m_k - 10) break;
        }
    }

    /** Initialize internal state of iterator */
    inline void init() {
        // while (m_pos<m_seq_length-m_k+1 && !NTMC64(m_seq+m_pos, m_k, m_h, m_fhVal, m_rhVal, locN, m_hVec, m_hStn))
        // while (m_pos<m_seq_length-m_k+1 && !NTM64(m_seq+m_pos, m_k, m_h, m_hVec, locN)) {
        calcCurPos();
        // cout << "m_pos: " << m_pos << endl;
        if (m_pos <= last_pos) {
        //     m_pos = std::numeric_limits<std::size_t>::max();
        // } else {
            #ifdef DEBUG
            unsigned w = 0;
            char *stbuf = (char*)malloc(sizeof(char)*(m_w+1));
            strncpy(stbuf, m_seq + m_pos, w);
            stbuf[w] = '\0';
            fprintf(stderr, "111: %s\n", stbuf);
            // fprintf(stderr, "2222\n");
            // free(stbuf);
            // fprintf(stderr, "22223333\n");
            fprintf(stderr, "m_pos: %u; w: %u;\n", m_pos, w);
            #endif
            // NTM64(m_seq + (m_pos + w - m_L), m_k, m_h, m_hVec);
            // m_pos += m_step;
            NTM64(m_seq + m_pos, m_k, m_h, m_hVec);
        }
		// for (unsigned i = 0; i < m_h; ++i) {
		// 	m_hStnArray[i] = m_hStn;
		// }
        // cout << "over init()\n";
    }

    /** Advance iterator right to the next valid k-mer */
    inline void next()
    {
        // m_pos += m_L - m_k + 1;
        calcCurPos();

        if (m_pos > last_pos) {
            return;
        }
        // cout << "m_pos: " << m_pos << endl;
            //shift w + 1?
        #ifdef DEBUG
        char *stbuf = (char*)malloc(sizeof(char)*(m_w+1));
        strncpy(stbuf, m_seq + m_pos, m_L - 1 + w);
        stbuf[m_L - 1 + w] = '\0';
        fprintf(stderr, "shift w: %u\n", w);
        fprintf(stderr, "222: %s\n", stbuf);
        // free(stbuf);
        #endif

        // if (m_step >= m_k) {
            NTM64(m_seq + m_pos, m_k, m_h, m_hVec);
        // } else {
        //     NTM64(m_seq + (m_pos - 1), m_seq + (m_pos - 1 + m_k), m_k, m_h, m_hVec, m_step);
        // }

        #ifdef DEBUG
        fprintf(stderr, "m_pos: %u\n", m_pos);
        // exit(0);
        #endif
            // NTM64(m_seq + (m_pos + m_k - 1 + w - m_L), m_k, m_h, m_hVec);
    }

    inline size_t pos() const{
    	return m_pos;
    }

    // this hash function is from http://www.amsoftware.narod.ru/algo2.html
    inline uint64_t getHash() {
        // return m_hVec[0];
        const char *str = m_seq + m_pos;
        std::uint64_t hash = m_k;
        for (std::uint32_t j = 0; j < m_k/4; ) {
            std::uint32_t k;
            memcpy(&k, str, 4);
            k += j++;
            hash ^= k;
            hash *= 171717;
            str += 4;
        }
        return hash;
    }
    /** get pointer to hash values for current k-mer */
    inline const uint64_t* operator*() const
    {
        return m_hVec;
    }

    /** test equality with another iterator */
    inline bool operator==(const ntHashIteratorSampleRef& it) const
    {
        return m_pos == it.m_pos;
    }

    /** test inequality with another iterator */
    inline bool operator!=(const ntHashIteratorSampleRef& it) const
    {
        return !(*this == it);
    }

    /** pre-increment operator */
    inline ntHashIteratorSampleRef& operator++()
    {
        next();
        return *this;
    }

    /** iterator pointing to one past last element */
    inline static const ntHashIteratorSampleRef end()
    {
        return ntHashIteratorSampleRef();
    }

    /** destructor */
    ~ntHashIteratorSampleRef() {
        if(m_hVec!=NULL) {
            delete [] m_hVec;
        }
    }

private:

    /** DNA sequence */
    // std::string m_seq;
    const char *m_seq;
    size_t m_seq_length;
    size_t last_pos;

    /** number of hashes */
    unsigned m_h;

    /** k-mer size */
    unsigned m_k;

    unsigned m_step;

    /** hash values */
    uint64_t *m_hVec;
    
    /** position of current k-mer */
    size_t m_pos;
};

#endif
