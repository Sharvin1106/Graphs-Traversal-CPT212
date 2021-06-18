#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <ctime>
using namespace std;

class Graph
{
private:
	double** adjMatrix;
	int numVertices;
	int visitedNum;
public:
	Graph(int);
	~Graph();
	void addEdge(int, int, double);
	void removeEdge(int, int);
	void toString();
	bool isAvailable(int, int);
	double getWeight(int, int);
	void generateRandomEdge(Graph&);
	
	bool DFS();
	bool cycleDetectionDFS(int, int[]);
	void printCycle(int[]);

	bool isSC();
	void getTranspose(Graph&);
	void DFSUtil(int, bool[]);
};

#endif
