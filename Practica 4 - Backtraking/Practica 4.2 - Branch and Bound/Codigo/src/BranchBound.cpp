#include <iostream>
#include <limits>
#include <vector>
#include <queue>
#include "BranchBound.h"
#include "Grafo.h"

using namespace std;

const int INFINITO = numeric_limits<int>::max();

bool NodeComparator::operator()(Nodo &n1,Nodo &n2){

	return n1.valoracion<n2.valoracion;
}

BranchBound::BranchBound(char* nombre_archivo){

	grafo = CargarGrafo(nombre_archivo);
}

double BranchBound::TamanioCamino(){
	int tamanio_camino = 0;
	for(int i = 0; i < camino.size()-1; i++ )
		tamanio_camino += grafo.distancia(camino[i],camino[i+1]);

	tamanio_camino += grafo.distancia(camino[0],camino[camino.size()-1]);

	return tamanio_camino;

}

Nodo BranchBound::generaHijo(Nodo & padre, int hijo){

	bool encontrado = true;
	int i;
	Nodo nuevo;

	for(i=hijo+1; i<grafo.size() && encontrado; i++){

		encontrado=false;

		for(int j=0; j<padre.camino.size() && !encontrado; j++)
			encontrado = padre.camino[j] == i;
		
	}

	if(!encontrado){
		nuevo.camino = padre.camino;
		nuevo.camino.push_back(i-1);
		heuristica1(nuevo,padre);
	} else {
		nuevo.valoracion = -1;
	}

	return nuevo;
}

double BranchBound::heuristica1(Nodo & n, Nodo & padre){
	if(padre.valoracion==-1){
		n.heuristica = 0;

		for(int i = 0 ; i < grafo.size() ; i++)
			n.heuristica += grafo.getAristaMinima(i).first;

		n.real = 0;
		n.valoracion = n.heuristica;

	}else{
		n.heuristica = padre.heuristica - grafo.getAristaMinima(n.camino.back()).first;
		n.real = padre.real + grafo.distancia(padre.camino.back(),n.camino.back());
		n.valoracion = n.real + n.heuristica;
	}
	
	return n.valoracion;
}

double BranchBound::heuristica2(Nodo & n, Nodo & padre){

	if(padre.valoracion==-1){
		n.heuristica = 0;

		for(int i = 0 ; i < grafo.size() ; i++)
			n.heuristica += (grafo.getAristaMinima(i).first + grafo.getAristaMinima(i).second)/2.0;

		n.real = 0;
		n.valoracion = n.heuristica;
		
	}else{
		n.heuristica = padre.heuristica - (grafo.getAristaMinima(n.camino.back()).first+grafo.getAristaMinima(n.camino.back()).second)/2.0;
		n.real = padre.real + grafo.distancia(padre.camino.back(),n.camino.back());
		n.valoracion = n.real + n.heuristica;
	}
	
	return n.valoracion;
}

Nodo BranchBound::BranchAndBound(){
	
	vector<int> solucion, aux;
	priority_queue<Nodo,vector<Nodo>,NodeComparator> abiertos;
	long long int ant, explorados = 0, podas = 0, max_cola = 0;
	Nodo node,hijo,mejor_solucion,nodo_nulo;
	node.camino.push_back(0);
	nodo_nulo.valoracion=-1;

	heuristica1(node,nodo_nulo);

	mejor_solucion.valoracion = VecinoMasCercano(grafo, aux) /*INFINITO*/; //Descomentar uno u otro para asignar cota superior
	
	abiertos.push(node);

	while(!abiertos.empty()){

		if(abiertos.size() > max_cola)
			max_cola = abiertos.size();

		node = abiertos.top();
		abiertos.pop();
		explorados++;

		// Comprobar si es solución y si es mejor que la mejor encontrada hasta el momento.
		if((node.camino.size()==grafo.size())){
			node.valoracion += grafo.distancia(node.camino.back(),node.camino.front());

			if (node.valoracion < mejor_solucion.valoracion){
				mejor_solucion.camino = node.camino;
				mejor_solucion.valoracion = node.valoracion;
			}
		}
		else if(mejor_solucion.valoracion > node.valoracion){ // Podar si la solución parcial es peor que la mejor solución encontrada.
			ant=-1;
			hijo=generaHijo(node,ant); // Generar hijos.

			do{ // Meter hijos en abiertos.

				if(hijo.valoracion < mejor_solucion.valoracion)
					abiertos.push(hijo);

				else
					podas++;
				ant=hijo.camino.back();
				hijo=generaHijo(node,ant);

			} while(hijo.valoracion!=-1);
		}
	}
	camino = mejor_solucion.camino;
	cout << "Nodos explorados: " << explorados << endl;
	cout << "Nodos podados: " << podas << endl;
	cout << "Tamaño maximo de la cola: " << max_cola << endl;
	return mejor_solucion;
}

//VECINO MAS CERCANO

int VecinoMasCercano(Grafo & grafo, vector<int> & mejor_camino){

	int mejor_coste = INFINITO; // Mejor coste de entre todas las soluciones.

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

			mejor_distancia_vecino = INFINITO;

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
