#include <iostream>
#include <fstream>
#include <ctime>
#include "Graph.h"
using namespace std;
void initializeGraph(Graph&);
void generateRandomEdge(int, Graph&, Graph&);
void initializeWeights(Graph&, int);
int main()
{
    int vertices = 5;
    Graph g(vertices);
    Graph allWeights(vertices);

    initializeGraph(g);
    initializeWeights(allWeights, vertices);
    /*g.addEdge(0, 1, 8923.20);
    g.addEdge(1, 2, 9705.75);
    g.addEdge(4, 2, 9331.86);
    g.addEdge(3, 4, 1606.09);
    g.addEdge(3, 0, 9392.12);*/
    g.toString();
    //g.isSC();

    /*while (!g.isSC()) {
        cout << "This is not strongly connected graph" << endl;
        generateRandomEdge(vertices, g, allWeights);
    }

    cout << "Graph strongly connected graph" << endl << endl;
    g.toString();*/


    while (!g.DFS()) {
       cout << "Graph doesn't contain cycle" << endl;
       generateRandomEdge(vertices, g, allWeights);
    }
    cout << "Graph is cyclic" << endl;
    g.toString();
    //.toString();
    //cout << g.isSC() << endl;
}

void initializeGraph(Graph &g) {
    g.addEdge(0, 1, 8923.20);
    g.addEdge(1, 2, 9705.75);
    g.addEdge(3, 2, 9331.86);
    g.addEdge(4, 3, 1606.09);
    g.addEdge(4, 0, 9392.12);
    //g.addEdge(2, 0, 1129.40);

}

void generateRandomEdge(int vertex, Graph &g, Graph &all) {
    int v1;
    int v2;
    srand(time(0));
    v1 = rand() % vertex;
    v2 = rand() % vertex;
    
    while (v1 == v2 || g.isAvailable(v1, v2)) {
        v1 = rand() % vertex;
        v2 = rand() % vertex;
    }
    //cout << all.getWeight(v1, v2) << endl;
    g.addEdge(v1, v2, all.getWeight(v1, v2));
    //cout << "Added edge" << v1 << " " << v2 << endl;
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
