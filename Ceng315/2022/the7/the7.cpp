#include "the7.h"

using namespace std;
#define INF 0x3f3f3f3f
vector<int> pathh;

typedef pair<int, int> iPair;

int NO_PARENT = -1;

class Graph {
	int V; // No. of vertices

	vector<pair<int, int> >* adj;

public:
	Graph(int V); // Constructor

	// function to add an edge to graph
	void addEdge(int u, int v, int w);

    void printPath(int currentVertex ,vector<int> parents);

	// prints shortest path from s
	pair<int,vector<int>> shortestPath(int src, int dest);
};

// Allocates memory for adjacency list
Graph::Graph(int V)
{
	this->V = V;
	adj = new vector<iPair>[V];
}

void Graph::addEdge(int u, int v, int w)
{
	adj[u].push_back(make_pair(v, w));
	adj[v].push_back(make_pair(u, w));
}

void Graph::printPath(int currentVertex, vector<int> parents)
{
	// Base case : Source node has
	// been processed
	if (currentVertex == NO_PARENT) {
		return;
	}
	printPath(parents[currentVertex], parents);
	// cout << currentVertex << " ";
    pathh.push_back(currentVertex);
}

// Prints shortest paths from src to all other vertices
pair<int,vector<int>> Graph::shortestPath(int src, int dest){
    // Create a priority queue to store vertices that
	priority_queue<iPair, vector<iPair>, greater<iPair> >pq;

	// Create a vector for distances and initialize all
	// distances as infinite (INF)
	vector<int> dist(V, INF);

	// Insert source itself in priority queue and initialize
	// its distance as 0.
	pq.push(make_pair(0, src));
	dist[src] = 0;

    // Parent array to store shortest path tree
	vector<int> parents(this->V);

    parents[src] = NO_PARENT;

	/* Looping till priority queue becomes empty (or all distances are not finalized) */
	while (!pq.empty()) {
		int u = pq.top().second;
		pq.pop();

		vector<pair<int, int> >::iterator i;
		for (i = adj[u].begin(); i != adj[u].end(); ++i) {
			// Get vertex label and weight of current
			// adjacent of u.
			int v = (*i).first;
			int weight = (*i).second;

			// If there is shorted path to v through u.
			if (dist[v] > dist[u] + weight) {
				// Updating distance of v
				dist[v] = dist[u] + weight;

                // Updating parent of v
                parents[v] = u;

				pq.push(make_pair(dist[v], v)); 
			}
		}
	}

    int distance = dist[dest];
    pathh.clear();
    printPath(dest, parents);
    
    return make_pair(distance, pathh);
}


void CanCatch(int n, std::vector<Road> roads, int s, int d, int x, int y, int l, int printPath) {
    // You can change these variables. These are here for demo only.
    std::vector<int> path;
    int cost = INT_MAX;
    string yes_no = "NO";
    string path_string = "IMPOSSIBLE";

    Graph g(n); // Create a graph with n vertices
    for (size_t i = 0; i < roads.size(); i++){
        g.addEdge(roads[i].buildings.first, roads[i].buildings.second,roads[i].time);
    }

    pair<int,vector<int>> result_s_x = g.shortestPath(s,x);
    pair<int,vector<int>> result_s_y = g.shortestPath(s,y);
    pair<int,vector<int>> result_s_d = g.shortestPath(s,d);
    pair<int,vector<int>> result_x_y = g.shortestPath(x,y);
    pair<int,vector<int>> result_x_d = g.shortestPath(x,d);
    pair<int,vector<int>> result_y_d = g.shortestPath(y,d);
    pair<int,vector<int>> result_y_x = g.shortestPath(y,x);

    if(result_s_x.first + result_x_y.first + result_y_d.first <= l ||
        result_s_y.first + result_y_x.first + result_x_d.first <= l){
        yes_no = "YES";
        path_string = "BOTH";

        if ((result_s_x.first + result_y_d.first) <= (result_s_y.first + result_x_d.first)){
            cost = result_s_x.first + result_x_y.first + result_y_d.first;
            path = result_s_x.second;
            path.insert(path.end(), result_x_y.second.begin(), result_x_y.second.end());
            path.insert(path.end(), result_y_d.second.begin(), result_y_d.second.end());
        }else{
            cost = result_s_y.first + result_y_x.first + result_x_d.first;
            path = result_s_y.second;
            path.insert(path.end(), result_y_x.second.begin(), result_y_x.second.end());
            path.insert(path.end(), result_x_d.second.begin(), result_x_d.second.end());
        }
    }
    else if (result_s_x.first + result_x_d.first <= l){
        yes_no = "YES";
        if(result_s_x.first + result_x_d.first < cost){
            path_string = "PRINTER";
            cost = result_s_x.first + result_x_d.first;
            path = result_s_x.second;
            path.insert(path.end(), result_x_d.second.begin(), result_x_d.second.end());
        }
    }
    else if (result_s_y.first + result_y_d.first <= l){
        yes_no = "YES";
        if(result_s_y.first + result_y_d.first < cost){
            path_string = "DORM";
            cost = result_s_y.first + result_y_d.first;
            path = result_s_y.second;
            path.insert(path.end(), result_y_d.second.begin(), result_y_d.second.end());
        }
    }
    else if (result_s_d.first <= l){
        yes_no = "YES";
        path_string = "DIRECTLY";
        if(result_s_d.first < cost){
            cost = result_s_d.first;
            path = result_s_d.second;
        }
    }
    else{
        cost = -1;
    }

    if (cost != -1){
        cout << yes_no << " " << path_string << " " <<  cost << "MINUTES" << endl;
    }
    else{
        cout << path_string << endl;
        return;
    }

    int old = path[0];
    for (size_t i = 1; i < path.size(); i++){
        if (path[i] == old){
            path.erase(path.begin() + i);
        }
        old = path[i];
    }

    if (printPath == 1){
        PrintRange(path.begin(), path.end());
    }
}
