#!/bin/bash

ls | grep -x "libopencv.*\.so.$1" >> libfile.txt
touch includeLibraries.h


infile=libfile.txt
outfile=includeLibraries.h

echo "#pragma cling add_include_path(\"/usr/local/include/opencv4\")" >> "$outfile"
echo "#pragma cling add_include_path(\"/usr/local/include/python"$2"m\")" >> "$outfile"
echo "#pragma cling load(\"/usr/local/lib/libpython"$2"m.so\")" >> "$outfile"
echo "#pragma cling add_include_path(\"/usr/local/lib/python"$2"/site-packages/numpy/core/include\")" >> "$outfile"

while read line
do
        echo "#pragma cling load(\"/usr/local/lib/$line\")" >> "$outfile"
done < "$infile"
rm -f libfile.txt