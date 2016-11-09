#!/bin/bash

make

echo "Ejecutando NearestNeighbor..."
./RunNearestNeighbor.sh

echo "Ejecutando CheapestInsertion..."
./RunCheapestInsertion.sh

echo "Ejecutando InsercionRadial..."
./RunInsercionRadial.sh

echo "Ejecucion completada"
