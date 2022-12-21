#include <bits/stdc++.h>
#include <fstream>
using namespace std;

long long find(unordered_map<string, string> &m, string key){
    string data = m[key];
    if (data[0] == '-' || (data[0] >= '0' && data[0] <= '9')){
        return stoll(data);
    }
    else{
        string v1 = data.substr(0, 4);
        string v2 = data.substr(7, 4);
        char op = data[5];
        long long a = find(m, v1);
        long long b = find(m, v2);
        switch(op){
            case '+':
                return a + b;
            case '*':
                return a * b;
            case '/':
                return a / b;
            case '-':
                return a - b;
            case '=':
                return a - b;
        }
    }
}



int main(){
    unordered_map<string, string> mp;
    string s;
    fstream file;
    string k, v;
    file.open("input.txt", ios::in);
    while(file.peek() != EOF){
        getline(file, s);
        k = s.substr(0, s.find(":"));
        v = s.substr(s.find(":") + 2);
        mp[k] = v;
    }
    cout << "Part 1: " << find(mp, "root") << endl;

    mp["root"][5] = '=';
    long long left, right;
    left = 0;
    right = 1000000000000000;
    while (true){
        long long guess = left + (right - left) / 2;
        mp["humn"] = to_string(guess);
        long long ans = find(mp, "root");
        if (ans == 0){
            cout <<"Part 2: " << guess << endl;
            break;
        }
        else if (ans < 0)
            right = guess;
        else
            left = guess + 1;
    }
}