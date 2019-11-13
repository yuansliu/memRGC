./memrgc e -m file -r testData/ref.fa -t testData/tar.fa -o testData/result
echo "testData/tar.fa is compressed"
./memrgc d -m file -r testData/ref.fa -t testData/result -o testData/dec.fa
echo "testData/result is decompressed"
diffstr="$(diff testData/tar.fa testData/dec.fa)"
if [[ "$diffstr" = "" ]]; then
	echo "The decompressed file is exactly the same with the original file."
else
	echo $diffstr
	echo "Decompression error. The above is the differences."
fi
# echo