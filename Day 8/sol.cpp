#include <bits/stdc++.h>
#include <fstream>
#include <string>
using namespace std;
int main(){
    fstream file;
    file.open("input.txt", ios::in);
    vector<vector<int>> map;
    string line;
    while(file >> line){
        vector<int> row;
        for(auto &ch: line){
            row.push_back(ch - '0');
        }
        map.push_back(row);
    }
    int res = 0;
    int res2 = 1;
    for (int i = 0; i < map.size(); i++){
        for(int j = 0; j < map[i].size(); j++){
            bool isedge = i == 0 || i == map.size() - 1 || j == 0 || j == map[i].size() - 1;
            int k;
            int res2c = !isedge;
            //cout << i << " " << j << " ";
            bool isup = true;
            bool isdown = true;
            bool isleft = true;
            bool isright = true;
            int u,l,d,r;
            u = l = d = r = 0;
            k = i - 1;
            for(; k >= 0; k--){
                u++;
                if (map[i][j] <= map[k][j]){
                    isup = false;
                    break;
                }
            }
            //cout << u;
            res2c *= u;
            k = i + 1;
            for(; k < map.size(); k++){
                d++;
                if (map[i][j] <= map[k][j]){
                    isdown = false;
                    break;
                }
            }
            //cout << " " << d;
            res2c *= d;
            k = j - 1;
            for(; k >= 0; k--){
                l++;
                if (map[i][j] <= map[i][k]){
                    isleft = false;
                    break;
                }
            }
            //cout << " " << l;
            res2c *= l;
            k = j + 1;
            for(; k < map[i].size(); k++){
                r++;
                if (map[i][j] <= map[i][k]){
                    isright = false;
                    break;
                }
            }
            //cout << " " << r << endl;
            res2c *= r;
            if (isedge || isup || isdown || isleft || isright){
                res++;
            }
            res2 = max(res2, res2c);
        }
    }
    cout << "Part 1: " << res << endl;
    cout << "Part 2: " << res2 << endl;
}