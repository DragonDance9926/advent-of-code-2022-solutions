#include <bits/stdc++.h>
#include <fstream>
using namespace std;

vector<pair<int, int>> create_shape(int turn, int y){
    switch (turn % 5){
        case 0:
            //cout << '-' << endl;
            return {{2, y + 3}, {3, y + 3}, {4, y + 3}, {5, y + 3}};
            break;
        case 1:
            //cout << '+' << endl;
            return {{3, y + 3}, {3, y + 4}, {3, y + 5}, {2, y + 4}, {4, y + 4}};
            break;
        case 2:
            //cout << 'J' << endl;
            return {{2, y + 3}, {3, y + 3}, {4, y + 3}, {4, y + 4}, {4, y + 5}};
            break;
        case 3:
            //cout << '|' << endl;
            return {{2, y + 3}, {2, y + 4}, {2, y + 5}, {2, y + 6}};
            break;
        case 4:
            //cout << 'O' << endl;
            return {{2, y + 3}, {2, y + 4}, {3, y + 3}, {3, y + 4}};
            break;
    }
}

void move(map<pair<int,int>,char> &m, vector<pair<int, int>> &shape, string &path, int &path_index, int &high_y){
    while (true){
        bool can_move = true;
        switch(path[path_index]){
            case '<':
                for(auto &[x, y]: shape){
                    if (x <= 0 || m[{x - 1, y}] == '#'){
                        can_move = false;
                        break;
                    }
                }
                if (can_move){
                    for (auto &[x, y]: shape){
                        x--;
                    }
                }
                break;
            case '>':
                for(auto &[x, y]: shape){
                    if (x >= 6 || m[{x + 1, y}] == '#'){
                        can_move = false;
                        break;
                    }
                }
                if (can_move){
                    for (auto &[x,y]:shape){
                        x++;
                    }
                }
                break;
            default:
                cout << "Error!" << endl;
        }
        path_index= (path_index + 1) % path.size();
        bool down = true;
        for(auto &[x , y]:shape){
            if (y == 0){
                down = false;
                break;
            }
            if (m[{x, y - 1}] == '#'){
                down = false;
                break;
            }
        }
        if (down){
            for(auto &[x, y]:shape){
                y--;
            }
        }
        else{
            for(auto coor: shape){
                m[coor] = '#';
            }
            break;
        }
        
    }
    int m_y = 0;
    for (auto &[x, y]: shape){
        m_y = max(m_y, y);
    }
    high_y = max(high_y, m_y);
}
string print(__uint128_t t){
    string s = "";
    while (t > 0){
        s += (t % 10) + '0';
        t /= 10;
    }
    reverse(s.begin(), s.end());
    return s;
}



int main(){
    map<pair<int,int>,char> m;
    fstream file;
    file.open("input.txt",ios::in);
    string paths;
    file >> paths;
    //cout << paths << endl;
    if (paths[paths.size() - 1] == '\n'){
        paths = paths.substr(0, paths.size() - 1);
    }
    __uint128_t turn = 0;
    file.close();
    int high_y = -1;
    int path_index = 0;
    string seq;
    while(turn < 100000){
        int prev = high_y + 1;
        vector<pair<int, int>> shape = create_shape(turn, high_y + 1);
        move(m, shape, paths, path_index, high_y);
        if (turn == 2021){
            cout << "Part 1: " << high_y + 1 << endl;
        }
        seq += to_string(high_y + 1 - prev);
        seq += " ";
        turn++;
    }
    file.close();
    file.open("a.txt", ios::in);
    /*
    About Part 2:
    Unfortunely I don't know how to detect cycle.
    So I printed the delta heights in a.txt and found that the cycle by CTRL + F
    */

    string n_seq, r_seq;
    getline(file, n_seq);
    getline(file, r_seq);
    vector<int> seq1, seq2;
    stringstream ss(n_seq), ss2(r_seq);
    int n;
    while(ss >> n){
        seq1.push_back(n);
        //cout << n << endl;
    }
    while(ss2 >> n){
        seq2.push_back(n);
    }

    int curr_ind = 0;
    turn = 0;
    __uint128_t total = 0;
    for(auto &ni: seq1){
        total += ni;
        turn ++;
    }
    __uint128_t seq2_total = 0;
    __uint128_t seq2_uncycle = 0;
    for (auto &ni: seq2){
        seq2_total += ni;
    }
    __uint128_t left = 1000000000000 - turn;
    __uint128_t cycle_c = left / seq2.size();
    __uint128_t uncycle = left % seq2.size();
    for(int i = 0; i < uncycle; i++){
        seq2_uncycle += seq2[i];
    }
    __uint128_t ans = total + cycle_c * seq2_total + seq2_uncycle;
    //print ans
    cout <<"Part 2:" << print(ans) << endl;
}