#include <bits/stdc++.h>
#include <fstream>
#include <utility>
using namespace std;

class curr_s{
    public:
    int i;
    int j;
    int state_min;
    bool operator<(const curr_s &other) const{
        if (i == other.i){
            if (j == other.j){
                return state_min < other.state_min;
            }
            return j < other.j;
        }
        return i < other.i;
    }
};

int manhattan(int x1,int y1, int x2,int y2){
    return abs(x1 - x2) + abs(y1 - y2);
}

void print(map<pair<int, int>, vector<char>> coords,vector<string> path){
    for (int i = 0; i < path.size(); i++){
        for (int j = 0; j < path[i].size(); j++){
            if (coords[{i, j}].size() == 1){
                cout << coords[{i, j}][0];
            }
            else if (coords[{i, j}].size() > 1){
                cout << coords[{i, j}].size();
            }
            else{
                cout << path[i][j];
            }
        }
        cout << endl;
    }
    cout << endl;
}

void p_move(map<pair<int, int>, vector<char>> &coords,vector<string> &path){
    map<pair<int ,int>, vector<char>> n_pth;
    for (auto &[src, points]: coords){
        auto &[i ,j] = src;
        for(auto &dir: points){
            switch (dir){
                case '^':
                    n_pth[path[i - 1][j] == '#' ? make_pair(static_cast<int>(path.size()) - 2, j): make_pair(i - 1, j)].push_back(dir);
                    break;
                case 'v':
                    n_pth[path[i + 1][j] == '#' ? make_pair(1, j): make_pair(i + 1, j)].push_back(dir);
                    break;
                case '<':
                    n_pth[path[i][j - 1] == '#' ? make_pair(i, static_cast<int>(path[i].size()) - 2): make_pair(i, j - 1)].push_back(dir);
                    break;
                case '>':
                    n_pth[path[i][j + 1] == '#' ? make_pair(i, 1): make_pair(i, j + 1)].push_back(dir);
                    break;
            }
        }
    }
    coords = n_pth;
}



