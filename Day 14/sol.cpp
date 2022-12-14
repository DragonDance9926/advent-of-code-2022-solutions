#include <bits/stdc++.h>
#include <fstream>
#include <string>
using namespace std;

void fill_rock(map<pair<int, int>,char> &m, pair<int, int> &p1, pair<int, int> &p2){
    if(p1.first == p2.first){
        for(int i = min(p1.second, p2.second); i <= max(p1.second, p2.second); i++)
            m[make_pair(p1.first, i)] = '#';
    }
    else{
        for(int i = min(p1.first, p2.first); i <= max(p1.first, p2.first); i++)
            m[make_pair(i, p1.second)] = '#';
    }
}
pair<int, int> find_place(map<pair<int, int>, char> &m, pair<int, int> curr_point){
    int x = curr_point.first;
    int y = curr_point.second;
    if (m.find(make_pair(x, y+1)) == m.end())
        return make_pair(x, y+1);
    else if (m.find(make_pair(x-1, y + 1)) == m.end())
        return make_pair(x-1, y + 1);
    else if (m.find(make_pair(x+1, y + 1)) == m.end())
        return make_pair(x+1, y + 1);
    else
        return make_pair(-1, -1);
}


bool sand_drop(map<pair<int, int>, char> &m, pair<int, int> start){
    int x = start.first;
    int y = start.second;
    while(y < 1000){
        auto [x1, y1] = find_place(m, make_pair(x, y));
        if (x1 == -1 && y1 == -1){
            break;
        }
        else{
            x = x1;
            y = y1;
        }
    }
    if (y == 1000)
        return false;
    else{
        m[make_pair(x, y)] = '~';
        return true;
    }
}

bool sand_drop2(map<pair<int, int>, char> &m, pair<int, int> start, int highy){
    int x = start.first;
    int y = start.second;
    bool moved = false;
    while(y < highy - 1){
        auto [x1, y1] = find_place(m, make_pair(x, y));
        if (x1 == -1 && y1 == -1){
            break;
        }
        else{
            moved = true;
            x = x1;
            y = y1;
        }
    }
    if (!moved)
        return false;
    else{
        m[make_pair(x, y)] = '~';
        return true;
    }
}

int main(){
    fstream file;
    file.open("input.txt", ios::in);
    string line,part;
    map<pair<int, int>, char> m, m2;
    while(file.peek() != EOF){
        getline(file,line);
        //Tokine String By " -> "
        vector<pair<int, int>> v;
        while(line.find(" -> ") != string::npos){
            part = line.substr(0,line.find(" -> "));
            line = line.substr(line.find(" -> ")+4);
            //Tokine String By " "
            //cout << part << endl;
            v.push_back(make_pair(stoi(part.substr(0,part.find(","))),stoi(part.substr(part.find(",")+1))));
        }
        v.push_back(make_pair(stoi(line.substr(0,line.find(","))),stoi(line.substr(line.find(",")+1))));
        for(int i = 1; i < v.size(); i++){
            fill_rock(m, v[i-1], v[i]);
            fill_rock(m2, v[i-1], v[i]);
        }
    }
    int c = 0;
    int highy = 0;
    pair<int, int> start = make_pair(500, 0);
    while(true){
        if (sand_drop(m, start))
            c++;
        else
            break;
    }
    for(auto &[k, v]: m){
        highy = max(highy, k.second);
    }
    cout <<"Part 1: " << c << endl;
    c = 0;
    highy += 2;
    while(true){
        if (sand_drop2(m2, start, highy))
            c++;
        else
            break;
    }
    cout <<"Part 2: " << c + 1<< endl;
}