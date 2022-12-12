#include <bits/stdc++.h>
#include <fstream>
#include <string>
#include <queue>
using namespace std;

int height(char c){
    if (c == 'S'){
        return 1;
    }
    if (c == 'E'){
        return 26;
    }
    return c - 'a' + 1;
}
typedef struct edge{
    int row;
    int col;
    int total_path;
}edge;

int min_path(vector<string> &grid, int row, int col, pair<int, int> start, pair<int, int> end){
    int n = grid.size();
    int m = grid[0].size();
    vector<vector<int>> visited(n, vector<int>(m, 0));
    queue<edge> q;
    q.push({start.first, start.second, 0});
    visited[start.first][start.second] = 1;
    while(!q.empty()){
        edge curr = q.front();
        q.pop();
        if(curr.row == end.first && curr.col == end.second){
            return curr.total_path;
        }
        int h = height(grid[curr.row][curr.col]);
        if (curr.row - 1 >= 0 && !visited[curr.row - 1][curr.col] && height(grid[curr.row - 1][curr.col]) <= h + 1){
            q.push({curr.row - 1, curr.col, curr.total_path + 1});
            visited[curr.row - 1][curr.col] = 1;
        }
        if (curr.row + 1 < n && !visited[curr.row + 1][curr.col] && height(grid[curr.row + 1][curr.col]) <= h + 1){
            q.push({curr.row + 1, curr.col, curr.total_path + 1});
            visited[curr.row + 1][curr.col] = 1;
        }
        if (curr.col - 1 >= 0 && !visited[curr.row][curr.col - 1] && height(grid[curr.row][curr.col - 1]) <= h + 1){
            q.push({curr.row, curr.col - 1, curr.total_path + 1});
            visited[curr.row][curr.col - 1] = 1;
        }
        if (curr.col + 1 < m && !visited[curr.row][curr.col + 1] && height(grid[curr.row][curr.col + 1]) <= h + 1){
            q.push({curr.row, curr.col + 1, curr.total_path + 1});
            visited[curr.row][curr.col + 1] = 1;
        }
    }
    return -1;
}

int min_path2(vector<string> &grid, int row, int col, pair<int, int> start, pair<int, int> end){
    int n = grid.size();
    int m = grid[0].size();
    vector<vector<int>> visited(n, vector<int>(m, 0));
    queue<edge> q;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if (height(grid[i][j]) == 1){
                q.push({i, j, 0});
                visited[i][j] = 1;
            }
        }
    }
    while(!q.empty()){
        edge curr = q.front();
        q.pop();
        if(curr.row == end.first && curr.col == end.second){
            return curr.total_path;
        }
        int h = height(grid[curr.row][curr.col]);
        if (curr.row - 1 >= 0 && !visited[curr.row - 1][curr.col] && height(grid[curr.row - 1][curr.col]) <= h + 1){
            q.push({curr.row - 1, curr.col, curr.total_path + 1});
            visited[curr.row - 1][curr.col] = 1;
        }
        if (curr.row + 1 < n && !visited[curr.row + 1][curr.col] && height(grid[curr.row + 1][curr.col]) <= h + 1){
            q.push({curr.row + 1, curr.col, curr.total_path + 1});
            visited[curr.row + 1][curr.col] = 1;
        }
        if (curr.col - 1 >= 0 && !visited[curr.row][curr.col - 1] && height(grid[curr.row][curr.col - 1]) <= h + 1){
            q.push({curr.row, curr.col - 1, curr.total_path + 1});
            visited[curr.row][curr.col - 1] = 1;
        }
        if (curr.col + 1 < m && !visited[curr.row][curr.col + 1] && height(grid[curr.row][curr.col + 1]) <= h + 1){
            q.push({curr.row, curr.col + 1, curr.total_path + 1});
            visited[curr.row][curr.col + 1] = 1;
        }
    }
    return -1;
}


int main(){
    fstream file;
    file.open("input.txt", ios::in);
    pair<int,int> start, end;
    vector<string> grid;
    string line;
    while(getline(file, line)){
        grid.push_back(line);
    }
    for(int i = 0; i < grid.size(); i++){
        for(int j = 0; j < grid[i].size(); j++){
            if(grid[i][j] == 'S'){
                start = {i, j};
            }
            if(grid[i][j] == 'E'){
                end = {i, j};
            }
        }
    }
    //Find the shortest path between start and end
    //BFS
    cout << "Part 1: " << min_path(grid, grid.size(), grid[0].size(), start, end) << endl;
    cout << "Part 2: " << min_path2(grid, grid.size(), grid[0].size(), start, end) << endl;
    return 0;
}