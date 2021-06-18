#include <iostream>
#include <fstream>
#include "Graph.h"
using namespace std;
void initializeGraph(Graph&);
void initializeWeights(Graph&, int);

int main()
{
    int vertices = 5;
    Graph g(vertices);
    Graph allWeights(vertices);

    initializeGraph(g);
    initializeWeights(allWeights, vertices);
    
    g.toString();
    

    /*while (!g.isSC()) {
        cout << "This is not strongly connected graph" << endl;
        generateRandomEdge(vertices, g, allWeights);
    }

    cout << "Graph strongly connected graph" << endl << endl;
    g.toString();*/


    while (!g.DFS()) {
       cout << "Graph doesn't contain cycle" << endl;
       
       g.generateRandomEdge(allWeights);
    }
    cout << "Graph is cyclic" << endl;
    g.toString();
   
}

void initializeGraph(Graph &g) {
    g.addEdge(0, 1, 8923.20);
    g.addEdge(1, 2, 9705.75);
    g.addEdge(3, 2, 9331.86);
    g.addEdge(4, 3, 1606.09);
    g.addEdge(4, 0, 9392.12);
    

}


void initializeWeights(Graph &all, int vertices) {
    fstream weightFile;
    double weight;
    weightFile.open("weights.txt", ios::in);

    while (weightFile) {
        for (int i = 0; i < vertices; i++) {
            for (int j = 0; j < vertices; j++) {
                weightFile >> weight;
                all.addEdge(i, j, weight);
            }
            weightFile.ignore();
        }
    }
}
