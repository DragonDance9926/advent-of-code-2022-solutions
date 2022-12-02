#include <bits/stdc++.h>
#include <fstream>
#include <string>
using namespace std;

int main(){
    fstream file;
    file.open("input.txt", ios::in);
    unordered_map<char, string> mp = {{'A', "Rock"}, {'B', "Paper"}, {'C', "Scissors"}};
    unordered_map<char, string> you = {{'X',"Rock"}, {'Y', "Paper"}, {'Z', "Scissors"}};
    unordered_map<string, int> cost = {{"Rock", 1}, {"Paper", 2}, {"Scissors", 3}};
    auto win = [](string &a, string &b){
        if(a == "Rock" && b == "Scissors") return 0;
        if(a == "Paper" && b == "Rock") return 0;
        if(a == "Scissors" && b == "Paper") return 0;
        if (a == b) return 3;
        return 6;
    };
    char c1, c2;
    char tmp;
    int ans = 0;
    while(file >> c1 >> c2){
        ans += win(mp[c1], you[c2]) + cost[you[c2]];
    }
    cout <<"Part 1:" << ans << endl;
    file.close();
    unordered_map<char, int> state = {{'X', 0}, {'Y', 3}, {'Z', 6}};
    //X lose, Y draw, Z win
    file.open("input.txt", ios::in);
    ans = 0;
    auto outcome = [&mp, &state, &cost](char &op_p, char &s){
        if (state[s] == 3) return cost[mp[op_p]];
        else if (state[s] == 6){
            //you have to win
            if (mp[op_p] == "Rock") return cost["Paper"];
            if (mp[op_p] == "Paper") return cost["Scissors"];
            if (mp[op_p] == "Scissors") return cost["Rock"];
        }
        else{
            //you have to lose
            if (mp[op_p] == "Rock") return cost["Scissors"];
            if (mp[op_p] == "Paper") return cost["Rock"];
            if (mp[op_p] == "Scissors") return cost["Paper"];
        }
        return 0;
    };
    while(file >> c1 >> c2){    
        //cout << state[c2] << " " << outcome(c1, c2) << endl;
        ans += state[c2] + outcome(c1, c2);
        
    }
    cout << "Part 2:" << ans << endl;
    return 0;
}