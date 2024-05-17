#!/bin/bash

path=$(realpath $1)

for lab in "$path/lab"*
do
    cd "$lab/latex"
    make
    cp report.pdf "$path/reports/$(basename $lab).pdf"
    make clean
done