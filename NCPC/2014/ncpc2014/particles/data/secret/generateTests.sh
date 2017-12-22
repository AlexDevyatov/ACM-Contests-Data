#!/bin/bash

for i in 3 4 5 6 7 8 9; do
    echo "Creating $i";
    ./part_data_generator.e $i >$i.in;
done

for i in `seq 9`; do
    echo "Generating answer to $i";
    time ../../submissions/accepted/part-mipi.e <./$i.in >./$i.ans;
done
