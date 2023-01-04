#include "the5.h"

using namespace std;

vector<int> path;
bool found = false;


class Graph
{
    int V;
    vector<int> *adj;
    void DFS_visit(int v, bool visited[], vector<Room*> maze);
public:
    Graph(int V);
    void addEdge(int v, int w);
    void DFS(int v, vector<Room*> maze);
};

Graph::Graph(int V)
{
    this->V = V;
    adj = new vector<int>[V];
}

void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w);
}

void Graph::DFS_visit(int v, bool visited[], vector<Room*> maze)
{
    visited[v] = true;
    if(found)
        return;
    path.push_back(v);
    if(maze[v]->content == '*'){
        found = true;
        return;
    }

    vector<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end();i++)
        {
            if(found)
                return;
            if (!visited[*i]){
                DFS_visit(*i, visited, maze);
                path.push_back(v);
            }
        }
}


void Graph::DFS(int v, vector<Room*> maze)
{
    // Mark all the vertices as not visited
    bool *visited = new bool[V];
    for (int i = 0; i < V; i++)
        visited[i] = false;


  DFS_visit(v, visited, maze);
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