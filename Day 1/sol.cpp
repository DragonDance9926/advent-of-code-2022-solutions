#include <bits/stdc++.h>
#include <fstream>
using namespace std;


int main(){
    fstream file;
    file.open("input.txt", ios::in);
    long long first, second, third;
    first = LONG_MIN;
    second = LONG_MIN;
    third = LONG_MIN;
    string line;
    long long tmp = 0;
    while (!file.eof()){
        //Detect if new line
        getline(file, line);
        if (line == ""){
            if (tmp > first){
                third = second;
                second = first;
                first = tmp;
            }
            else if (tmp > second){
                third = second;
                second = tmp;
            }
            else if (tmp > third){
                third = tmp;
            }
            tmp = 0;
        }
        else{
            tmp += stoi(line);
        }
    }
    cout << "Part1: " << first << endl;
    cout << first << " " << second << " " << third << endl;
    cout << "Part2: " << first + second + third << endl;
}