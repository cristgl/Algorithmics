#!/bin/bash

echo ' ' > data/FBP.dat
for((I=9; I<23; I=I+1))
do
	./bin/FBP $I >> data/FBP.dat 
done
