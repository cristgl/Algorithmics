#!/bin/bash

for filename in data/*.tsp; do

    bin/InsercionRadial "$filename" > solutions/InsercionRadial/"${filename#data/}"

done 

for filename in solutions/InsercionRadial/*.tsp; do 
	bin/tsp data/"${filename#solutions/InsercionRadial/}" "$filename" > printable/"${filename#solutions/}"
done
