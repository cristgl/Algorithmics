#include <iostream>
#include <vector>
#include <limits>
#include <ctime>
#include <cstdlib>
#include "Grafo.h"

using namespace std;

const int INFINITY = numeric_limits<int>::max();

int VecinoMasCercano(Grafo & grafo, vector<int> & mejor_camino){

	int mejor_coste = INFINITY; // Mejor coste de entre todas las soluciones.

	int mejor_vecino_actual; // Mejor ciudad vecina seleccionado en cada paso de construir un camino.
	int mejor_distancia_vecino; // Coste de la mejor ciudad vecina seleccionada en cada paso.
	int distancia_vecino; // Coste de cada ciudad vecina que evaluamos en busca de la más cercana.

	int coste_camino_actual; // Coste del camino que estemos construyendo.
	int ciudad_actual; // Ciudad en la que estamos situados para buscar vecinos.

	for(int ciudad_inicial = 0 ; ciudad_inicial < grafo.size() ; ciudad_inicial++){ // Empezamos el greedy desde cada una de las ciudades.

		vector<bool> usados(grafo.size(), false); // Marcamos todas las ciudades como no visitadas
		vector<int> camino_actual; // y creamos un camino vacío.
		coste_camino_actual = 0;

		ciudad_actual = ciudad_inicial; // Nos situamos en la ciudad inicial,
		camino_actual.push_back(ciudad_inicial); // la añadimos al camino
		usados[ciudad_inicial] = true; // y la marcamos como visitada.

		for(int j = 1 ; j < grafo.size() ; j++){ // En cada paso añadiremos una ciudad.

			mejor_distancia_vecino = INFINITY;

			for(int k = 0 ; k < grafo.size() ; k++){ // Buscamos la ciudad más cercana.

				distancia_vecino = grafo.distancia(ciudad_actual, k);

				if(!usados[k] && distancia_vecino < mejor_distancia_vecino && distancia_vecino > 0){ // Si no está usado y el coste es mejor, se actualiza.

					mejor_vecino_actual = k;
					mejor_distancia_vecino = distancia_vecino;

				}
			}

			// Añadimos al camino el vecino más cercano, sumamos su coste y lo marcamos como visitado.
			usados[mejor_vecino_actual] = true;
			ciudad_actual = mejor_vecino_actual;
			camino_actual.push_back(mejor_vecino_actual);
			coste_camino_actual += mejor_distancia_vecino;

		}

		camino_actual.push_back(ciudad_inicial); // Completamos el ciclo con la ciudad inicial.
		coste_camino_actual += grafo.distancia(ciudad_actual, ciudad_inicial);

		if(coste_camino_actual < mejor_coste){ // Si este camino es el mejor hasta el momento, lo almacenamos.

			mejor_coste = coste_camino_actual;
			mejor_camino = camino_actual;

		}

	}

	return mejor_coste;

}

int main (int argc, char **argv){
	
	if(argc != 2){
	
		cerr << "El funcionamiento es: bin/VecinoMasCercano <nombre del archivo>" << endl;
		return -1;

	}
		
	char * nombre = argv[1];

	Grafo grafo;
	vector<int> camino;

	grafo = CargarGrafo(nombre);

	clock_t before = clock();
	int recorrido = VecinoMasCercano(grafo, camino);
	clock_t after = clock();

	double elapsed_time = ((double)(after - before)/CLOCKS_PER_SEC);

	//cout << "Camino obtenido: " << endl;

	cout << "DIMENSION: " << grafo.size() << endl;

	for (int i = 0 ; i < camino.size() ; i++)

		cout << camino[i]+1 << endl;



	//cout << "Recorrido total: " << recorrido << endl;
	//cout << "Tiempo de ejecución: " << elapsed_time << endl;
	
}
