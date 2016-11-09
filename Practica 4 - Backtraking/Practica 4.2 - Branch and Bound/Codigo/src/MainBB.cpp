#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include "Grafo.h"
#include "BranchBound.h"

using namespace std;

int main(int argc, char **argv){

	if(argc < 2){

		cout << "Uso: ./bin/ByB <nombre archivo ciudades>" << endl;
		return 0;
	}

	Nodo solucion;
	BranchBound s(argv[1]);
	int tamanio_ciclo = 0;
	
	cout << "----------------------------------------------" << endl;
	clock_t before = clock();
	solucion = s.BranchAndBound();
	clock_t after = clock();

	double elapsed_time = ((double)(after - before)/CLOCKS_PER_SEC);

	cout << solucion.camino.size() << " " << elapsed_time << endl;

	for(int i = 0; i < solucion.camino.size(); i++ )
		cout << solucion.camino[i]+1 << " " ;
	

	cout << endl << "Tamanio camino: " << s.TamanioCamino() << endl;
	cout << "-------------- Dimension " << solucion.camino.size() << " -------------- " << endl;

}