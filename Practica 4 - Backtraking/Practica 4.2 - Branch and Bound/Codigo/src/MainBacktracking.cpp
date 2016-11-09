#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include "Grafo.h"
#include "Backtracking.h"

using namespace std;

int main(int argc, char **argv){

	if(argc < 2){

		cout << "Uso: ./bin/ByB <nombre archivo ciudades>" << endl;
		return 0;
	}

	vector<int> solucion;
	int coste;
	Backtracking s(argv[1]);

	clock_t before = clock();
	s.FBacktracking();
	clock_t after = clock();

	solucion = s.getMejorCamino();
	coste = s.getMejorCoste();

	double elapsed_time = ((double)(after - before)/CLOCKS_PER_SEC);

	cout << solucion.size() << " " << elapsed_time << endl;

	for(int i = 0; i < solucion.size(); i++ )

		cout << solucion[i]+1 << " " ;

	cout << coste << endl;

}