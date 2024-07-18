
#include <iostream>
#include <vector>
#include <climits> // For INT_MAX
#include <set>
#include <cctype> // For isdigit() and toupper()

using namespace std;

int convertInputToIndex(char inputChar) {
    if (isdigit(inputChar)) {
        return inputChar - '0'; // Convert char digit to integer
    }
    inputChar = toupper(inputChar); // Standardize to uppercase
    if (inputChar >= 'A' && inputChar <= 'E') {
        return inputChar - 'A';
    }
    return -1; // Invalid input
}

int getMinDistanceVertex(const vector<int>& distances, const set<int>& processed) {
    int minDistance = INT_MAX, minIndex = -1; 
    for (int i = 0; i < distances.size(); ++i) {
        if (processed.find(i) == processed.end() && distances[i] < minDistance) {
            minDistance = distances[i];
            minIndex = i;
        }
    }
    return minIndex;
}

void displayShortestPath(const vector<int>& distances, int vertexCount, const vector<int>& predecessors, int source, int destination) {
    cout << "Vertex\t\tDistance from Source\tPath" << endl;
    vector<int> path;
    int currentNode = destination;

    while (predecessors[currentNode] != -1) {
        path.insert(path.begin(), currentNode);
        currentNode = predecessors[currentNode];
    }
    path.insert(path.begin(), source);

    cout << "Shortest path from " << source << " to " << destination << ": ";
    for (size_t i = 0; i < path.size(); ++i) {
        if (i > 0) cout << " -> ";
        cout << path[i];
    }
    cout << "\nTotal distance: " << distances[destination] << endl;
}

void performDijkstra(const vector<vector<pair<int, int>>>& adjacencyList, int startVertex, int endVertex) {
    int numVertices = adjacencyList.size();
    vector<int> distances(numVertices, INT_MAX);
    vector<int> predecessors(numVertices, -1);
    set<int> processedVertices;

    distances[startVertex] = 0;

    for (int count = 0; count < numVertices; ++count) {
        int currentVertex = getMinDistanceVertex(distances, processedVertices);
        if (currentVertex == -1) break;

        processedVertices.insert(currentVertex);

        for (const auto& neighbor : adjacencyList[currentVertex]) {
            int neighborVertex = neighbor.first;
            int weight = neighbor.second;
            if (processedVertices.find(neighborVertex) == processedVertices.end() && distances[currentVertex] != INT_MAX && distances[currentVertex] + weight < distances[neighborVertex]) {
                predecessors[neighborVertex] = currentVertex;
                distances[neighborVertex] = distances[currentVertex] + weight;
            }
        }
    }

    displayShortestPath(distances, numVertices, predecessors, startVertex, endVertex);
}

int main() {
    vector<vector<pair<int, int>>> graph = {
        {{1, 10}, {4, 3}},    // Adjacency list for vertex 0 (A)
        {{2, 2}, {0, 10}, {3, 4}, {4, 1}}, // Adjacency list for vertex 1 (B)
        {{1, 2}, {3, 9}, {4, 8}}, // Adjacency list for vertex 2 (C)
        {{1, 4}, {2, 9}, {4, 2}}, // Adjacency list for vertex 3 (D)
        {{0, 3}, {1, 1}, {2, 8}, {3, 2}}  // Adjacency list for vertex 4 (E)
    };

    string userInput;
    int startNode, endNode;

    cout << "Enter the starting node (A=0, B=1, C=2, D=3, E=4): ";
    cin >> userInput;
    startNode = convertInputToIndex(userInput[0]);

    cout << "Enter the ending node (A=0, B=1, C=2, D=3, E=4): ";
    cin >> userInput;
    endNode = convertInputToIndex(userInput[0]);

    if (startNode < 0 || endNode < 0 || startNode >= graph.size() || endNode >= graph.size()) {
        cout << "Invalid input. Please enter a value between A (or 0) and E (or 4)." << endl;
        return 1;
    }

    performDijkstra(graph, startNode, endNode);

    return 0;
}
