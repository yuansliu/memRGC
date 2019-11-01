ref=$1
tar=$2
result="$tar"_ref_"$ref"
mkdir -p $result
dec="$result"_dec
mkdir -p $dec
# echo $result

# java Utilities ../../HG17/chrY.fa ../../HG18/chrY.fa HG18_ref_HG17/chrY.fa
# java DecompressCG HG17/chr1.fa HG19_ref_HG17/chr1.fa chr1.fa

tmp=$result"/chr1.fa.7z -o"$result" -aos"
./7za e $tmp
java DecompressCG $ref/chr1.fa $result/chr1.fa $dec/chr1.fa
tmp=$result"/chr2.fa.7z -o"$result" -aos"
./7za e $tmp
java DecompressCG $ref/chr2.fa $result/chr2.fa $dec/chr2.fa
tmp=$result"/chr3.fa.7z -o"$result" -aos"
./7za e $tmp
java DecompressCG $ref/chr3.fa $result/chr3.fa $dec/chr3.fa
tmp=$result"/chr4.fa.7z -o"$result" -aos"
./7za e $tmp
java DecompressCG $ref/chr4.fa $result/chr4.fa $dec/chr4.fa
tmp=$result"/chr5.fa.7z -o"$result" -aos"
./7za e $tmp
java DecompressCG $ref/chr5.fa $result/chr5.fa $dec/chr5.fa
tmp=$result"/chr6.fa.7z -o"$result" -aos"
./7za e $tmp
java DecompressCG $ref/chr6.fa $result/chr6.fa $dec/chr6.fa
tmp=$result"/chr7.fa.7z -o"$result" -aos"
./7za e $tmp
java DecompressCG $ref/chr7.fa $result/chr7.fa $dec/chr7.fa
tmp=$result"/chr8.fa.7z -o"$result" -aos"
./7za e $tmp
java DecompressCG $ref/chr8.fa $result/chr8.fa $dec/chr8.fa
tmp=$result"/chr9.fa.7z -o"$result" -aos"
./7za e $tmp
java DecompressCG $ref/chr9.fa $result/chr9.fa $dec/chr9.fa
tmp=$result"/chr10.fa.7z -o"$result" -aos"
./7za e $tmp
java DecompressCG $ref/chr10.fa $result/chr10.fa $dec/chr10.fa
tmp=$result"/chr11.fa.7z -o"$result" -aos"
./7za e $tmp
java DecompressCG $ref/chr11.fa $result/chr11.fa $dec/chr11.fa
tmp=$result"/chr12.fa.7z -o"$result" -aos"
./7za e $tmp
java DecompressCG $ref/chr12.fa $result/chr12.fa $dec/chr12.fa
tmp=$result"/chr13.fa.7z -o"$result" -aos"
./7za e $tmp
java DecompressCG $ref/chr13.fa $result/chr13.fa $dec/chr13.fa
tmp=$result"/chr14.fa.7z -o"$result" -aos"
./7za e $tmp
java DecompressCG $ref/chr14.fa $result/chr14.fa $dec/chr14.fa
tmp=$result"/chr15.fa.7z -o"$result" -aos"
./7za e $tmp
java DecompressCG $ref/chr15.fa $result/chr15.fa $dec/chr15.fa
tmp=$result"/chr16.fa.7z -o"$result" -aos"
./7za e $tmp
java DecompressCG $ref/chr16.fa $result/chr16.fa $dec/chr16.fa
tmp=$result"/chr17.fa.7z -o"$result" -aos"
./7za e $tmp
java DecompressCG $ref/chr17.fa $result/chr17.fa $dec/chr17.fa
tmp=$result"/chr18.fa.7z -o"$result" -aos"
./7za e $tmp
java DecompressCG $ref/chr18.fa $result/chr18.fa $dec/chr18.fa
tmp=$result"/chr19.fa.7z -o"$result" -aos"
./7za e $tmp
java DecompressCG $ref/chr19.fa $result/chr19.fa $dec/chr19.fa
tmp=$result"/chr20.fa.7z -o"$result" -aos"
./7za e $tmp
java DecompressCG $ref/chr20.fa $result/chr20.fa $dec/chr20.fa
tmp=$result"/chr21.fa.7z -o"$result" -aos"
./7za e $tmp
java DecompressCG $ref/chr21.fa $result/chr21.fa $dec/chr21.fa
tmp=$result"/chr22.fa.7z -o"$result" -aos"
./7za e $tmp
java DecompressCG $ref/chr22.fa $result/chr22.fa $dec/chr22.fa
tmp=$result"/chrX.fa.7z -o"$result" -aos"
./7za e $tmp
java DecompressCG $ref/chrX.fa $result/chrX.fa $dec/chrX.fa
tmp=$result"/chrY.fa.7z -o"$result" -aos"
./7za e $tmp
java DecompressCG $ref/chrY.fa $result/chrY.fa $dec/chrY.fa

