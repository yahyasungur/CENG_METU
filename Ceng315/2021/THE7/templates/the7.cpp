#include "the7.h"

using namespace std;

int **graph;
vector<int> path;

int minDistance(int dist[], bool sptSet[], int V)
{
    int min = INT_MAX, min_index = 0;

    for (int v = 0; v < V; v++)
    {
        if (sptSet[v] == false && dist[v] <= min)
        {
            min = dist[v], min_index = v;
        }
    }

    return min_index;
}

void printPath(int parent[], int j)
{
    if(parent[j] == -1)
        return;

    printPath(parent, parent[j]);
    path.push_back(j);
}

int printSolution(int dist[], int n, int parent[], int src, int V, int d){
    int min = INT_MAX;

    path.push_back(src);
    printPath(parent, d);

    if(dist[d] < min && dist[d] != 0)
    {
        min = dist[d];
    }
  
  return min;
}

int dijkstra(int src, int V, int d){
    int dist[V];
    bool sptSet[V];
    int parent[V];

    parent[src] = -1;
    for (int i = 0; i < V; i++)
    {
        dist[i] = INT_MAX;
        sptSet[i] = false;
    }

    dist[src] = 0;

    for (int count = 0; count < V-1; count++)
    {
        int u = minDistance(dist, sptSet, V);

        sptSet[u] = true;

        for (int v = 0; v < V; v++)
        {
            if (!sptSet[v] && graph[u][v] && dist[u]+graph[u][v] < dist[v])
            {
                dist[v] = dist[u] + graph[u][v];
                parent[v]  = u;
            }
        }
    }

    return printSolution(dist, V, parent, src, V, d);
}

void FindRoute(int n, std::vector<Road> roads, int s, int d, int x, int y) {
  std::vector<int> result_path;
  int cost = 0;

  graph = (int**)malloc(n*sizeof(int*));
  for (int i = 0; i < n; i++){
    graph[i] = (int*)malloc(n*sizeof(int));
  }

  for (int i = 0; i < n; i++){
    for (int j = 0; j < n; j++){
      graph[i][j] = 0;
    }
  }
  
  for (int i = 0; i < (int)roads.size(); i++){
    int time = roads[i].time;
    int left = roads[i].endpoints.first;
    int right = roads[i].endpoints.second;

    graph[left][right] = time;
    graph[right][left] = time;
  }

  int s_to_x = dijkstra(s,n,x);
  vector<int> path_s_to_x(path);
  path.clear();
  path.shrink_to_fit();

  int s_to_y = dijkstra(s,n,y);
  vector<int> path_s_to_y(path);
  path.clear();
  path.shrink_to_fit();

  int x_to_d = dijkstra(x,n,d);
  vector<int> path_x_to_d(path);
  path.clear();
  path.shrink_to_fit();

  int y_to_d = dijkstra(y,n,d);
  vector<int> path_y_to_d(path);
  path.clear();
  path.shrink_to_fit();

  int x_to_y = dijkstra(x,n,y);
  vector<int> path_x_to_y(path);
  path.clear();
  path.shrink_to_fit();

  if (s_to_x + x_to_y + y_to_d < s_to_y + x_to_y + x_to_d){
    cost = s_to_x + x_to_y + y_to_d;
    result_path = path_s_to_x;
    for (int i = 1; i < (int)path_x_to_y.size(); i++){
      result_path.push_back(path_x_to_y[i]);
    }
    for (int i = 1; i < (int)path_y_to_d.size(); i++){
      result_path.push_back(path_y_to_d[i]);
    }
  }
  else{
    cost = s_to_y + x_to_y + x_to_d;
    result_path = path_s_to_y;
    for (int i = (int)path_x_to_y.size()-2; i >=0 ; i--){
      result_path.push_back(path_x_to_y[i]);
    }
    for (int i = 1; i < (int)path_x_to_d.size(); i++){
      result_path.push_back(path_x_to_d[i]);
    }
  }

  for (int i = 0; i < n; i++){
    delete[] graph[i];
  }
  delete[] graph;

  std::cout << cost << " ";
  PrintRange(result_path.begin(), result_path.end());
  std::cout << std::endl;
}