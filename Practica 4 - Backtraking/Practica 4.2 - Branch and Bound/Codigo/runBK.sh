#!/bin/bash

make;

for filename in data/*.tsp; do

   bin/MainBacktracking "$filename" > solutions/Backtracking/"${filename#data/}"

done
