#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include "Grafo.h"

using namespace std;

Grafo CargarGrafo(char* nombre_archivo) {

	int dim;
	pair<double,double> coordenadas;
	vector< pair<double,double> > vectorNodos;  
	ifstream f;
	int i;
	double d;
	
	f.open(nombre_archivo);
	f.ignore(11,' '); // Ignora los caracteres anteriores a la dimensión.
	f >> dim; // Lee la dimensión del problema.
	
	Grafo graf(dim);
	
	for (i=0; i<dim; i++) {
		
		f >> d; // Lee el número de nodo.
		
		f >> d; // Lee x.
		coordenadas.first = d;
		
		f >> d; // Lee y.
		coordenadas.second = d;
		
		vectorNodos.push_back(coordenadas);
	}
	
	
	for (i=0; i<vectorNodos.size(); i++)
	
		for (int n=(i+1); n<vectorNodos.size(); n++)
			
			graf.insertar(i,n,DistanciaEuclidea(vectorNodos[i].first,vectorNodos[i].second,
				vectorNodos[n].first,vectorNodos[n].second));
				
		
	return graf;
}

int DistanciaEuclidea(double x1, double y1, double x2, double y2) {

	return round(sqrt(pow(x1-x2,2) + pow(y1-y2,2)));
}

////////////////////////// ESPECIFICACION CLASE GRAFO //////////////////////////

Grafo::Grafo() {
	
	TAM = 0;
	matriz = NULL;
}

Grafo::Grafo(int nodos) {

	TAM = nodos;
	matriz = new int* [TAM];
	for (int i = 0; i<TAM; i++)
		matriz[i] = new int [TAM];
		
	for (int f = 0; f<TAM; f++)
		for (int c = 0; c<TAM; c++)
			matriz[f][c] = -1;
}

Grafo::Grafo(const Grafo &g) {
	
	TAM = g.TAM;
	matriz = new int* [TAM];
	for (int i = 0; i<TAM; i++)
		matriz[i] = new int [TAM];
		
	for (int f = 0; f<TAM; f++)
		for (int c = 0; c<TAM; c++)
			matriz[f][c] = g.matriz[f][c];
}

Grafo::~Grafo() {
	
	LiberarMemoria();
}

int Grafo::size () {
	
	return TAM;
}

void Grafo::insertar (int nodo_ini,int nodo_dest, int tamanio, bool dirigido) {
	
	if (!dirigido) {
		
		matriz[nodo_ini][nodo_dest] = tamanio;
		matriz[nodo_dest][nodo_ini] = tamanio;	
	}
	else
	
		matriz[nodo_ini][nodo_dest] = tamanio;
}

int Grafo::distancia(int nodo_ini, int nodo_dest) {
	
	return matriz[nodo_ini][nodo_dest];
}

bool Grafo::estanConectados (int nodo_ini, int nodo_dest) {
	
	if (matriz[nodo_ini][nodo_dest] > 0)
	
		return true;
		
	else
	
		return false;
}

vector<arista> Grafo::aristasNodo (int nodo) {
	
	vector<arista> v;
	arista a;
	a.nodo_ini = nodo;
	
	for (int i = 0; i<TAM; i++)
	
		if (matriz[nodo][i] > 0) {
		
			a.nodo_dest = i;
			a.tam = matriz[nodo][i];
			
			v.push_back(a);
		}
	
	return v;
}

vector<int> Grafo::nodosConectados (int nodo) {
	
	vector<int> nodos;
	
	for (int i = 0; i<TAM; i++)
	
		if (matriz[nodo][i] > 0) 
			
			nodos.push_back(i);
	
	return nodos;
}

int Grafo::gradoNodo (int nodo) {
	
	int grado = 0;
	
	for (int i = 0; i<TAM; i++)
	
		if (matriz[nodo][i] > 0) 
			
			grado++;
	
	return grado;
}

int Grafo::costeCircuito(vector<int> & circuito){

	int coste = 0;

	for(int i = 1 ; i < circuito.size() ; i++)

		coste += distancia(circuito[i-1], circuito[i]);

	return coste;

}

pair<double,double> Grafo::getNodeFromVector(int indice){
	
	return vectorNodos.at(indice);
}

void Grafo::CargarVectorNodos(char* nombre_archivo){

	int dim;
	pair<double,double> coordenadas;
	ifstream f;
	int i;
	double d;
	
	f.open(nombre_archivo);
	f.ignore(11,' '); // Ignora los caracteres anteriores a la dimensión.
	f >> dim; // Lee la dimensión del problema.
	
	for (i=0; i<dim; i++) {
		
		f >> d; // Lee el número de nodo.
		
		f >> d; // Lee x.
		coordenadas.first = d;
		
		f >> d; // Lee y.
		coordenadas.second = d;
		
		vectorNodos.push_back(coordenadas);
	}
}

Grafo & Grafo::operator = (const Grafo &g) {
	
	LiberarMemoria();
	
	TAM = g.TAM;
	matriz = new int* [TAM];
	for (int i = 0; i<TAM; i++)
		matriz[i] = new int [TAM];
		
	for (int f = 0; f<TAM; f++)
		for (int c = 0; c<TAM; c++)
			matriz[f][c] = g.matriz[f][c];

	return *this;
}

void Grafo::LiberarMemoria () {
	
	TAM = 0;
	
	if (matriz != NULL) {
	
		for (int i = 0; i<TAM; i++)
			delete [] matriz[i];
		delete[] matriz;
	}
	
	matriz = NULL;			
}