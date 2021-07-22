#!/usr/bin/env bash
#g++ -std=c++11 main.cpp

#for i in {1..6} ; do
#    ./a.out < testcase/$i.in > testcase/$i.out
#done

#rm a.out

gcc -g -o matrix matrix.c -O0
./matrix

