#include <bits/stdc++.h>
#include <fstream>
#include <string>
#include <cstdio>
using namespace std;
int main(){
    fstream file;
    file = fstream("input.txt", ios::in);
    string text;
    int qty, src, dst;
    vector<vector<char>> stacks(9);
    /*
    stacks[0] = {'Z', 'N'};
    stacks[1] = {'M', 'C', 'D'};
    stacks[2] = {'P'};*/

    //I have entered the stacks by hand. Please change these values to the ones you get from the input file.
    stacks[0] = {'D', 'H', 'N', 'Q', 'T', 'W', 'V', 'B'};
    stacks[1] = {'D', 'W', 'B'};
    stacks[2] = {'T', 'S', 'Q', 'W', 'J', 'C'};
    stacks[3] = {'F', 'J', 'R', 'N', 'Z', 'T', 'P'};
    stacks[4] = {'G', 'P', 'V', 'J', 'M', 'S', 'T'};
    stacks[5] = {'B', 'W', 'F', 'T', 'N'};
    stacks[6] = {'B', 'L', 'D', 'Q', 'F', 'H','V', 'N'};
    stacks[7] = {'H', 'P', 'F', 'R'};
    stacks[8] = {'Z', 'S', 'M', 'B', 'L', 'N', 'P', 'H'};
    while(file.peek() != EOF){
        getline(file, text);
        sscanf(text.c_str(), "move %d from %d to %d", &qty, &src, &dst);
        src--;
        dst--;
        while(qty && stacks[src].size()){
            stacks[dst].push_back(stacks[src].back());
            stacks[src].pop_back();
            qty--;
        }
    }
    file.close();
    cout << "Part 1: ";
    for(int i = 0; i < stacks.size(); i++){
        cout << stacks[i].back();
    }
    cout << endl;
    /*
    stacks[0] = {'Z', 'N'};
    stacks[1] = {'M', 'C', 'D'};
    stacks[2] = {'P'};*/

    //Same as above
    stacks[0] = {'D', 'H', 'N', 'Q', 'T', 'W', 'V', 'B'};
    stacks[1] = {'D', 'W', 'B'};
    stacks[2] = {'T', 'S', 'Q', 'W', 'J', 'C'};
    stacks[3] = {'F', 'J', 'R', 'N', 'Z', 'T', 'P'};
    stacks[4] = {'G', 'P', 'V', 'J', 'M', 'S', 'T'};
    stacks[5] = {'B', 'W', 'F', 'T', 'N'};
    stacks[6] = {'B', 'L', 'D', 'Q', 'F', 'H','V', 'N'};
    stacks[7] = {'H', 'P', 'F', 'R'};
    stacks[8] = {'Z', 'S', 'M', 'B', 'L', 'N', 'P', 'H'};
    //cout << 1 << endl;
    file = fstream("input.txt", ios::in);
    while(file.peek() != EOF){
        //cout << 2 << endl;
        getline(file, text);
        //cout << text << endl;
        sscanf(text.c_str(), "move %d from %d to %d", &qty, &src, &dst);
        src--;
        dst--;
        stack<char> tmp;
        while(qty && stacks[src].size()){
            tmp.push(stacks[src].back());
            stacks[src].pop_back();
            qty--;
        }
        while(tmp.size()){
            stacks[dst].push_back(tmp.top());
            tmp.pop();
        }
    }
    cout << "Part 2: ";
    for(int i = 0; i < stacks.size(); i++){
        cout << stacks[i].back();
    }
    cout << endl;
}