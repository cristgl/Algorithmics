#ifndef SOL
#define SOL

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <utility>
#include <fstream>
#include <string>

using namespace std;

class Solution{
	private:
		typedef pair<int,int> celda;
		char **Laberinto;
		int size;
		vector<celda> camino;
		vector<celda> camino_aux;
		celda NULO; // -1,-1
		celda END;  // -2,-2

		bool findPath(int pos_actual);
		bool findBestPath(int pos_actual);
	public:
		Solution(int _size);
		celda generateNextMove(int pos_actual, int hijo_ant);
		void generateMaze();
		bool factible(celda hijo);
		bool findPath();
		void CprintMaze();
		void printMaze(string name);
		void printSolution(string name);
		bool findBestPath();
		void cleanMaze();
		vector<celda> getPath(); 
		~Solution();
};

#endif