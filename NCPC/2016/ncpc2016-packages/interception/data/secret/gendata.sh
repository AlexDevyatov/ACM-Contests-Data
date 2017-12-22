#!/bin/bash

SOL=../../submissions/accepted/per.cc

g++ -O2 -std=gnu++0x $SOL
rm -f *.in *.ans *.desc

python gendata.py $1


for f in *.in; do
    echo $f
    time ./a.out < $f > ${f%.in}.ans
done
    
rm a.out
