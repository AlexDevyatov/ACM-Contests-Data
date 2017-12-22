#!/bin/bash

python gendata.py

g++ -std=gnu++0x -O2 ../submissions/accepted/per.cc
for f in secret/*in; do
    ./a.out < $f > ${f%.in}.ans
done
rm a.out
