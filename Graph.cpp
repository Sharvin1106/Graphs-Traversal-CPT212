#include "Graph.h"

Graph::Graph(int numVertices) {
    this->numVertices = numVertices;
    adjMatrix = new double* [numVertices];
    for (int i = 0; i < numVertices; i++) {
        adjMatrix[i] = new double[numVertices];
        for (int j = 0; j < numVertices; j++) 
            adjMatrix[i][j] = 0;
        
    }
    visitedNum = 0;
}

void Graph::addEdge(int i, int j, double weight) {
	adjMatrix[i][j] = weight;
}

void Graph::removeEdge(int i, int j) {
    adjMatrix[i][j] = 0;
}

void Graph::toString() {
    cout << "\t0" << "\t1" << "\t2" << "\t3" << "\t4" << endl;
    for (int i = 0; i < numVertices; i++) {
        cout << i << " : \t";
        for (int j = 0; j < numVertices; j++)
            cout << adjMatrix[i][j] << "\t";
        cout << "\n";
    }
}

bool Graph::DFS() {
    int* visited = new int[numVertices];
    
    
    for (int i = 0; i < numVertices; i++) {
        visited[i] = 0;
    }

    for (int i = 0; i < numVertices; i++)
        if (cycleDetectionDFS(i, visited)) {
            printCycle(visited);
            return true;
        }
    return false;
}

bool Graph::cycleDetectionDFS(int v, int visited[])
{
    if (visited[v] == 0)
    {
        visited[v] = visitedNum++;
        
        for (int i = 0; i < numVertices; i++)
        {
            if (adjMatrix[v][i] > 0) {
                if (!visited[i] && cycleDetectionDFS(i, visited)) {
                    return true;
                }
                else if (visited[i]>0) {
                    visited[i] = -1;
                    return true;
                   
                }
            }
        }

    }
   
    visited[v] = 0; 
    
    return false;
}

bool Graph::isAvailable(int v1, int v2) {
    if (adjMatrix[v1][v2] > 0) {
        return true;
    }
    else {
        return false;
    }
}

double Graph::getWeight(int v1, int v2) {
    return adjMatrix[v1][v2];
}

Graph::~Graph() {
    for (int i = 0; i < numVertices; i++)
        delete[] adjMatrix[i];
    delete[] adjMatrix;

}

void Graph::printCycle(int recursionStack[]) {
    cout << "\n";
    int visitedIndex = 0;
    for (int i = 0; i < numVertices; i++) {
        if (recursionStack[i] != -1) {
            continue;
        }
        else {
            visitedIndex = i;
        }
    }

    for (int i = visitedIndex; i < numVertices; i++) {
        if (recursionStack[i] > 0 || recursionStack[i] == -1) {
            cout << i << "--> ";
        }

    }
    cout << visitedIndex << endl;

}

void Graph::generateRandomEdge(Graph& all) {
    int v1;
    int v2;
    srand(time(0));
    v1 = rand() % numVertices;
    v2 = rand() % numVertices;

    while (v1 == v2 || isAvailable(v1, v2)) {
        v1 = rand() % numVertices;
        v2 = rand() % numVertices;
    }
    
    addEdge(v1, v2, all.getWeight(v1, v2));
    
}

void Graph::getTranspose(Graph& g)
{
    for (int v = 0; v < numVertices; v++)
    {
        for (int i = 0; i < numVertices; ++i)
        {
            if (g.adjMatrix[v][i] > 0) {
                addEdge(i, v, g.adjMatrix[v][i]);
            }
        }
    }
}

bool Graph::isSC()
{
    bool* visited = new bool[numVertices];
    for (int i = 0; i < numVertices; i++)
        visited[i] = false;

    DFSUtil(0, visited);

    for (int i = 0; i < numVertices; i++)
        if (visited[i] == false)
            return false;

    return true;
}

void Graph::DFSUtil(int v, bool visited[]) {

    visited[v] = true;

    for (int i = 0; i < numVertices; ++i)
    {
        if (adjMatrix[v][i] > 0) {
            if (!visited[i]) {
                DFSUtil(i, visited);
            }
        }
    }

}

