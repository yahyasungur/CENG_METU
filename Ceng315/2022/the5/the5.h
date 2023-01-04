#ifndef HEADER_FILE
#define HEADER_FILE

#include <vector>
#include <iostream>

using namespace std;

struct Room {
        int id;
        char content;
        vector<Room*> neighbors;
};

vector<int> maze_trace(vector<Room*> maze);

#endif