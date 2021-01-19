# !/bin/bash

total=0
for i in *.cpp
do
    nlines=$(wc -l < $i)
    total=$((nlines+total))
done

for i in *.hpp
do
    nlines=$(wc -l < $i)
    total=$((nlines+total))
done

nlines=$(wc -l < makefile)
total=$((nlines+total))

echo $total
exit