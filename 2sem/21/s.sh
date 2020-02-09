#!/usr/bin/env bash
#№15
#file_for_copy length suff

suff=$(find . -type f -name "*$3")

for i in $suff; do
    l=$(wc -m $i | awk '{print $1}')



    while [[ "$2" -gt "$l" ]]; do
        head -c -1 -q $1 >> $i;
        l=$(wc -m $i | awk '{print $1}')


    done


done

