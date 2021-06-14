#include "Graph.h"

Graph::Graph(int numVertices) {
    this->numVertices = numVertices;
    adjMatrix = new double* [numVertices];
    for (int i = 0; i < numVertices; i++) {
        adjMatrix[i] = new double[numVertices];
        for (int j = 0; j < numVertices; j++) 
            adjMatrix[i][j] = 0;
        
    }
}

void Graph::addEdge(int i, int j, double weight) {
	adjMatrix[i][j] = weight;
	//adjMatrix[j][i] = true;
}

void Graph::removeEdge(int i, int j) {
    adjMatrix[i][j] = 0;
    //adjMatrix[j][i] = false;
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

bool Graph::isCyclic() {
    bool* visited = new bool[numVertices];
    bool* recStack = new bool[numVertices];
    bool cycleDetected = false;
    for (int i = 0; i < numVertices; i++) {
        visited[i] = false;
        recStack[i] = false;
    }

    for (int i = 0; i < numVertices; i++) {
        if (isCyclicUtil(i, visited, recStack)) {
            //printCycle(recStack);
            cycleDetected = true;
        }
    }

    if (cycleDetected)
        return true;
    else
        return false;
}

bool Graph::isCyclicUtil(int v, bool visited[], bool* recStack)
{
    if (visited[v] == false)
    {
        // Mark the current node as visited and part of recursion stack
        visited[v] = true;
        recStack[v] = true;

        // Recur for all the vertices adjacent to this vertex
        
        for (int i = 0; i < numVertices; ++i)
        {
            if (adjMatrix[v][i] > 0) {
                if (!visited[i] && isCyclicUtil(i, visited, recStack)) {
                    //printCycle(recStack);
                    return true;
                }
                else if (recStack[i]) {
                    printCycle(recStack);
                    return true;
                }
            }
        }

    }
    recStack[v] = false;  // remove the vertex from recursion stack
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

void Graph::printCycle(bool recursionStack[]) {
    cout << "\n";
    for (int i = 0; i < numVertices; i++) {
        if (recursionStack[i]) {
            if (i != numVertices - 1)
                cout << i << "--> ";
            else
                cout << i << endl;
        }
    }
    cout << "\n";
}

void Graph::DFSUtil(int v, bool visited[]) {
    
    visited[v] = true;

    for (int i = 0; i < numVertices; ++i)
    {
        //cout << adjMatrix[v][i] << endl;
        //cout << v << " " << i << endl;
        if (adjMatrix[v][i] > 0) {
            if (!visited[i]) {
                DFSUtil(i, visited);
            }
           
        }
    }
}

void Graph::getTranspose()
{
    //Graph g(numVertices);
    for (int v = 0; v < numVertices; v++)
    {
        // Recur for all the vertices adjacent to this vertex
        
        for (int i = 0; i < numVertices; ++i)
        {
            if (adjMatrix[v][i] > 0) {
                cout << v << " " << i << " " << adjMatrix[v][i] << endl;
                addEdge(i, v, adjMatrix[v][i]);
            }
        }
    }
    //return g;
}

bool Graph::isSC()
{
    // St1p 1: Mark all the vertices as not visited (For first DFS)
    bool* visited = new bool[numVertices];
    for (int i = 0; i < numVertices; i++)
        visited[i] = false;

    // Step 2: Do DFS traversal starting from first vertex.
    DFSUtil(0, visited);

    // If DFS traversal doesn’t visit all vertices, then return false.
    for (int i = 0; i < numVertices; i++)
        if (visited[i] == false)
            return false;

    // Step 3: Create a reversed graph
    Graph gr(numVertices);
    gr.getTranspose();
    // Step 4: Mark all the vertices as not visited (For second DFS)
    for (int i = 0; i < numVertices; i++)
        visited[i] = false;

    // Step 5: Do DFS for reversed graph starting from first vertex.
    // Staring Vertex must be same starting point of first DFS
    //cout << "traversing transpose" << endl;
    //.toString();
    gr.DFSUtil(0, visited);

    // If all vertices are not visited in second DFS, then
    // return false
    for (int i = 0; i < numVertices; i++)
        if (visited[i] == false)
            return false;

    return true;
}