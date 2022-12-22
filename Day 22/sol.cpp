#include <bits/stdc++.h>
#include <fstream>
using namespace std;





void rotate(char &dir, char &rotation){
    //if rotation is 'L' rotate 90 degrees counter-clockwise
    //if rotation is 'R' rotate 90 degrees clockwise
    if(rotation == 'L'){
        if(dir == 'N') dir = 'W';
        else if(dir == 'W') dir = 'S';
        else if(dir == 'S') dir = 'E';
        else if(dir == 'E') dir = 'N';
    }
    else if(rotation == 'R'){
        if(dir == 'N') dir = 'E';
        else if(dir == 'E') dir = 'S';
        else if(dir == 'S') dir = 'W';
        else if(dir == 'W') dir = 'N';
    }
}


bool move(vector<string> &path, int &x, int &y, char &dir){
    int tmp_x = x, tmp_y = y;
    bool moved = false;
    pair<int, int> dir_vec;
    switch(dir){
        case 'N':
            dir_vec = {-1, 0};
            break;
        case 'S':
            dir_vec = {1, 0};
            break;
        case 'E':
            dir_vec = {0, 1};
            break;
        case 'W':
            dir_vec = {0, -1};
            break;
    }
    bool x_border = tmp_x == 0 || tmp_x == path[tmp_y].size() - 1;
    bool y_border = tmp_y == 0 || tmp_y == path.size() - 1;
    if (x_border || y_border || path[tmp_y + dir_vec.first][tmp_x + dir_vec.second] == ' '){
        tmp_x = (tmp_x + dir_vec.second + path[tmp_y].size()) % path[tmp_y].size();
        tmp_y = (tmp_y + dir_vec.first + path.size()) % path.size();
        while (path[tmp_y][tmp_x] == ' '){
            tmp_x = (tmp_x + dir_vec.second + path[tmp_y].size()) % path[tmp_y].size();
            tmp_y = (tmp_y + dir_vec.first + path.size()) % path.size();
        }
    }
    else{
        tmp_x += dir_vec.second;
        tmp_y += dir_vec.first;
    }
    if (path[tmp_y][tmp_x] == '.'){
        x = tmp_x;
        y = tmp_y;
    }
    //cout << "Moved to " << tmp_x << " " << tmp_y << endl;
    return path[tmp_y][tmp_x] == '.';
}





int main(){
    fstream file;
    file.open("input.txt", ios::in);
    string line;
    vector<string> path;
    int m_len = 0;
    while (true){
        getline(file, line);
        m_len = max(m_len, (int)line.size());
        if (line == "") break;
        path.push_back(line);
    }
    for (auto &line: path){
        while (line.size() < m_len){
            line += ' ';
        }
    }
    string walking;
    getline(file, walking);
    //cout << walking << endl;
    vector<string> parse;
    string temp;
    for(int i = 0; i < walking.size(); i++){
        if (walking[i] == 'L' || walking[i] == 'R'){
            // push walking[i] into parse
            parse.push_back(temp);
            temp = "";
            temp += walking[i];
            parse.push_back(temp);
            temp = "";
        }
        else{
            temp += walking[i];
        }
    }
    if (temp != ""){
        parse.push_back(temp);
    }
    int start_x = 0, start_y = 0;
    char curr_dir = 'E';
    for(int i = 0; i < path[0].size(); i++){
        if(path[0][i] == '.'){
            start_x = i;
            break;
        }
    }
    int vv;
    //cout << start_x << " " << start_y << endl;
    for(auto &command: parse){
        //cout << command << endl;
        if (command == "L" || command == "R"){
            rotate(curr_dir, command[0]);
        }
        else{
            int steps = stoi(command);
            //cout << "Direction: " << curr_dir << endl;
            while (steps){
                if (!move(path, start_x, start_y, curr_dir)){
                    //cout << "No more moves" << endl;
                    break;
                }
                else{
                    //cout << "Moved to " << start_x << " " << start_y << endl;
                }
                steps--;
            }
            //cin >> vv;
        }
    }
    start_x++;
    start_y++;
    int result = 0;
    switch(curr_dir){
        case 'N':
            result = 3;
            break;
        case 'S':
            result = 1;
            break;
        case 'E':
            result = 0;
            break;
        case 'W':
            result = 2;
            break;
    }
    result += start_y * 1000 + 4 * start_x;
    cout <<"Part 1:" << result << endl;
    /*
    For my input
    Sides:
        **
        *
       **
       *
    So I solve part 2 by hand :(
    */
}