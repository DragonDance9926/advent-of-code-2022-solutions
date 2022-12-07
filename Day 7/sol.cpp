#include <bits/stdc++.h>
#include <fstream>
#include <string>
using namespace std;
int main(){
    map<string, vector<string>> dirs;
    string curr_path = "";
    string line;
    fstream file;
    file.open("input.txt", ios::in);
    vector<string> commands;
    while (file.peek() != EOF){
        getline(file, line);
        commands.push_back(line);
    }
    file.close();
    int i = 0;
    while(i < commands.size()){
        string command = commands[i];
        //split command by space
        vector<string> split_command;
        string temp = "";
        for(int j = 0; j < command.size(); j++){
            if(command[j] == ' '){
                split_command.push_back(temp);
                temp = "";
            }
            else{
                temp += command[j];
            }
        }
        split_command.push_back(temp);
        if (split_command[0] == "$"){
            if (split_command[1] == "cd"){
                if (split_command[2] == ".."){
                    int pos = curr_path.find_last_of("/");
                    curr_path = curr_path.substr(0, pos);
                }
                else if (split_command[2] == "/"){
                    curr_path = "/";
                }
                else{
                    if (curr_path == "/"){
                        curr_path += split_command[2];
                    }
                    else{
                        curr_path += "/" + split_command[2];
                    }
                }
            }
        }
        else{
            dirs[curr_path].push_back(command);
        }
        i++;
    }


    //reverse iterate through dirs
    vector<string> dirs_l;
    for(auto it = dirs.rbegin(); it != dirs.rend(); it++){
        dirs_l.push_back(it->first);
    }
    sort(dirs_l.begin(), dirs_l.end(),greater<string>());
    unordered_map<string, int> dir_size;
    for(auto &dir: dirs_l){
        //cout << dir << endl;
        for(auto &command: dirs[dir]){
            vector<string> split_command;
            string temp = "";
            for(int j = 0; j < command.size(); j++){
                if(command[j] == ' '){
                    split_command.push_back(temp);
                    temp = "";
                }
                else{
                    temp += command[j];
                }
            }
            split_command.push_back(temp);
            if (split_command[0] == "dir"){
                string new_dir;
                if (dir == "/"){
                    new_dir = dir + split_command[1];
                }
                else{
                    new_dir = dir + "/" + split_command[1];
                }
                dir_size[dir] += dir_size[new_dir];
            }
            else{
                dir_size[dir] += stoi(split_command[0]);
            }
        }
    }
    int res = 0;
    for(auto &dir: dirs_l){
        //cout << dir << " " << dir_size[dir] << endl;
        if (dir_size[dir] <= 100000){
            res += dir_size[dir];
        }
    }
    cout << "Part 1: " << res << endl;
    int total = 70000000;
    int free = total - dir_size["/"];
    free = 30000000 - free;
    //cout << free << endl;
    res = INT_MAX;
    for(auto &dir: dirs_l){
        if (dir_size[dir] >= free){
            res = min(res, dir_size[dir]);
        }
    }
    cout << "Part 2: " << res << endl;
    return 0;
}