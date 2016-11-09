#include <iostream>
#include <ctime>
#include <cstdlib>
#include "tda.h"

using namespace std;

int main(int argc, char **argv){

	if(argc != 2){
	
		cerr << "El funcionamiento es: bin/Backtracking <tamaño del laberinto>" << endl;
		return -1;

	}

	clock_t before, after;
	bool path_found = false;
	int size, exitos;
	double elapsed_time;

	srand(time(NULL));
	size = atoi(argv[1]);
	Solution sol(size);
	
	sol.cleanMaze();
	//sol.printMaze("Maze" + to_string(size));

	sol.cleanMaze();
	for(int i=0; i<15; i++){
		before = clock();
		path_found = sol.findPath();
		after = clock();
		if(path_found){
			elapsed_time += ((double)(after - before)/CLOCKS_PER_SEC);
			exitos++;
			//cout << "-------Solucion no optima-------" << endl;
			//sol.CprintMaze();
		}
		sol.generateMaze();
	}

	elapsed_time = elapsed_time / exitos;
	cout << size << " " << elapsed_time << endl;
	
	return 0;

}