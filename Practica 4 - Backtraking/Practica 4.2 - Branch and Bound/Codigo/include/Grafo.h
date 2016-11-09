#ifndef GRAFO
#define GRAFO

#include <iostream>
#include <vector>
using namespace std;

class Grafo;

struct arista {
		
	int nodo_ini;
	int nodo_dest;
	int tam;
};

Grafo CargarGrafo(char* nombre_archivo);

int DistanciaEuclidea(double x1, double y1, double x2, double y2);


class Grafo{

private:
	
	int **matriz;
	int TAM;
	vector <pair<double,double> > aristasMinimas; 
	void LiberarMemoria();
	
public:

	Grafo();
	Grafo(int nodos);
	Grafo(const Grafo &g);
	~Grafo();
	int size();
	// Insertar una arista en el grafo.
	void insertar(int nodo_ini,int nodo_dest,
				   int tamanio, bool dirigido = false);
	// Obtener la distancia entre dos nodos.
	int distancia(int nodo_ini, int nodo_dest);
	// Los nodos tienen o no una arista que los conecta.
	bool estanConectados(int nodo_ini, int nodo_dest);
	// Devolver las aristas conectadas a un nodo.
	vector<arista> aristasNodo(int nodo);
	// Devolver los nodos vecinos.
	vector<int> nodosConectados(int nodo);
	// Obtener el grado del nodo.
	int gradoNodo(int nodo);
	pair<double,double> getAristaMinima(int ind);
	void rellenaMin();
	int calculaCoste(vector<int> &camino);
	
	Grafo & operator=(const Grafo &g);

};

#endif
