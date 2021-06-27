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

void Graph::reset(int numVertices) {
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
    //To print the resulting graph
    cout << "\t0" << "\t1" << "\t2" << "\t3" << "\t4" << endl;
    for (int i = 0; i < numVertices; i++) {
        cout << i << " : \t";
        for (int j = 0; j < numVertices; j++)
            cout << adjMatrix[i][j] << "\t";
        cout << "\n";
    }
}

bool Graph::DFS() {
    
    int *visited = new int[numVertices];
   
    for (int i = 0; i < numVertices; i++) {
        visited[i] = 0;
        
    }
    //To perform DFS from different nodes
    for (int i = 0; i < numVertices; i++) {
        if (cycleDetectionDFS(i, visited)) {
            cout << "\nA cycle has been detected" << endl;
            cout << "\nThe cycle that has been found" << endl;
            printCycle(visited);
            return true;
        }
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
                if (!(visited[i] > 0) && cycleDetectionDFS(i, visited)) {
                    return true;
                }
                //Part where we detect the cycle and mark the node as visited
                else if (visited[i]>0 && i != v) {
                    visited[i] = -1;
                    return true;
                }
            }
        }

    }
    //If no adjacent vertex at all or there is no adjacent vertex that have been already visited
    visited[v] = 0; 
    return false;
}

bool Graph::isAvailable(int v1, int v2) {
    //Check if an edge available 
    if (adjMatrix[v1][v2] > 0) {
        return true;
    }
    else {
        return false;
    }
}

double Graph::getWeight(int v1, int v2) {
    //Get the weight between any two vertices
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
    int lastCycleIndex = 0;

    //To get the last vertex in the cycle
    for (int i = 0; i < numVertices; i++) {
        if (recursionStack[i] > 0 || recursionStack[i] == -1) {
            lastCycleIndex = i;
        }
    }
    //To get the first vertex in the cycle
    for (int i = 0; i < numVertices; i++) {
        if (recursionStack[i] != -1) {

            continue;
        }
        else {
            //Check if we can make the first vertex in the graph as the first vertex in the cycle, 
            //if the second vertex in the graph is the first vertex in the cycle
            if (i - 1 == 0 && recursionStack[i-1] > 0 && adjMatrix[lastCycleIndex][i-1] > 0) {
                visitedIndex = i -1;
            }
            else {
                visitedIndex = i;
            }
        }
    }
    //Printing the cycle
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

void Graph::dijkstraDist(Graph& all, int s, int d)
{
    int path[5], infi = 100000000, origin = s, next_location[5], c = 0, destination = d;
    double edge[5], dist[5];
    bool visited[5], reached = false;

    for (int i = 0; i < 5; i++)
    {
        visited[i] = false;
        path[i] = -1;
        dist[i] = infi;
        edge[i] = -1;
        next_location[i] = -1;
    }

    path[origin] = -1;
    dist[origin] = 0;

    int current = origin;

    while (reached == false)
    {
        int count = 0;
        visited[current] = true;

        while (count == 0)
        {
            for (int i = 0; i < 5; i++)
            {
                if (adjMatrix[current][i] > 0 && visited[i] != true)
                {
                    edge[count] = adjMatrix[current][i];
                    next_location[count] = i;
                    count = count + 1;

                    double alt = dist[current] + adjMatrix[current][i];
                    if (alt < dist[i])
                    {
                        dist[i] = alt;
                        path[i] = current;
                    }
                }
            }

            if (count == 0)
            {
                generateRandomEdge(all);
            }
        }

        double minDist = infi;
        int index = 0;

        for (int a = 0; a < count; a++)
        {
            if (edge[a] < minDist && edge[a] != -1)
            {
                minDist = edge[a];
                index = next_location[a];
            }
        }

        for (int i = 0; i < 5; i++)
        {
            edge[i] = -1;
            next_location[i] = -1;
        }

        current = index;

        if (current == destination)
        {
            reached = true;
        }
    }
    printShortPath(path, dist, origin, destination);
}

void Graph::printShortPath(int path[], double dist[], int origin, int destination)
{
    cout << "Shortest Path From " << origin << " to " << destination << ": ";

    int finding = destination;

    int shortest_path[5], x = 0;
    while (finding != -1)
    {
        shortest_path[x] = finding;
        finding = path[finding];
        x = x + 1;
    }

    for (int y = x - 1; y >= 0; y--)
    {
        cout << shortest_path[y];

        if (y != 0)
        {
            cout << " -> ";
        }
    }

    cout << "\nTotal Distance From Origin: " << dist[destination] << endl;
}


