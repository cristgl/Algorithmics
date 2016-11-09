#!/bin/bash

for filename in data/*.tsp; do

    bin/VecinoMasCercano "$filename" > solutions/VecinoMasCercano/"${filename#data/}"

done 

for filename in solutions/VecinoMasCercano/*.tsp; do 
	bin/tsp data/"${filename#solutions/VecinoMasCercano/}" "$filename" > printable/"${filename#solutions/}"
done
