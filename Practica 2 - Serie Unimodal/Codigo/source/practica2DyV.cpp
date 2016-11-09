#include <iostream>
#include <ctime>
#include <cstdlib>
#include <climits>
#include <cassert>
#include <chrono>
#include <iomanip>
#include <algorithm>

//compilar con g++ practica2.c -o practica2 

#define umbral 3

using namespace std;

int BusquedaFB(int * & v, int ini, int fin){

	int maximo = ini;
	
	if((fin - ini) > 1){
	
		for (int i=ini; i<fin; i++)

			if(v[i] > v[maximo])

				maximo = i;
		
	}

	return maximo;

}

int busqueda(int * & v, const int ini, const int fin){

	int solucion;

	if((fin - ini) <= umbral)

		solucion = BusquedaFB(v,ini,fin);
	
	else{

		solucion = (fin + ini)/2;

		if(v[solucion-1] < v[solucion] && v[solucion] < v[solucion+1])

			solucion = busqueda(v,solucion+1,fin);

		else if(v[solucion-1] > v[solucion] && v[solucion] > v[solucion+1])

			solucion = busqueda(v,ini,solucion);
		
	}

	return solucion;
	
}

double uniforme() //Genera un número uniformemente distribuido en el
                  //intervalo [0,1) a partir de uno de los generadores
                  //disponibles en C.
{
double u;
  u = (double) rand();
  u = u/(double)(RAND_MAX+1.0);
 return u;
}

int main(int argc, char * argv[]){
	std::chrono::high_resolution_clock::time_point t_antes, t_despues, t_antes2, t_despues2;
	int solucion;
	std::chrono::duration<double> d1,d2, d_acumulado;
		
	if (argc != 2)
    {
      cerr << "Formato " << argv[0] << " <num_elem>" << endl;
      return -1;
    }

  	int n = atoi(argv[1]);
	int * T = new int[n];
  	assert(T);

  	for(int j=0; j<200; j++) {
  		/*Codigo para generar la serie unimodal*/
		srand(time(0));
		double u=uniforme();
		int p=1+(int)((n-2)*u);
		T[p]=n-1;
		for (int i=0; i<p; i++) T[i]=i;
		for (int i=p+1; i<n; i++) T[i]=n-1-i+p;
		/****************************************/


		t_antes=std::chrono::high_resolution_clock::now();
		solucion = busqueda(T,0,n);
		t_despues=std::chrono::high_resolution_clock::now();
	
		//t_antes2=std::chrono::high_resolution_clock::now();
		//solucion = BusquedaFB(T,0,n-1);
		//t_despues2=std::chrono::high_resolution_clock::now();

		if(j==0)
			d_acumulado = std::chrono::duration_cast<std::chrono::duration<double>>((t_despues-t_antes));
		else
			d_acumulado += std::chrono::duration_cast<std::chrono::duration<double>>((t_despues-t_antes));
	}


	d1=d_acumulado/200;
	//d2=std::chrono::duration_cast<std::chrono::duration<double>>(t_despues2-t_antes2);
	
	cout << n << " " << d1.count() << endl;
	//cout << n << " " << d2.count() << endl;
	
	return 0;
	
}
