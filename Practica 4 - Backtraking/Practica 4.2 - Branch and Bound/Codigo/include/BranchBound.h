#ifndef BRANCH
#define BRANCH

#include <iostream>
#include <vector>
#include "Grafo.h"

using namespace std;

struct Nodo {
	int real;
	int heuristica;
	int valoracion;
	vector<int> camino;
	//El ultimo elemento del camino se corresponde con la ciudad
	//El tamaño del vector se corresponde con el nivel en el que se encuentra la ciudad
};

class NodeComparator{

public:

	bool operator()(Nodo &n1,Nodo &n2);

};

int VecinoMasCercano(Grafo & grafo, vector<int> & mejor_camino);

class BranchBound{

private:

	Grafo grafo;
	vector<int> camino;
	double heuristica1(Nodo & n, Nodo & padre);
	double heuristica2(Nodo & n, Nodo & padre);

public:

	BranchBound(char* nombre_archivo);
	Nodo BranchAndBound();
	Nodo generaHijo(Nodo & padre, int hijo);
	double TamanioCamino();
	
};

#endif