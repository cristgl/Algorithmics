#!/bin/bash

for filename in data/*.tsp; do

    bin/InsercionMinima "$filename" > solutions/InsercionMinima/"${filename#data/}"

done 

for filename in solutions/InsercionMinima/*.tsp; do 
	bin/tsp data/"${filename#solutions/InsercionMinima/}" "$filename" > printable/"${filename#solutions/}"
done
