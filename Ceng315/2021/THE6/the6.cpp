//#include "the6.h"
#include <climits>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <utility>
#include <vector>


using namespace std;

vector<int> result;

class Graph
{
    int V;
    vector<int> *adj;
    bool isCyclicUtil(int v, bool visited[], bool *rs);
public:
    Graph(int V);
    void addEdge(int v, int w);
    bool isCyclic();
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

bool Graph::isCyclicUtil(int v, bool visited[], bool *recStack)
{
    if(visited[v] == false)
    {

        visited[v] = true;
        recStack[v] = true;


        vector<int>::iterator i;
        for(i = adj[v].begin(); i != adj[v].end(); ++i)
        {
            if ( !visited[*i] && isCyclicUtil(*i, visited, recStack) ){
                result.push_back(v);
                return true;
            }
            else if (recStack[*i]){
                result.push_back(v);
                return true;
            }

        }

    }
    recStack[v] = false;
    return false;
}

bool Graph::isCyclic()
{

    bool *visited = new bool[V];
    bool *recStack = new bool[V];
    for(int i = 0; i < V; i++)
    {
        visited[i] = false;
        recStack[i] = false;
    }

    for(int i = 0; i < V; i++)
        if (isCyclicUtil(i, visited, recStack))
            return true;

    return false;
}

int find2(std::vector<int> racers, int number){
  for (int i = 0; i < (int)racers.size(); i++){
    if (racers[i] == number){
      return i;
    }
  }
  return -1;
}

int number_of_occurence_zero_racer(std::vector<std::pair<int, int>> updates, std::vector<int> racers){
  std::vector<int> occurances;
  for (int i = 0; i < (int)racers.size(); i++){
    int number = 0;
    for (int j = 0; j < (int)updates.size(); j++){
      if (racers[i] == updates[j].second){
        number++;
      }
    }
    occurances.push_back(number);
  }

  int min = (int)updates.size();
  int index = 0;
  for (int i = 0; i < (int)occurances.size(); i++){
    if (occurances[i] < min){
      min = occurances[i];
      index = i;
    }
  }

  return racers[index];
}

std::pair<bool, std::vector<int>> RaceResult(int N, std::vector<std::pair<int, int>> updates) {
  int M = (int)updates.size();
  bool possible = true;
  std::vector<int> loop;

  Graph g(N);

  for (int i = 0; i < M; i++){
    g.addEdge(updates[i].first,updates[i].second);
  }
  

  if(g.isCyclic()) {
      for (int i = (int)result.size()-1; i >= 0 ; i--){
          loop.push_back(result[i]);
      }
      loop.push_back(loop[0]);
      possible = false;    
      return {false,loop};
  }
  

  // finding all racers who are in announcements
  std::vector<int> racers;
  for (int i = 0; i < M; i++){
    if (find2(racers,updates[i].first) == -1){
      racers.push_back(updates[i].first);
    }
    if (find2(racers,updates[i].second) == -1){
      racers.push_back(updates[i].second);
    }
  }
  //--------------------------------------------

  int size = (int)racers.size();
  int size2 = size;
  for (int i = 0; i < size2; i++){
    int racer = number_of_occurence_zero_racer(updates,racers);
    result.push_back(racer);
    

    for (int j = 0; j < size ; j++){
      if (racer == racers[j]){
        racers.erase(racers.begin()+j);
        size--;
        break;
      }
    }
    
    for (int j = 0; j < M; j++){
      if (racer == updates[j].first){
        updates.erase(updates.begin()+j);
        M--;
        j--;
      }
    }
  }

  for (int i = 0; i < N; i++){
    if (find2(result,i) == -1){
      result.push_back(i);
    }
  }
  

  return {possible,result};
}
















int main(){
  std::vector<std::pair<int,int>> updates = {{0, 33}, {0, 57}, {0, 69}, {1, 65}, {1, 12}, {1, 60}, {2, 30}, {2, 44}, {3, 43}, {3, 16}, {4, 33}, {5, 14}, {5, 26}, {5, 52}, {6, 49}, {6, 58}, {6, 7}, {7, 52}, {8, 5}, {8, 23}, {9, 61}, {9, 48}, {9, 7}, {9, 45}, {10, 76}, {11, 19}, {12, 46}, {12, 66}, {13, 29}, {13, 31}, {13, 63}, {13, 61}, {14, 22}, {14, 3}, {15, 10}, {15, 66}, {16, 43}, {16, 69}, {16, 45}, {17, 59}, {17, 43}, {17, 62}, {18, 26}, {18, 35}, {19, 36}, {20, 43}, {20, 58}, {20, 24}, {21, 72}, {21, 68}, {22, 2}, {22, 77}, {23, 5}, {23, 36}, {23, 22}, {24, 18}, {25, 47}, {25, 54}, {25, 31}, {27, 42}, {29, 11}, {30, 34}, {31, 74}, {31, 54}, {31, 69}, {32, 63}, {32, 77}, {33, 29}, {33, 28}, {33, 1}, {35, 69}, {36, 71}, {36, 7}, {37, 20}, {37, 69}, {39, 15}, {39, 42}, {41, 10}, {41, 50}, {41, 65}, {41, 36}, {41, 59}, {42, 17}, {43, 70}, {43, 77}, {44, 69}, {44, 65}, {46, 74}, {46, 10}, {46, 5}, {46, 53}, {46, 24}, {47, 68}, {48, 54}, {48, 38}, {49, 72}, {49, 54}, {49, 27}, {50, 57}, {51, 25}, {51, 26}, {53, 73}, {54, 28}, {55, 32}, {56, 63}, {56, 49}, {56, 50}, {56, 31}, {56, 12}, {56, 78}, {57, 44}, {58, 48}, {58, 51}, {58, 43}, {59, 64}, {59, 37}, {60, 12}, {60, 79}, {60, 22}, {61, 37}, {62, 78}, {62, 15}, {62, 35}, {63, 47}, {63, 6}, {63, 12}, {63, 18}, {63, 57}, {64, 71}, {64, 21}, {64, 19}, {64, 29}, {64, 18}, {66, 79}, {67, 35}, {67, 63}, {68, 26}, {70, 42}, {70, 40}, {71, 3}, {72, 7}, {72, 44}, {72, 46}, {72, 40}, {72, 9}, {73, 9}, {73, 30}, {73, 2}, {74, 28}, {74, 71}, {75, 0}, {75, 16}, {76, 58}, {76, 45}, {76, 5}, {76, 47}, {78, 1}, {78, 58}, {78, 39}, {79, 49}};
  int N = 80;
  std::pair<bool, std::vector<int>> result;

  result = RaceResult(N, updates);
  bool is_there_loop = result.first;
  std::vector<int> result_vector = result.second;

  int size = (int)result_vector.size();

  std::cout<<"{"<< is_there_loop << " [";
  for (int i = 0; i < size; i++){
    printf(" %d",result_vector[i]);
  }
  printf("]}\n");
  

  return 0;
}
