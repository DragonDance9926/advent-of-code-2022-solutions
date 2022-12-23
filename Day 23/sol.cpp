#include <bits/stdc++.h>
#include <fstream>
#include <utility>
using namespace std;
enum direction {NORTH, EAST, SOUTH, WEST};

pair<int ,int> mve(set<pair<int ,int>> &mp,map<pair<int ,int> ,vector<direction>> &order, pair<int, int> coor){
    //North
    auto [i ,j] = coor;
    bool nw = mp.find({i-1,j - 1}) == mp.end();
    bool n = mp.find({i-1,j}) == mp.end();
    bool ne = mp.find({i-1,j + 1}) == mp.end();
    //South
    bool sw = mp.find({i+1,j - 1}) == mp.end();
    bool s = mp.find({i+1,j}) == mp.end();
    bool se = mp.find({i+1,j + 1}) == mp.end();
    //East
    bool e = mp.find({i,j + 1}) == mp.end();
    // West
    bool w = mp.find({i,j - 1}) == mp.end();
    int k = 0;
    bool f = false;
    pair<int, int> next = {i,j};
    //cout << "Current: " << i << " " << j << endl;
    for(;!f && k < 4; k++){
        switch (order[coor][k]){
            case NORTH:
                //cout << "N";
                if (nw && n && ne){
                    //cout << "Moving North" << endl;
                    next = {i-1,j};
                    f = true;
                }
                break;
            case SOUTH:
                //cout << "S";
                if (sw && s && se){
                    //cout << "Moving South" << endl;
                    next = {i+1,j};
                    f = true;
                }
                break;
            case EAST:
                //cout << "E";
                if (e && ne && se){
                    //cout << "Moving East" << endl;
                    next = {i,j+1};
                    f = true;
                }
                break;
            case WEST:
                //cout << "W";
                if (w && nw && sw){
                    //cout << "Moving West" << endl;
                    next = {i,j-1};
                    f = true;
                }
                break;
        }
    }
    //cout << " " << i << " " << j << " ";
    k--;
    if (f){
        direction temp = order[coor][k];
        switch(temp){
            case NORTH:
                //cout << "N" << endl;
                break;
            case SOUTH:
                //cout << "S" << endl;
                break;
            case EAST:
                //cout << "E" << endl;
                break;
            case WEST:
                //cout << "W" << endl;
                break;
        }
        //rotate left once
    }
    else{
        //cout << "-" << endl;
    }
    //cout << "End" << endl;
    return next;
}

int main(){
    string line;
    fstream file;
    file.open("input.txt", ios::in);
    set<pair<int ,int>> c_p;
    map<pair<int ,int> ,vector<direction>> order;
    vector<string> mp;
    while(getline(file, line)){
        mp.push_back(line);
    }
    for(int i = 0; i < mp.size(); i++){
        for(int j = 0; j < mp[i].size(); j++){
            if (mp[i][j] == '#'){
                c_p.insert({i, j});
                order[{i, j}] = {NORTH, SOUTH, WEST, EAST};
            }
        }
    }
    /*
    for(auto &row : map){
        cout << row << endl;
    }
    */
   int i_min, i_max, j_min, j_max;
    i_min = j_min = 100000;
    i_max = j_max = -100000;
    int turn = 0;
   while(true){
        map<pair<int, int>, vector<pair<int, int>>> adj;
        bool any_moved = false;
        for (auto &[i ,j]: c_p){
            bool _adj = false;
            for (int di = -1; di <= 1; di++){
                for (int dj = -1; dj <= 1; dj++){
                    if (di == 0 && dj == 0){
                        continue;
                    }
                    if (c_p.find({i + di, j + dj}) != c_p.end()){
                        _adj = true;
                    }
                }
            }
            if (_adj){
                auto next = mve(c_p, order, {i, j});
                if (next != make_pair(i, j)){
                    adj[next].push_back({i, j});
                }
            }
            rotate(order[{i, j}].begin(), order[{i, j}].begin() + 1, order[{i, j}].end());
        }
        for (auto &key: adj){
            if (key.second.size() == 1){
                //cout << key.second[0].first << " " << key.second[0].second << " moved to " << key.first.first << " " << key.first.second << endl;
                c_p.insert(key.first);
                c_p.erase(key.second[0]);
                order[key.first] = order[key.second[0]];
                order.erase(key.second[0]);
                any_moved = true;
            }
        }
        for (auto &[i, j]: c_p){
            i_min = min(i_min, i);
            i_max = max(i_max, i);
            j_min = min(j_min, j);
            j_max = max(j_max, j);
        }
        /*
        for(int i = i_min; i <= i_max; i++){
            for(int j = j_min; j <= j_max; j++){
                if (c_p.find({i, j}) != c_p.end()){
                    cout << "#";
                }else{
                    cout << ".";
                }
            }
            cout << endl;
        }
        cout << endl;
        */
        if (turn == 10){
            int area = (i_max - i_min + 1) * (j_max - j_min + 1);
            cout << area - c_p.size() << endl;
        }
        turn++;
        if (!any_moved){
            break;
        }
   }
   cout << turn << endl;
}