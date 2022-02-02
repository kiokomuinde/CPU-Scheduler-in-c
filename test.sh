#!/bin/sh
# This is a comment

rm *.txt
make clean
make

./cpu_scheduler results/in.txt sout_sjf.txt SJF
./cpu_scheduler results/in.txt sout_sjf_100.txt SJF 100
./cpu_scheduler results/in.txt sout_srtf.txt SRTF
./cpu_scheduler results/in.txt sout_srtf_100.txt SRTF 100

if diff -w sout_sjf.txt results/correct_sjf.txt; then
    echo Test 1 - Success--------------------SJF--------------------------------Success
else
    echo Test 1 - Fail-----------------------SJF--------------------------------Fail
fi

if diff -w sout_sjf_100.txt results/correct_sjf_100.txt; then
    echo Test 2 - Success--------------------SJF-100----------------------------Success
else
    echo Test 2 - Fail-----------------------SJF-100----------------------------Fail
fi

if diff -w sout_srtf.txt results/correct_srtf.txt; then
    echo Test 3 - Success--------------------SRTF-------------------------------Success
else
    echo Test 3 - Fail-----------------------SRTF-------------------------------Fail
fi

if diff -w sout_srtf_100.txt results/correct_srtf_100.txt; then
    echo Test 4 - Success--------------------SRTF-100---------------------------Success
else
    echo Test 4 - Fail-----------------------SRTF-100---------------------------Fail
fi
