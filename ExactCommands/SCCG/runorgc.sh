ref=$1
tar=$2
res="$tar"_ref_"$ref"
mkdir -p $res
# javac ORGC.java
java -Xms8192m -Xmx10g ORGC $ref $tar $res
./7za a $res/result.7z $res/result -m0=PPMd