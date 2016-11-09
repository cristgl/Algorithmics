#!/bin/bash

make;

for filename in data/*.tsp; do

   bin/MainBB "$filename" > solutions/BranchBound/"${filename#data/}"

done