int main(){
    string line;
    fstream file;
    file.open("input.txt", ios::in);
    map<pair<int, int>, vector<char>> coords;
    vector<string> path;
    while(getline(file, line)){
        path.push_back(line);
    }
    for(int i = 0; i < path.size(); i++){
        for(int j = 0; j < path[i].size(); j++){
            if (path[i][j] == '<' || path[i][j] == '>' || path[i][j] == '^' || path[i][j] == 'v'){
                coords[{i, j}].push_back(path[i][j]);
                path[i][j] = '.';
            }
        }
    }
    /*
    int turn = 0;
    while(turn < 10){
        p_move(coords, path);
        print(coords, path);
        turn++;
    }
    */
   vector<map<pair<int, int>, vector<char>>> state;
   state.push_back(coords);
   set<curr_s> visited;
   queue<curr_s> q;
    q.push({0, 1, 0});
    int min_min = INT_MAX;
    while(!q.empty()){
        auto [i, j, state_min] = q.front();
        q.pop();
        //cout << i << " " << j << endl;
        if (state_min + manhattan(i,j,path.size() - 1,path[i].size() - 2) > min_min){
            continue;
        }
        if (visited.find({i, j, state_min}) != visited.end()){
            continue;
        }
        if (i == path.size() - 1 && j == path[i].size() - 2){
            min_min = min(min_min, state_min);
            //cout << min_min << endl;
            continue;
        }
        visited.insert({i, j, state_min});
        int next_state = state_min + 1;
        map<pair<int, int>, vector<char>> n_state;
        //cout << state_min << " " << next_state << endl;
        if (next_state >= state.size()){
            n_state = state[state_min];
            p_move(n_state, path);
            state.push_back(n_state);
        }
        else{
            n_state = state[next_state];
        }
        //print(n_state, path);
        //cout << i << " " << j << endl;
        bool wait = true;
        if (i != 0 && path[i - 1][j] != '#' && n_state.find({i - 1, j}) == n_state.end()){
            q.push({i - 1, j, next_state});
            //cout << "Up" << endl;
            wait = false;
        }
        if (i != path.size() - 1 && path[i + 1][j] != '#' && n_state.find({i + 1, j}) == n_state.end()){
            q.push({i + 1, j, next_state});
            //cout << "Down" << endl;
            wait = false;
        }
        if (j != 0 && path[i][j - 1] != '#' && n_state.find({i, j - 1}) == n_state.end()){
            q.push({i, j - 1, next_state});
            //cout << "Left" << endl;
            wait = false;
        }
        if (j != path[i].size() - 1 && path[i][j + 1] != '#' && n_state.find({i, j + 1}) == n_state.end()){
            q.push({i, j + 1, next_state});
            //cout << "Right" << endl;
            wait = false;
        }
        if (n_state.find({i, j}) == n_state.end()){
            q.push({i, j, next_state});
            //cout << "Stay" << endl;
            wait = false;
        }
    }
    cout <<"Part 1: " << min_min << endl;
    int min_min2 = INT_MAX;
    q.push({static_cast<int>(path.size()) - 1, static_cast<int>(path[path.size() - 1].size()) - 2, min_min});
    visited.clear();
    while(!q.empty()){
        auto [i, j, state_min] = q.front();
        q.pop();
        //cout << i << " " << j << endl;
        if (state_min + manhattan(i, j, 0, 1) > min_min2){
            continue;
        }
        if (visited.find({i, j, state_min}) != visited.end()){
            continue;
        }
        if (i == 0 && j == 1){
            min_min2 = min(min_min2, state_min);
            //cout << min_min2 << endl;
            continue;
        }
        visited.insert({i, j, state_min});
        int next_state = state_min + 1;
        map<pair<int, int>, vector<char>> n_state;
        //cout << state_min << " " << next_state << endl;
        if (next_state >= state.size()){
            n_state = state[state_min];
            p_move(n_state, path);
            state.push_back(n_state);
        }
        else{
            n_state = state[next_state];
        }
        //print(n_state, path);
        //cout << i << " " << j << endl;
        bool wait = true;
        if (i != 0 && path[i - 1][j] != '#' && n_state.find({i - 1, j}) == n_state.end()){
            q.push({i - 1, j, next_state});
            //cout << "Up" << endl;
            wait = false;
        }
        if (i != path.size() - 1 && path[i + 1][j] != '#' && n_state.find({i + 1, j}) == n_state.end()){
            q.push({i + 1, j, next_state});
            //cout << "Down" << endl;
            wait = false;
        }
        if (j != 0 && path[i][j - 1] != '#' && n_state.find({i, j - 1}) == n_state.end()){
            q.push({i, j - 1, next_state});
            //cout << "Left" << endl;
            wait = false;
        }
        if (j != path[i].size() - 1 && path[i][j + 1] != '#' && n_state.find({i, j + 1}) == n_state.end()){
            q.push({i, j + 1, next_state});
            //cout << "Right" << endl;
            wait = false;
        }
        if (n_state.find({i, j}) == n_state.end()){
            q.push({i, j, next_state});
            //cout << "Stay" << endl;
            wait = false;
        }
    }
    int min_min3 = INT_MAX;
    q.push({0, 1, min_min2});
    visited.clear();
    while(!q.empty()){
        auto [i, j, state_min] = q.front();
        q.pop();
        //cout << i << " " << j << endl;
        if (state_min  + manhattan(i , j, path.size() - 1, path[i].size() - 2)> min_min3){
            continue;
        }
        if (visited.find({i, j, state_min}) != visited.end()){
            continue;
        }
        if (i == path.size() - 1 && j == path[i].size() - 2){
            min_min3 = min(min_min3, state_min);
            //cout << min_min3 << endl;
            continue;
        }
        visited.insert({i, j, state_min});
        int next_state = state_min + 1;
        map<pair<int, int>, vector<char>> n_state;
        //cout << state_min << " " << next_state << endl;
        if (next_state >= state.size()){
            n_state = state[state_min];
            p_move(n_state, path);
            state.push_back(n_state);
        }
        else{
            n_state = state[next_state];
        }
        //print(n_state, path);
        //cout << i << " " << j << endl;
        bool wait = true;
        if (i != 0 && path[i - 1][j] != '#' && n_state.find({i - 1, j}) == n_state.end()){
            q.push({i - 1, j, next_state});
            //cout << "Up" << endl;
            wait = false;
        }
        if (i != path.size() - 1 && path[i + 1][j] != '#' && n_state.find({i + 1, j}) == n_state.end()){
            q.push({i + 1, j, next_state});
            //cout << "Down" << endl;
            wait = false;
        }
        if (j != 0 && path[i][j - 1] != '#' && n_state.find({i, j - 1}) == n_state.end()){
            q.push({i, j - 1, next_state});
            //cout << "Left" << endl;
            wait = false;
        }
        if (j != path[i].size() - 1 && path[i][j + 1] != '#' && n_state.find({i, j + 1}) == n_state.end()){
            q.push({i, j + 1, next_state});
            //cout << "Right" << endl;
            wait = false;
        }
        if (n_state.find({i, j}) == n_state.end()){
            q.push({i, j, next_state});
            //cout << "Stay" << endl;
            wait = false;
        }
    }
    cout << "Part 2: " << min_min3 << endl;
}