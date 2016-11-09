#include <iostream>
#include <vector>
#include <limits>
#include <ctime>
#include <cstdlib>
#include "Grafo.h"

using namespace std;
const int INFINITY = numeric_limits<int>::max();

int masLejanoCentro(Grafo &grafo,vector<int> &circuito){
	int mejor_aumento=INFINITY,recorrido,max_dist,pos_inserc;
	vector<bool> usados(grafo.size(),false);
	pair<double,double> coord,centro;
	double min_x=INFINITY,min_y=INFINITY,max_x=-1,max_y=-1,min_dist=INFINITY,dist,aumento=-1;
	int ciudad_centro;
	int ciudad_norte,ciudad_sur,nodo_candidato;


	for(int i=0;i<grafo.size();i++){
		coord=grafo.getNodeFromVector(i);
		if(coord.first>max_x)
			max_x=coord.first;
		else if(coord.first < min_x)
			min_x=coord.first;

		if(coord.second>max_y){
			max_y=coord.second;
			ciudad_norte=i;
		}else if(coord.second < min_y){
			min_y=coord.second;
			ciudad_sur=i;
		}
	}
	centro.first=(max_x+min_x)/2.0;
	centro.second=(max_y+min_y)/2.0;

	usados[ciudad_sur]=true;
	usados[ciudad_norte]=true;
	circuito.push_back(ciudad_sur);
	circuito.push_back(ciudad_norte);

	for(int i=0;i<grafo.size();i++){
		if(!usados[i]){
			coord=grafo.getNodeFromVector(i);
			dist=DistanciaEuclidea(coord.first,coord.second,centro.first,centro.second);
			if(dist<min_dist){
				min_dist=dist;
				ciudad_centro=i;
			}
		}
	}



	for (int i = 0 ; i < grafo.size() ; i++)
		if (grafo.distancia(circuito[0],i) + grafo.distancia(circuito[1],i)
			 > aumento && !usados[i]) {
			
			aumento = grafo.distancia(circuito[0],i) + 
						grafo.distancia(circuito[1],i);
			nodo_candidato = i;
		}

	circuito.push_back(nodo_candidato);
	usados[nodo_candidato]=true;

	for(int i=0;i<grafo.size()-3;i++){
		max_dist=-1;
		for(int j=0;j<grafo.size();j++){
			if(!usados[j]){
				dist=j==ciudad_centro?0:grafo.distancia(ciudad_centro,j);
				if(dist>max_dist){ 
					max_dist=dist;
					nodo_candidato=j;
				}
			}
		}
		mejor_aumento=INFINITY;
		for(int j=0;j<circuito.size();j++){
			aumento=grafo.distancia(circuito[j],nodo_candidato)+
					grafo.distancia(circuito[(j+1)%circuito.size()],j)-
					grafo.distancia(circuito[j],circuito[(j+1)%circuito.size()]);
			if(aumento < mejor_aumento){
				mejor_aumento=aumento;
				pos_inserc=j+1;
			}
		}

		if(pos_inserc==circuito.size())
			circuito.push_back(nodo_candidato);
		else
			circuito.insert(circuito.begin()+pos_inserc,nodo_candidato);
		usados[nodo_candidato]=true;
	}

	for(int i=0;i<circuito.size();i++)
		recorrido+=grafo.distancia(circuito[i],circuito[(i+1)%circuito.size()]);
	circuito.push_back(circuito[0]);

	return recorrido;
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
	grafo.CargarVectorNodos(nombre);

	clock_t before = clock();
	int recorrido = masLejanoCentro(grafo, camino);
	clock_t after = clock();

	double elapsed_time = ((double)(after - before)/CLOCKS_PER_SEC);

	//cout << "Camino obtenido: " << endl;

	cout << "DIMENSION: " << grafo.size() << endl;

	for (int i = 0 ; i < camino.size() ; i++)
		cout << camino[i]+1 << endl;



	//cout << "Recorrido total: " << recorrido << endl;
	//cout << "Tiempo de ejecución: " << elapsed_time << endl;
	
}
