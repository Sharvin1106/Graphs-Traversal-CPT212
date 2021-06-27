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
                addEdge(i, v, g.adjMatrix[v][i]);    //add edge of the inverse graph
            }
        }
    }
}

bool Graph::isSC()
{
    bool* visited = new bool[numVertices];
    for (int i = 0; i < numVertices; i++)
        visited[i] = false; // declare visited

    DFSUtil(0, visited); //call DFSUtil function

    for (int i = 0; i < numVertices; i++)
        if (visited[i] == false)
            return false;   //return false if any of the vertices is not visited

    return true; //return true if all vertices is visited
}



void Graph::DFSUtil(int v, bool visited[]) {

    visited[v] = true;  // set the first vertex of the graph as visited

    for (int i = 0; i < numVertices; ++i)
    {
        if (adjMatrix[v][i] > 0) {
            if (!visited[i]) {   //if any of the vertices is not visited, call thefunction again
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
        visited[i] = false; //check whther a vertex is visited or not yet
        path[i] = -1; //used to hold path of each vertex
        dist[i] = infi; //used to hold distance of each vertex
        edge[i] = -1; //used to hold weight of edges
        next_location[i] = -1; //used to hold vertex that are adjacent to the current vertex
    }

    path[origin] = -1;//origin's path and distance value
    dist[origin] = 0;

    int current = origin; //current will become origin as path starts there

    while (reached == false) //while loop will keep looping until destincation is reached where reached becomes true.
    {
        int count = 0;
        visited[current] = true; //current will become visited so that it will not be selected again

        while (count == 0) //loop to find edges for a particular vertex
        {
            for (int i = 0; i < 5; i++)
            {
                if (adjMatrix[current][i] > 0 && visited[i] != true)
                {
                    edge[count] = adjMatrix[current][i];
                    next_location[count] = i;
                    count = count + 1;

                    double alt = dist[current] + adjMatrix[current][i]; //relaxation procedure 
                    if (alt < dist[i])
                    {
                        dist[i] = alt;
                        path[i] = current;
                    }
                }
            }

            if (count == 0) //if vertex have no edges create random edges
            {
                generateRandomEdge(all);
            }
        }

        double minDist = infi; //minimum distance from current
        int index = 0; //value to hold adjacent vertex

        for (int a = 0; a < count; a++) //loop to find shortest edge in order to determine next vertex.
        {
            if (edge[a] < minDist && edge[a] != -1)
            {
                minDist = edge[a];
                index = next_location[a];
            }
        }

        for (int i = 0; i < 5; i++) //loop to reset values of some array that will be used again for next loopug
        {
            edge[i] = -1;
            next_location[i] = -1;
        }

        current = index; //current will now be index which is the next chosen vetex

        if (current == destination) //checks whether destonation is reached
        {
            reached = true;
        }
    }
    printShortPath(path, dist, origin, destination); //call function to print shortest path
}

void Graph::printShortPath(int path[], double dist[], int origin, int destination)
{
    cout << "Shortest Path From " << origin << " to " << destination << ": "; //print origin and destination

    int finding = destination;

    int shortest_path[5], x = 0;
    while (finding != -1) //backtrack and find path staring from destination
    {
        shortest_path[x] = finding;
        finding = path[finding];
        x = x + 1;
    }

    for (int y = x - 1; y >= 0; y--) //print shortest_path array in reverse order staring from orign to destonation
    {
        cout << shortest_path[y];

        if (y != 0)
        {
            cout << " -> ";
        }
    }

    cout << "\nTotal Distance From Origin: " << dist[destination] << endl;//print total distance form destination
}


