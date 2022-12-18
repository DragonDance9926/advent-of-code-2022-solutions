#include <bits/stdc++.h>
#include <fstream>
using namespace std;
int maxx = 0;
int maxy = 0;
int maxz = 0;
int minx = INT_MAX;
int miny = INT_MAX;
int minz = INT_MAX;

int count_sides(set<tuple<int, int, int>> &m,vector<tuple<int, int, int>> &faces, tuple<int, int, int> curr){
    int count = 0;
    for(auto &f : faces){
        tuple<int, int, int> next = {get<0>(curr) + get<0>(f), get<1>(curr) + get<1>(f), get<2>(curr) + get<2>(f)};
        if (m.find(next) != m.end()) count++;
    }
    return count;
}

set<tuple<int ,int, int>> known_exterior;

bool exterior(set<tuple<int, int, int>> &m, vector<tuple<int, int, int>> &faces, tuple<int, int, int> c){
    if (m.find(c) != m.end()) return false;
    set<tuple<int, int, int>> visited;
    stack<tuple<int, int, int>> s;
    s.push(c);
    while(!s.empty()){
        tuple<int, int, int> curr = s.top();
        s.pop();
        if (visited.find(curr) != visited.end()) continue;
        visited.insert(curr);
        if (known_exterior.find(curr) != known_exterior.end()){
            for (auto &v : visited){
                if (m.find(v) == m.end()) known_exterior.insert(v);
                return true;
            }
        }
        if (get<0>(curr) < minx || get<0>(curr) > maxx || get<1>(curr) < miny || get<1>(curr) > maxy || get<2>(curr) < minz || get<2>(curr) > maxz) {
            for (auto &v : visited){
                if (m.find(v) == m.end()) known_exterior.insert(v);
                return true;
            }
        }
        if (m.find(curr) != m.end()) continue;
        for (auto &f : faces){
            s.push({get<0>(curr) + get<0>(f), get<1>(curr) + get<1>(f), get<2>(curr) + get<2>(f)});
        }
    }
    return false;
}



int main(){
    set<tuple<int, int, int>> m;
    set<tuple<int, int, int>> space;
    vector<tuple<int, int, int>> faces = {
        {0, 1, 0}, {0, -1, 0}, {1, 0, 0}, {-1, 0, 0}, {0, 0, 1}, {0, 0, -1}
    };
    fstream file;
    file.open("input.txt", ios::in);
    string line;
    while(getline(file, line)){
        tuple<int ,int, int> t;
        sscanf(line.c_str(), "%d,%d,%d", &get<0>(t), &get<1>(t), &get<2>(t));
        m.insert(t);
        maxx = max(maxx, get<0>(t));
        maxy = max(maxy, get<1>(t));
        maxz = max(maxz, get<2>(t));
        minx = min(minx, get<0>(t));
        miny = min(miny, get<1>(t));
        minz = min(minz, get<2>(t));
    }
    minx -= 2;
    miny -= 2;
    minz -= 2;
    maxx += 2;
    maxy += 2;
    maxz += 2;
    int res = 0;
    int res2 = 0;
    for(auto &[x, y, z]: m){
        for(auto &[dx, dy, dz]: faces){
            if (m.find({x + dx, y + dy, z + dz}) == m.end()){
                res++;
                tuple<int, int, int> sp = {x + dx, y + dy, z + dz};
                space.insert(sp);
            }
        }
    }
    cout <<"Part 1: " << res << endl;
    res2 = res;
    for(auto &[x, y, z]: space){
        //cout << x << " " << y << " " << z << endl;
        if (!exterior(m, faces, {x, y, z})){
            res2 -= count_sides(m, faces, {x, y, z});
        }
    }
    cout <<"Part 2: " << res2 << endl;
}