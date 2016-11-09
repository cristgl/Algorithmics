BIN = bin
SRC = src
OBJ = obj
INCLUDE = include
COMPILER = -std=c++0x

CXX = g++

all: $(BIN)/VecinoMasCercano $(BIN)/InsercionMinima $(BIN)/tsp $(BIN)/InsercionRadial

VecinoMasCercano: $(BIN)/VecinoMasCercano
	
InsercionMinima: $(BIN)/InsercionMinima

InsercionRadial: $(BIN)/InsercionRadial

tsp: $(BIN)/tsp

$(BIN)/tsp: $(OBJ)/tsp.o
	@$(CXX) -o $(BIN)/tsp $(OBJ)/tsp.o 
	@echo "Compilando TSP..."

$(OBJ)/tsp.o: $(SRC)/tsp.cpp
	@$(CXX) -c -o $(OBJ)/tsp.o $(SRC)/tsp.cpp -I$(INCLUDE)
	@echo "Compilando código objeto TSP..."
	
$(BIN)/InsercionRadial: $(OBJ)/InsercionRadial.o $(OBJ)/Grafo.o
	@$(CXX) -o $(BIN)/InsercionRadial $(OBJ)/InsercionRadial.o $(OBJ)/Grafo.o
	@echo "Compilando algoritmo Greedy del vecino más cercano..."

$(OBJ)/InsercionRadial.o: $(SRC)/InsercionRadial.cpp $(INCLUDE)/Grafo.h
	@$(CXX) -c -o $(OBJ)/InsercionRadial.o $(SRC)/InsercionRadial.cpp -I$(INCLUDE) $(COMPILER)
	@echo "Compilando código objeto del algoritmo Greedy de inserción mínima..."

$(BIN)/VecinoMasCercano: $(OBJ)/VecinoMasCercano.o $(OBJ)/Grafo.o
	@$(CXX) -o $(BIN)/VecinoMasCercano $(OBJ)/VecinoMasCercano.o $(OBJ)/Grafo.o
	@echo "Compilando algoritmo Greedy del vecino más cercano..."

$(BIN)/InsercionMinima: $(OBJ)/InsercionMinima.o $(OBJ)/Grafo.o
	@$(CXX) -o $(BIN)/InsercionMinima $(OBJ)/InsercionMinima.o $(OBJ)/Grafo.o $(COMPILER)
	@echo "Compilando algoritmo Greedy de inserción mínima..."

$(OBJ)/VecinoMasCercano.o: $(SRC)/VecinoMasCercano.cpp $(INCLUDE)/Grafo.h
	@$(CXX) -c -o $(OBJ)/VecinoMasCercano.o $(SRC)/VecinoMasCercano.cpp -I$(INCLUDE)
	@echo "Compilando código objeto del algoritmo Greedy del vecino más cercano..."

$(OBJ)/InsercionMinima.o: $(SRC)/InsercionMinima.cpp $(INCLUDE)/Grafo.h
	@$(CXX) -c -o $(OBJ)/InsercionMinima.o $(SRC)/InsercionMinima.cpp -I$(INCLUDE) $(COMPILER)
	@echo "Compilando código objeto del algoritmo Greedy de inserción mínima..."
	
$(OBJ)/Grafo.o: $(SRC)/Grafo.cpp $(INCLUDE)/Grafo.h
	@$(CXX) -c -o $(OBJ)/Grafo.o $(SRC)/Grafo.cpp -I$(INCLUDE)
	@echo "Compilando código objeto de manejo de grafos..."

clean:
	@echo "Eliminando ejecutables y ficheros objeto..."
	@rm -f $(OBJ)/* $(BIN)/*

DeleteSolutions:
	@echo "Eliminando ficheros solucion..."
	@rm ./solutions/InsercionMinima/*.*
	@rm ./solutions/InsercionRadial/*.*
	@rm ./solutions/VecinoMasCercano/*.*
	@rm ./printable/InsercionMinima/*.*
	@rm ./printable/InsercionRadial/*.*
	@rm ./printable/VecinoMasCercano/*.*
