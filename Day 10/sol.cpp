#include <bits/stdc++.h>
#include <fstream>
#include <string>
#include <queue>
using namespace std;

int main(){
    fstream file;
    file.open("input.txt", ios::in);
    int x = 1;
    int cycle = 0;
    int check = 20;
    long long int res = 0;
    int old;
    string line;
    while(file.peek() != EOF){
        old = x;
        getline(file, line);
        //cout << line.substr(0,4) << endl;
        if(line.substr(0, 4) == "addx"){
            x += stoi(line.substr(5));
            cycle++;
        }
        cycle++;
        if (check <= 220 && cycle >= check){
            //cout << "Cycle: " << check << " " << old << endl;
            res += old * check;
            check += 40;
        }
    }
    cout << "Part 1: " << res << endl;
    file.close();
    file.open("input.txt", ios::in);
    string sprite(40, '.');
    sprite[0] = sprite[1] = sprite[2] = '#';
    string n_line = "";
    int i = 0;
    x = 1;
    while(file.peek() != EOF){
        getline(file, line);
        if(line.substr(0, 4) == "addx"){
            n_line += sprite[i % 40];
            i++;
            n_line += sprite[i % 40];
            i++;
            x += stoi(line.substr(5));
            for(int i = 0; i < 40; i++)
                sprite[i] = '.';
            sprite[x - 1] = sprite[x] = sprite[x+1] = '#';
            //cout << sprite << endl;
        }
        else{
            n_line += sprite[i % 40];
            i++;
        }
    }
    cout << "Part 2: " << endl;
    for(int i = 0; i < 240; i += 40)
        cout << n_line.substr(i, 40) << endl;
    return 0;
}