ref=$1
tar=$2
result="$tar"_ref_"$ref"
mkdir -p $result
# echo $result

# java Utilities ../../HG17/chrY.fa ../../HG18/chrY.fa HG18_ref_HG17/chrY.fa

java Utilities $ref/chr1.fa $tar/chr1.fa $result/chr1.fa
./7za a -t7z $result/chr1.fa.7z $result/chr1.fa -m0=PPMd
java Utilities $ref/chr2.fa $tar/chr2.fa $result/chr2.fa
./7za a -t7z $result/chr2.fa.7z $result/chr2.fa -m0=PPMd
java Utilities $ref/chr3.fa $tar/chr3.fa $result/chr3.fa
./7za a -t7z $result/chr3.fa.7z $result/chr3.fa -m0=PPMd
java Utilities $ref/chr4.fa $tar/chr4.fa $result/chr4.fa
./7za a -t7z $result/chr4.fa.7z $result/chr4.fa -m0=PPMd
java Utilities $ref/chr5.fa $tar/chr5.fa $result/chr5.fa
./7za a -t7z $result/chr5.fa.7z $result/chr5.fa -m0=PPMd
java Utilities $ref/chr6.fa $tar/chr6.fa $result/chr6.fa
./7za a -t7z $result/chr6.fa.7z $result/chr6.fa -m0=PPMd
java Utilities $ref/chr7.fa $tar/chr7.fa $result/chr7.fa
./7za a -t7z $result/chr7.fa.7z $result/chr7.fa -m0=PPMd
java Utilities $ref/chr8.fa $tar/chr8.fa $result/chr8.fa
./7za a -t7z $result/chr8.fa.7z $result/chr8.fa -m0=PPMd
java Utilities $ref/chr9.fa $tar/chr9.fa $result/chr9.fa
./7za a -t7z $result/chr9.fa.7z $result/chr9.fa -m0=PPMd
java Utilities $ref/chr10.fa $tar/chr10.fa $result/chr10.fa
./7za a -t7z $result/chr10.fa.7z $result/chr10.fa -m0=PPMd
java Utilities $ref/chr11.fa $tar/chr11.fa $result/chr11.fa
./7za a -t7z $result/chr11.fa.7z $result/chr11.fa -m0=PPMd
java Utilities $ref/chr12.fa $tar/chr12.fa $result/chr12.fa
./7za a -t7z $result/chr12.fa.7z $result/chr12.fa -m0=PPMd
java Utilities $ref/chr13.fa $tar/chr13.fa $result/chr13.fa
./7za a -t7z $result/chr13.fa.7z $result/chr13.fa -m0=PPMd
java Utilities $ref/chr14.fa $tar/chr14.fa $result/chr14.fa
./7za a -t7z $result/chr14.fa.7z $result/chr14.fa -m0=PPMd
java Utilities $ref/chr15.fa $tar/chr15.fa $result/chr15.fa
./7za a -t7z $result/chr15.fa.7z $result/chr15.fa -m0=PPMd
java Utilities $ref/chr16.fa $tar/chr16.fa $result/chr16.fa
./7za a -t7z $result/chr16.fa.7z $result/chr16.fa -m0=PPMd
java Utilities $ref/chr17.fa $tar/chr17.fa $result/chr17.fa
./7za a -t7z $result/chr17.fa.7z $result/chr17.fa -m0=PPMd
java Utilities $ref/chr18.fa $tar/chr18.fa $result/chr18.fa
./7za a -t7z $result/chr18.fa.7z $result/chr18.fa -m0=PPMd
java Utilities $ref/chr19.fa $tar/chr19.fa $result/chr19.fa
./7za a -t7z $result/chr19.fa.7z $result/chr19.fa -m0=PPMd
java Utilities $ref/chr20.fa $tar/chr20.fa $result/chr20.fa
./7za a -t7z $result/chr20.fa.7z $result/chr20.fa -m0=PPMd
java Utilities $ref/chr21.fa $tar/chr21.fa $result/chr21.fa
./7za a -t7z $result/chr21.fa.7z $result/chr21.fa -m0=PPMd
java Utilities $ref/chr22.fa $tar/chr22.fa $result/chr22.fa
./7za a -t7z $result/chr22.fa.7z $result/chr22.fa -m0=PPMd
java Utilities $ref/chrX.fa $tar/chrX.fa $result/chrX.fa
./7za a -t7z $result/chrX.fa.7z $result/chrX.fa -m0=PPMd
java Utilities $ref/chrY.fa $tar/chrY.fa $result/chrY.fa
./7za a -t7z $result/chrY.fa.7z $result/chrY.fa -m0=PPMd
