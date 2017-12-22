#!/bin/bash

for i in `seq 12`; do
    echo "Doing $i";
    ./squ_data_generator.e $i >squ$i.in;
    time ../../submissions/accepted/squ-mipi.e <./squ$i.in >./squ$i.ans;
done