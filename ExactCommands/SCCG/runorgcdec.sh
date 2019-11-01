ref=$1
tar=$2
res="$tar"_ref_"$ref"
ztar="$res"/result.7z
echo $ztar
dec="$res"_dec
mkdir -p $dec
java -Xms8192m -Xmx10g ORGD $ref $ztar $dec
