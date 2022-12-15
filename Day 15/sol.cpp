#include <bits/stdc++.h>
#include <fstream>
using namespace std;

int manhattan(pair<int, int> a, pair<int, int> b){
    return abs(a.first - b.first) + abs(a.second - b.second);
}


int main(){
    fstream file("input.txt");
    string line;
    map<pair<int, int>, char> m;
    pair<int, int> beacon;
    pair<int ,int> sensor;
    vector<pair<pair<int, int>, pair<int, int>>> v;
    int x_max = INT_MIN;
    while(getline(file, line)){
        char* cstrline = new char[line.length() + 1];
        strcpy(cstrline, line.c_str());
        sscanf(cstrline, "Sensor at x=%d, y=%d: closest beacon is at x=%d, y=%d", &sensor.first, &sensor.second, &beacon.first, &beacon.second);
        //cout << "Sensor: " << sensor.first << " " << sensor.second << endl;
        //cout << "Beacon: " << beacon.first << " " << beacon.second << endl;
        x_max = max(x_max, sensor.first);
        m[beacon] = 'B';
        m[sensor] = 'S';
        v.push_back({sensor, beacon});
        delete cstrline;
    }
    int y = 2000000;
    int x = -(x_max* 2);
    int c = 0;
    for(; x <= x_max * 2; x++){
        bool placed = true;
        pair<int, int> p = {x, y};
        if (m[p] == 'S'){
            continue;
        }
        if (m[p] == 'B'){
            continue;
        }
        for (auto&[sensor, beacon]: v){
            if (manhattan(sensor, p) <= manhattan(sensor, beacon)){
                placed = false;
                break;
            }
        }
        if (!placed){
            c++;
        }
    }
    cout << "Part 1:" << c << endl;
   bool f = false;
    for(y = 0;!f && y <= 4000000; y++){
        vector<pair<int, int>> intervals;
        for (auto&[sensor, beacon]: v){
            int total_man = manhattan(sensor, beacon);
            int x_diff = abs(y - sensor.second);
            total_man -= x_diff;
            if (total_man < 0){
                continue;
            }
            intervals.push_back({max(0, sensor.first - total_man), min(4000000, sensor.first + total_man)});
        }
        //Merge overlapping intervals
        sort(intervals.begin(), intervals.end());
        vector<pair<int, int>> merged;
        for (auto&[l, r]: intervals){
            if (merged.empty()){
                merged.push_back({l, r});
            }
            else{
                auto&[last_l, last_r] = merged.back();
                if (last_r >= l ){
                    last_r = max(last_r, r);
                }
                else{
                    merged.push_back({l, r});
                }
            }
        }
        if (merged.size() == 1){
            continue;
        }
        else{
            for(int i = 0; i < merged.size() - 1; i++){
                auto&[l, r] = merged[i];
                auto&[next_l, next_r] = merged[i + 1];
                if (next_l - r > 1){
                    cout << "Part 2:" << endl;
                    cout << "x:" <<  r + 1 << " y:" << y << endl;
                    //unsigned long long res = 4000000 * (r + 1) + 14;
                    f = true;
                    break;
                }
            }
        }
    }

}