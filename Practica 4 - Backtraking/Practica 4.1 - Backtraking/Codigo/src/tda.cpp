#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <utility>
#include <fstream>
#include <string>
#include <limits>
#include "tda.h"

using namespace std;

#define INFINITO numeric_limits<int>::max()

//compilar : g++  -o tda tda.cpp -std=c++0x

Solution::Solution(int _size)
:NULO(-1,-1),END(-2,-2){

	size=_size;
	Laberinto = new char*[size];

	for(int i=0; i<size; i++)
		Laberinto[i] = new char[size];

	generateMaze();
}

void Solution::generateMaze(){

	bool hay_salida;
	
	for(int i=0; i<size; i++){

		Laberinto[0][i] = 'X';
		Laberinto[size-1][i] = 'X';
		Laberinto[i][0] = 'X';
		Laberinto[i][size-1] = 'X';

	}
	
	for(int i=1; i<size-1; i++){

		for(int j=1; j<size-1; j++){
			
			if(i%2 == 0)
				Laberinto[i][j] = 'X';
			else
				Laberinto[i][j] = ' ';
				
			if(rand()%10 < 3 && i%2 == 0){
				Laberinto[i][j] = ' ';
				
			}else if(rand()%10 < 1 && i%2 != 0){

				hay_salida = false;

				for(int k=1; k<size-1 && !hay_salida; k++)
					if(Laberinto[(i-1)][k] == ' ' || Laberinto[(i+1)][k] == ' ')
						hay_salida = true;
				
				if(hay_salida)
					Laberinto[i][j] = 'X';
			}
		}
	}

	Laberinto[1][1] = ' ';

	for(int i=0; i<size/10+1; i++){

		Laberinto[size-2][size-2-i] = ' ';
		Laberinto[size-2-i][size-2] = ' ';

	}
}

Solution::celda Solution::generateNextMove(int pos_actual, int hijo_ant){

	celda nextMove;

	switch(hijo_ant){

		case 0: //devuelve SUR
			nextMove.first=camino[pos_actual].first+1;
			nextMove.second=camino[pos_actual].second;
		break;
		case 1: //devuelve ESTE
			nextMove.first=camino[pos_actual].first;
			nextMove.second=camino[pos_actual].second+1;
		break;
		case 2: //devuelve OESTE
		nextMove.first=camino[pos_actual].first;
			nextMove.second=camino[pos_actual].second-1;
		break;
		case 3: //devuelve NORTE
		nextMove.first=camino[pos_actual].first-1;
			nextMove.second=camino[pos_actual].second;
		break;
		default: //devuelve ACTUAL
			nextMove.first=camino[pos_actual].first;
			nextMove.second=camino[pos_actual].second;
		break;

	}

	return nextMove;

}

bool Solution::factible(Solution::celda hijo){

	return Laberinto[hijo.first][hijo.second]==' ';

}


bool Solution::findPath( int pos_actual){

	bool encontrado=false;
	int move=0;
	
	if(camino[pos_actual].first==size-2 && camino[pos_actual].second==size-2){

		return true;

	}

	else{

		for(move=0; move <4 && !encontrado; move++){

			celda nextMove=generateNextMove(pos_actual,move);
			if(factible(nextMove)){

				Laberinto[nextMove.first][nextMove.second]='o';
				camino.push_back(nextMove);
				encontrado=findPath(pos_actual+1);

			}
		}
		if(!encontrado){

		 	Laberinto[camino[pos_actual].first][camino[pos_actual].second]=' ';
		 	camino.pop_back();

		}

		return encontrado;
	}
}

bool Solution::findPath(){

	camino.clear();
	camino.push_back(make_pair(1,1));
	Laberinto[1][1]='o';
	return findPath(0);

}

bool Solution::findBestPath(int pos_actual){

	bool encontrado_mejor=false;
	int move=0;
	int mejor=camino_aux.empty()?INFINITO:camino_aux.size();

	if(camino[pos_actual].first==size-2 && camino[pos_actual].second==size-2){

		if(camino.size()<mejor){

			encontrado_mejor=true;
			camino_aux=camino;

		}else
			encontrado_mejor=false;

		Laberinto[camino[pos_actual].first][camino[pos_actual].second]=' ';
		camino.pop_back();

		return encontrado_mejor;

	}

	else{

		for(move=0; move <4 && camino.size()<mejor; move++){

			celda nextMove=generateNextMove(pos_actual,move);

			if(factible(nextMove)){

				Laberinto[nextMove.first][nextMove.second]='o';
				camino.push_back(nextMove);
				if(findBestPath(pos_actual+1))
					encontrado_mejor=true;

			}
		}
		
		Laberinto[camino[pos_actual].first][camino[pos_actual].second]=' ';
		camino.pop_back();

		return encontrado_mejor;

	}
}

bool Solution::findBestPath(){

	camino.clear();
	camino_aux.clear();
	camino.push_back(make_pair(1,1));
	Laberinto[1][1]='o';
	bool encontrado=findBestPath(0);
	camino=camino_aux;
	return encontrado;

}

vector<Solution::celda> Solution::getPath(){

	return camino;

}

void Solution::cleanMaze(){

	for(int i=0;i<size;i++){
		for(int j=0;j<size;j++){
			if(Laberinto[i][j]=='o')
				Laberinto[i][j]=' ';
		}
	}
}

void Solution::CprintMaze(){

	for(int i=0;i<camino.size();i++)

		Laberinto[camino[i].first][camino[i].second]='o';
	
	for(int i=0; i<size;i++){

		for(int j=0;j<size;j++)

			cout << Laberinto[i][j] << " ";

		cout << endl;

	}
}

void Solution::printMaze(string name){

	ofstream of;
	of.open(name);
	
	for(int i=0; i<size; i++)
		for(int j=0; j<size; j++)
			if(Laberinto[i][j] == 'X')
				of << i << " " << j << endl;
				
	of.close();

}

void Solution::printSolution(string name){

	ofstream of;
	of.open(name);
	
	for(int i=0; i<camino.size(); i++)

		of << camino[i].first << " " << camino[i].second << endl;
		
	of.close();

}

Solution::~Solution(){
	
	for(int i=0; i<size; i++)
		delete [] Laberinto[i];
	delete [] Laberinto;

}

/*int main(int argc, char **argv){

	srand(time(NULL));
	Solution sol(atoi(argv[1]));
	
	//sol.printMaze();
	sol.findBestPath();

	//if(sol.findBestPath())
		//sol.printSolution();
	sol.CprintMaze();
	
	return 0;

}*/