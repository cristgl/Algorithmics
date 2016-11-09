#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include <limits>
#include "Grafo.h"

using namespace std;

const int INFINITO = numeric_limits<int>::max();


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
				
	graf.rellenaMin();
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

	aristasMinimas.resize(nodos);
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
	aristasMinimas=g.aristasMinimas;
	matriz = new int* [TAM];
	for (int i = 0; i<TAM; i++)
		matriz[i] = new int [TAM];
		
	for (int f = 0; f<TAM; f++)
		for (int c = 0; c<TAM; c++)
			matriz[f][c] = g.matriz[f][c];

}

void Grafo::rellenaMin(){

	aristasMinimas.resize(TAM);
	int min, min2;
	for(int i=0; i<TAM; i++){
		min2 = min = INFINITO;
		for(int j=0; j<TAM; j++){
			if(i!=j && matriz[i][j] < min){
				min2 = min;
				min=matriz[i][j];
			} else if (i != j && matriz[i][j] < min2) {
				min2 = matriz[i][j];
			}
		}
		aristasMinimas[i].first = min;
		aristasMinimas[i].second = min2;
	}
}

int Grafo::calculaCoste(vector<int> &camino){

	int coste = 0;

	for(int i = 1 ; i < camino.size() ; i++)

		coste += distancia(i-1,i);

	if(camino.size() == TAM)

		coste += distancia(camino.back(),camino.front());

	return coste;

}

Grafo::~Grafo() {
	
	LiberarMemoria();
}

int Grafo::size () {
	
	return TAM;
}

pair<double,double> Grafo::getAristaMinima(int ind){
	return aristasMinimas[ind];
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


Grafo & Grafo::operator = (const Grafo &g) {
	
	LiberarMemoria();
	
	TAM = g.TAM;
	aristasMinimas=g.aristasMinimas;
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