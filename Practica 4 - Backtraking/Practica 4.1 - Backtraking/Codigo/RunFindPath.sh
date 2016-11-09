#!/bin/bash


echo ' ' > data/FP.dat
for((I=9; I<26; I=I+1))
do
	./bin/FP $I >> data/FP.dat 
done
