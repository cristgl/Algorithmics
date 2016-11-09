BIN = bin
SRC = src
OBJ = obj
INCLUDE = include
CXXFLAGS = -std=c++0x

CXX = g++

all: $(BIN)/FP $(BIN)/FBP

FP: $(BIN)/FP
FBP: $(BIN)/FBP
	
$(BIN)/FP: $(OBJ)/BacktrackingFP.o $(OBJ)/tda.o
	@$(CXX) -o $(BIN)/FP $(OBJ)/BacktrackingFP.o $(OBJ)/tda.o $(CXXFLAGS)
	@echo "Compilando programa principal FP..."

$(BIN)/FBP: $(OBJ)/BacktrackingFBP.o $(OBJ)/tda.o
	@$(CXX) -o $(BIN)/FBP $(OBJ)/BacktrackingFBP.o $(OBJ)/tda.o $(CXXFLAGS)
	@echo "Compilando programa principal FBP..."

$(OBJ)/BacktrackingFP.o: $(SRC)/BacktrackingFP.cpp $(INCLUDE)/tda.h
	@$(CXX) -c -o $(OBJ)/BacktrackingFP.o $(SRC)/BacktrackingFP.cpp -I$(INCLUDE) $(CXXFLAGS)
	@echo "Compilando código objeto del programa principal FP..."

$(OBJ)/BacktrackingFBP.o: $(SRC)/BacktrackingFBP.cpp $(INCLUDE)/tda.h
	@$(CXX) -c -o $(OBJ)/BacktrackingFBP.o $(SRC)/BacktrackingFBP.cpp -I$(INCLUDE) $(CXXFLAGS)
	@echo "Compilando código objeto del programa principal FBP..."

$(OBJ)/tda.o: $(SRC)/tda.cpp $(INCLUDE)/tda.h
	@$(CXX) -c -o $(OBJ)/tda.o $(SRC)/tda.cpp -I$(INCLUDE) $(CXXFLAGS)
	@echo "Compilando código objeto del algoritmo de backtracking..."

clean:
	@echo "Eliminando ejecutables y ficheros objeto..."
	@rm -f $(OBJ)/* $(BIN)/*
