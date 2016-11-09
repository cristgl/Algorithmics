BIN = bin
SRC = src
OBJ = obj
INCLUDE = include
COMPILER = -std=c++0x
OPTIMIZATION = -O2

CXX = g++

all: $(BIN)/MainBB $(BIN)/MainBacktracking

MainBB: $(BIN)/MainBB

MainBacktracking: $(BIN)/MainBacktracking

$(BIN)/MainBB: $(OBJ)/MainBB.o $(OBJ)/Grafo.o $(OBJ)/BranchBound.o
	@$(CXX) -o $(BIN)/MainBB $(OBJ)/MainBB.o $(OBJ)/Grafo.o $(OBJ)/BranchBound.o $(COMPILER) $(OPTIMIZATION)
	@echo "Compilando algoritmo B&B..."

$(BIN)/MainBacktracking: $(OBJ)/MainBacktracking.o $(OBJ)/Grafo.o $(OBJ)/Backtracking.o
	@$(CXX) -o $(BIN)/MainBacktracking $(OBJ)/MainBacktracking.o $(OBJ)/Grafo.o $(OBJ)/Backtracking.o $(COMPILER) $(OPTIMIZATION)
	@echo "Compilando algoritmo B&B..."

$(OBJ)/MainBB.o: $(SRC)/MainBB.cpp $(INCLUDE)/Grafo.h $(INCLUDE)/BranchBound.h
	@$(CXX) -c -o $(OBJ)/MainBB.o $(SRC)/MainBB.cpp -I$(INCLUDE) $(COMPILER) $(OPTIMIZATION)
	@echo "Compilando código objeto del algoritmo B&B..."

$(OBJ)/MainBacktracking.o: $(SRC)/MainBacktracking.cpp $(INCLUDE)/Grafo.h $(INCLUDE)/Backtracking.h
	@$(CXX) -c -o $(OBJ)/MainBacktracking.o $(SRC)/MainBacktracking.cpp -I$(INCLUDE) $(COMPILER) $(OPTIMIZATION)
	@echo "Compilando código objeto del algoritmo Backtracking..."
	
$(OBJ)/Grafo.o : $(SRC)/Grafo.cpp $(INCLUDE)/Grafo.h
	@$(CXX) -c -o $(OBJ)/Grafo.o $(SRC)/Grafo.cpp -I$(INCLUDE) $(COMPILER) $(OPTIMIZATION)
	@echo "Compilando código objeto de manejo de grafos..."
	
$(OBJ)/BranchBound.o : $(SRC)/BranchBound.cpp $(INCLUDE)/BranchBound.h $(INCLUDE)/Grafo.h
	@$(CXX) -c -o $(OBJ)/BranchBound.o $(SRC)/BranchBound.cpp -I$(INCLUDE) $(COMPILER) $(OPTIMIZATION)
	@echo "Compilando código objeto de Branch and Bound..."

$(OBJ)/Backtracking.o : $(SRC)/Backtracking.cpp $(INCLUDE)/Backtracking.h $(INCLUDE)/Grafo.h
	@$(CXX) -c -o $(OBJ)/Backtracking.o $(SRC)/Backtracking.cpp -I$(INCLUDE) $(COMPILER) $(OPTIMIZATION)
	@echo "Compilando código objeto de Backtracking..."

clean:
	@echo "Eliminando ejecutables y ficheros objeto..."
	@rm -f $(OBJ)/* $(BIN)/*
