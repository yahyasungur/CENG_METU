#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

bool flag = false;

// Heuristic function to estimate the distance of the current state from the goal state
int heuristic(const vector<int> &vec)
{
    int wrongCount = 0;

    // Check if the first element is in the correct position
    if (vec[0] - 1 != 0)
    {
        wrongCount++;
    }

    // Check if the last element is in the correct position
    if (vec[vec.size()-1] != (int)vec.size())
    {
        wrongCount++;
    }

    // Check if each element is adjacent to the next or the previous element
    for (unsigned i = 0; i < vec.size()-1; i++){
        if((vec[i] + 1 == vec[i+1]) || (vec[i] - 1 == vec[i+1])){
            continue;
        }
        else{
            wrongCount++;
        }
    }
    // Divide by 2 and round up to get an admissible heuristic
    return ceil(wrongCount / 2.0);
}

// Return true if the given state is the goal state
bool is_goal(const vector<int>& state) {
    for (unsigned i = 0; i < state.size(); i++) {
        if ((unsigned)state[i] != i + 1) return false;
    }
    flag = true;
    return true;
}

// Reverse the order of elements in the given vector between indices i and j (inclusive)
void reverse(vector<int> &vec, int i, int j)
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

// Recursive depth-first search function to find the optimal solution to the problem
int dfs(vector<int> &state, int depth_limit, int depth, vector<pair<int, int>> &path)
{   
    // Check if the goal state has been reached
    if (flag) return depth;
    if (is_goal(state)) return depth;
    // Compute the heuristic value of the current state
    int h = heuristic(state);
    // Check if the depth limit has been exceeded
    if (depth + h > depth_limit) return numeric_limits<int>::max(); // pruning
    
    int moves = numeric_limits<int>::max();
    for (unsigned i = 0; i < state.size(); i++) {
        for (unsigned j = i + 1; j < state.size(); j++) {
            vector<int> child_state = state;
            // Reverse the order of elements between indices i and j
            reverse(child_state, i, j);
            // Add the move to the path
            path.push_back(make_pair(i, j));
            // Recursively search for a solution from the new state
            int child_moves = dfs(child_state, depth_limit, depth + 1, path);
            // If the goal state has been found, return the number of moves to reach it
            if (flag){
                state = child_state;
                return child_moves;
            }
            // Keep track of the minimum number of moves found so far
            if (child_moves < moves) moves = child_moves;
            // Remove the last move from the path
            path.pop_back();
        }
    }
    // Return the minimum number of moves found
    return moves;
}


int main()
{   
    int n;
    vector<int> vec = {};

    // Read the initial state from standard input until EOF
    while (cin >> n) {
        vec.push_back(n);
    }

    n = vec.size();
    // The minimum number of moves required to solve the problem
    int minMove = n * (n - 1) / 2;
    vector<pair<int, int>> minPath;
    vector<pair<int, int>> path;
    int limit = 0;

    while (true) {
        int numMoves = dfs(vec, limit, 0, path);

        // Keep track of the minimum number of moves found so far
        if (numMoves < minMove) {
            minMove = numMoves;
            minPath = path;
        }

        // If the goal state has been found, break out of the loop
        if (minMove == 0 || flag) break;

        limit++;
        path.clear();
    }

    cout << minMove << endl;

    for (unsigned i = 0; i < minPath.size(); i++) {
        cout << minPath[i].first + 1 << ' ' << minPath[i].second + 1 << endl;
    }

    return 0;
}
