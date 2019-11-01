ref=$1
tar=$2
result="$tar"_ref_"$ref"_decode.txt
res="$tar"_ref_"$ref"_dec
mkdir -p $res
echo $ref/chr1.fa $res/chr1.fa > $result
echo $ref/chr2.fa $res/chr2.fa >> $result
echo $ref/chr3.fa $res/chr3.fa >> $result
echo $ref/chr4.fa $res/chr4.fa >> $result
echo $ref/chr5.fa $res/chr5.fa >> $result
echo $ref/chr6.fa $res/chr6.fa >> $result
echo $ref/chr7.fa $res/chr7.fa >> $result
echo $ref/chr8.fa $res/chr8.fa >> $result
echo $ref/chr9.fa $res/chr9.fa >> $result
echo $ref/chr10.fa $res/chr10.fa >> $result
echo $ref/chr11.fa $res/chr11.fa >> $result
echo $ref/chr12.fa $res/chr12.fa >> $result
echo $ref/chr13.fa $res/chr13.fa >> $result
echo $ref/chr14.fa $res/chr14.fa >> $result
echo $ref/chr15.fa $res/chr15.fa >> $result
echo $ref/chr16.fa $res/chr16.fa >> $result
echo $ref/chr17.fa $res/chr17.fa >> $result
echo $ref/chr18.fa $res/chr18.fa >> $result
echo $ref/chr19.fa $res/chr19.fa >> $result
echo $ref/chr20.fa $res/chr20.fa >> $result
echo $ref/chr21.fa $res/chr21.fa >> $result
echo $ref/chr22.fa $res/chr22.fa >> $result
echo $ref/chrX.fa $res/chrX.fa >> $result
echo $ref/chrY.fa $res/chrY.fa >> $result