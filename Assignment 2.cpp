#include <iostream>
#include <fstream>
#include "Graph.h"
using namespace std;
void initializeGraph(Graph&);
void initializeWeights(Graph&, int);
void MainMenu();
bool checkStrong(Graph&, int);
int main()
{
    //Five vertices
    int vertices = 5;

    //Declaring main graph and graph with all weights
    Graph g(vertices);
    Graph allWeights(vertices);

    //Initializing
    initializeGraph(g);
    initializeWeights(allWeights, vertices);
    
    int choice = 0;
    

    do {
        MainMenu();
        cin >> choice;
        //Validation for choice
        while (choice < 1 || choice > 7) {
            cout << "Invalid input." << endl;
            cout << "Re-enter your choice." << endl;
            cin >> choice;
        }

        if (choice != 8) {
            if (choice == 1) {
                g.toString();
                cin.get();
                cin.get();
            }
            else if (choice == 2) {
                while (!checkStrong(g, vertices)) {
                    char selection;
                    cout << "The graph is not strong connected " << endl;
                    cout << "Would you like to make it strong?" << endl;
                    cin >> selection;
                    if (selection == 'Y' || selection == 'y') {
                        g.generateRandomEdge(allWeights);
                    }
                    else {
                        break;
                    }
                }
                g.toString();
                cin.get();
                cin.get();
                
            }
            else if (choice == 3) {
                while (!g.DFS()) {
                    char selection;
                    cout << "The graph does not contain cycles " << endl;
                    cout << "Would you like to make it to have cycles?" << endl;
                    cin >> selection;
                    if (selection == 'Y' || selection == 'y') {
                        g.generateRandomEdge(allWeights);
                    }
                    else {
                        break;
                    }
                }
                cin.get();
                cin.get();
            }
            else if (choice == 4) {
                int origin, destination;
                cout << "Please enter your departure point" << endl;
                cin >> origin;
                cout << "Please enter your arrival point" << endl;
                cin >> destination;
            }
        }
    } while (choice != 8);
  
  
  
    while (!g.DFS()) {
       cout << "Graph doesn't contain cycle" << endl;
       
       g.generateRandomEdge(allWeights);
    }
    cout << "Graph is cyclic" << endl;
    g.toString();

    g.dijkstraDist(allWeights, 1, 3);

   
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

void MainMenu() {
    system("CLS");
    cout << "***********************************Graph Traversal********************************************" << endl;
    cout << "Main Menu: " << endl;
    cout << "Please select your choice: " << endl;
    cout << "1. Display graph" << endl;
    cout << "2: Check Strongly Connected" << endl;
    cout << "3: Check Cycle Detection" << endl;
    cout << "4: Find Shortest Path" << endl;
    cout << "5: Reset Graph" << endl;
    cout << "6: Add Edge" << endl;
    cout << "7: Remove Edge" << endl;
    cout << "8: Exit" << endl;
    cout << "Your choice: ";

}

bool checkStrong(Graph& g, int V) {
    Graph inverse(V);

    if (g.isSC()) {
        inverse.getTranspose(g);
        if (inverse.isSC()) {
            return true;
        }
        else {
            return false;
        }
    }
    return false;
}
