#include <bits/stdc++.h>
#include <fstream>
#include <string>

using namespace std;

int main(){
    fstream file;
    file.open("input.txt", ios::in);
    int n1, n2, n3, n4;
    char c;
    vector<tuple<int, int, int,int>> data;
    while(file >> n1 >> c >> n2 >> c >> n3 >> c >> n4){
        data.push_back(make_tuple(n1, n2, n3, n4));
    }
    auto covers = [](int &x1, int &x2, int &y1, int &y2){
        int l = max(x1, y1);
        int r = min(x2, y2);
        //cout << l << r << endl;
        return (x1 == l && r == x2) || (y1 == l && r == y2);
    };
    auto overlap = [](int &x1, int &x2, int &y1, int &y2){
        return x1 <= y2 && y1 <= x2;
    };
    int res = 0, res2 = 0;
    for (auto &[x1, x2, y1, y2]: data){
        res += covers(x1,x2,y1,y2);
        res2 += overlap(x1,x2,y1,y2);
    }
    cout << "Part 1: " << res << endl;
    cout << "Part 2: " << res2 << endl;
}