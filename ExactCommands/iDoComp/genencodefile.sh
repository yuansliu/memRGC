ref=$1
tar=$2
sa="$ref"_sa
result="$tar"_ref_"$ref"_encode.txt
res="$tar"_ref_"$ref"
mkdir -p $res
echo $ref/chr1.fa $tar/chr1.fa $sa/chr1.sa > $result
echo $ref/chr2.fa $tar/chr2.fa $sa/chr2.sa >> $result
echo $ref/chr3.fa $tar/chr3.fa $sa/chr3.sa >> $result
echo $ref/chr4.fa $tar/chr4.fa $sa/chr4.sa >> $result
echo $ref/chr5.fa $tar/chr5.fa $sa/chr5.sa >> $result
echo $ref/chr6.fa $tar/chr6.fa $sa/chr6.sa >> $result
echo $ref/chr7.fa $tar/chr7.fa $sa/chr7.sa >> $result
echo $ref/chr8.fa $tar/chr8.fa $sa/chr8.sa >> $result
echo $ref/chr9.fa $tar/chr9.fa $sa/chr9.sa >> $result
echo $ref/chr10.fa $tar/chr10.fa $sa/chr10.sa >> $result
echo $ref/chr11.fa $tar/chr11.fa $sa/chr11.sa >> $result
echo $ref/chr12.fa $tar/chr12.fa $sa/chr12.sa >> $result
echo $ref/chr13.fa $tar/chr13.fa $sa/chr13.sa >> $result
echo $ref/chr14.fa $tar/chr14.fa $sa/chr14.sa >> $result
echo $ref/chr15.fa $tar/chr15.fa $sa/chr15.sa >> $result
echo $ref/chr16.fa $tar/chr16.fa $sa/chr16.sa >> $result
echo $ref/chr17.fa $tar/chr17.fa $sa/chr17.sa >> $result
echo $ref/chr18.fa $tar/chr18.fa $sa/chr18.sa >> $result
echo $ref/chr19.fa $tar/chr19.fa $sa/chr19.sa >> $result
echo $ref/chr20.fa $tar/chr20.fa $sa/chr20.sa >> $result
echo $ref/chr21.fa $tar/chr21.fa $sa/chr21.sa >> $result
echo $ref/chr22.fa $tar/chr22.fa $sa/chr22.sa >> $result
echo $ref/chrX.fa $tar/chrX.fa $sa/chrX.sa >> $result
echo $ref/chrY.fa $tar/chrY.fa $sa/chrY.sa >> $result
