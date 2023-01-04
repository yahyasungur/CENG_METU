#include "the5.h"

using namespace std;

vector<int> path;
bool found = false;

class Graph {
    int numVertices;
    vector<int> *adjLists;
    bool *visited;

    public:
        Graph(int V);
        void addEdge(int src, int dest);
        void DFS(int vertex, vector<Room*> maze);
};

// Initialize graph
Graph::Graph(int vertices) {
    numVertices = vertices;
    adjLists = new vector<int>[vertices];
    visited = new bool[vertices];
}

// Add edges
void Graph::addEdge(int src, int dest) {
    adjLists[src].push_back(dest);
}

// DFS algorithm
void Graph::DFS(int vertex, vector<Room*> maze) {

    visited[vertex] = true;
    path.push_back(vertex);
    
    if (maze[vertex]->content == '*' && !found){
        found = true;
        return;
    }
    
    vector<int> adjList = adjLists[vertex];

    vector<int>::iterator i;
    for (i = adjList.begin(); i != adjList.end(); ++i){
        if (found){
            return;
        }
        if (!visited[*i]){
            DFS(*i, maze);
            path.push_back(vertex);
        }
    }
}

vector<int> maze_trace(vector<Room*> maze) {    
    Graph g(maze.size());
    vector<pair<int, int>> edges;
    for (size_t i = 0; i < maze.size(); i++){
        int id = maze[i]->id;
        for (size_t j = 0; j < maze[i]->neighbors.size(); j++){
            int neighbor_id = maze[i]->neighbors[j]->id;
            g.addEdge(id, neighbor_id);
        }
    }

    g.DFS(maze[0]->id, maze);

    return path;
}


