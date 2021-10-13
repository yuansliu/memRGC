# memrgc

Memrgc is a tool for compression genome sequence. The program is written in C++11 and tested on Red Hat Enterprise Linux 7.5 (64 bit). 

Currently, it does not work on Ubuntu.

## Download & Compile

	git clone https://github.com/yuansliu/memrgc.git
	cd memrgc
	make
## Test

Two fasta files are stored in testData.

	sh runtest.sh

## Usage

	./memrgc <e|d> -m <mode> -r <reference> -t <target> -o <output> [options]

	e	for compression
	d	for decompression
	-m  	mode; 'file' compress a single file; 'genome' compress a genome; 'set' compress a genome set; 'chrset' compress a set of chromosomes
	-r  	reference file or genome
	-t  	target file or genome
	-o  	the output file
	-f  	use to set the file name; each line contain two file names, i.e., the reference and the target
	-n  	the number of threads
	-h  	print help message

## Example

	./memrgc e -m file -r HG38/chr1.fa -t HG17/chr1.fa -o HG17chr1_ref_HG38chr1.memrgc
	./memrgc e -m genome -r HG38 -t HG17 -o HG17_ref_HG38.memrgc
	./memrgc e -m set -r HG38 -t genome50.txt -o genome50_ref_HG38.memrgc
	./memrgc e -m chrset -t filelist.txt -o chrsets.result
	./memrgc d -m file -r HG38/chr1.fa -t HG17chr1_ref_HG38chr1.memrgc -o HG17_chr1_dec.fa
	./memrgc d -m genome -r HG38 -t HG17_ref_HG38.memrgc -o HG17_dec
	./memrgc d -m set -r HG38 -t genome50_ref_HG38.memrgc -o genome50_dec

## Contacts
If any bugs during you run our code, please email to <yyuanshengliu@gmail.com> or <yuanshengliu@hnu.edu.cn>.
