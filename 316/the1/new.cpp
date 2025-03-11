#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;


int heuristic(const vector<int> &vec)
{
    int wrongCount = 0;
    if (vec[0] - 1 != 0)
    {
        wrongCount++;
    }

    if (vec[vec.size()-1] != vec.size())
    {
        wrongCount++;
    }
    


    for (int i = 0; i < vec.size()-1; i++){
        if((vec[i] + 1 == vec[i+1]) || (vec[i] - 1 == vec[i+1])){
            continue;
        }
        else{
            wrongCount++;
        }
    }
    return ceil(wrongCount / 2.0);
}

bool flag = false;

// Return true if the given state is the goal state
bool is_goal(const vector<int>& state) {
    for (int i = 0; i < state.size(); i++) {
        if (state[i] != i + 1) return false;
    }
    flag = true;
    return true;
}

// Reverse implementation
void reverse2(vector<int> &vec, int i, int j)
{
    int temp;
    while(i < j){
        temp = vec[i];
        vec[i] = vec[j];
        vec[j] = temp;
        i++;
        j--;
    }
}

int dfs(vector<int> &state, int depth_limit, int depth, vector<pair<int, int>> &path)
{   
    if (flag) return depth;
    if (is_goal(state)) return depth;
    int h = heuristic(state);
    if (depth + h > depth_limit) return numeric_limits<int>::max();  // Prune the search if the f-value is greater than the depth limit
    
    int moves = numeric_limits<int>::max();
    for (int i = 0; i < state.size(); i++) {
        for (int j = i + 1; j < state.size(); j++) {
            vector<int> child_state = state;

            //reverse(child_state.begin() + i - 1, child_state.begin() + j);
            reverse2(child_state, i, j);
            path.push_back(make_pair(i, j));
            int child_moves = dfs(child_state, depth_limit, depth + 1, path);
            if (flag) return child_moves;
            if (child_moves < moves) moves = child_moves;
            path.pop_back();
        }
    }
    return moves;
}


int main()
{   
    int start_time = clock();

    int n;
    vector<int> vec = {};

    cin >> n;

    for (int i = 0; i < n; i++){
        int temp;
        cin >> temp;
        vec.push_back(temp);
    }

    n = vec.size();

    int minMove = n * (n - 1) / 2;
    vector<pair<int, int>> minPath;
    vector<pair<int, int>> path;
    int limit = 0;

    while(true){

        int numMoves = dfs(vec, limit, 0, path);

        if(numMoves < minMove){
            minMove = numMoves;
            minPath = path;
        }

        if(minMove == 0 || flag)
            break;

        limit++;
        path.clear();
    }

    cout << minMove << endl;

    for (int i = 0; i < minPath.size(); i++){
        cout << minPath[i].first << ' ' << minPath[i].second << endl;
    }

    int end_time = clock();
    
    // Print the time taken by the program as seconds
    cout << "Time taken: " << (end_time - start_time) / double(CLOCKS_PER_SEC) << " seconds" << endl;

    return 0;
}
