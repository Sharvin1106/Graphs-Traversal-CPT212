#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
using namespace std;

class Graph
{
private:
	double** adjMatrix;
	int numVertices;
public:
	Graph(int);
	~Graph();
	void addEdge(int, int, double);
	void removeEdge(int, int);
	void toString();
	bool isCyclic();
	bool isCyclicUtil(int, bool[], bool *);
	bool isAvailable(int, int);
	double getWeight(int, int);
	void printCycle(bool[]);
	//Strongly connected
	void DFSUtil(int, bool[]);
	bool isSC();
	void getTranspose();
};

#endif
