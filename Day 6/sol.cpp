#include <bits/stdc++.h>
#include <fstream>
#include <string>
using namespace std;

int main(){
    fstream file;
    file = fstream("input.txt", ios::in);
    string text;
    file >> text;
    //cout << text;
    string buffer = "";
    unordered_map<char, int> hash;
    for(int i = 0; i < text.size(); i++){
        buffer += text[i];
        //cout << text[i] << endl;
        hash[text[i]]++;
        if (buffer.length() == 4){
            //cout << buffer << endl;
            bool f = true;
            for(auto &ch : buffer){
                if (hash[ch] != 1){
                    f = false;
                    break;
                }
            }
            if (f){
                //cout << buffer << endl;
                cout << "Part 1: " << i + 1 << endl;
                break;
            }
            else{
                char front = buffer[0];
                buffer = buffer.substr(1);
                //cout << buffer << endl;
                hash[front]--;
            }
        }
    }

    for(int i = 0; i < text.size(); i++){
        buffer += text[i];
        //cout << text[i] << endl;
        hash[text[i]]++;
        if (buffer.length() == 14){
            //cout << buffer << endl;
            bool f = true;
            for(auto &ch : buffer){
                if (hash[ch] != 1){
                    f = false;
                    break;
                }
            }
            if (f){
                //cout << buffer << endl;
                cout << "Part 2: " << i + 1 << endl;
                break;
            }
            else{
                char front = buffer[0];
                buffer = buffer.substr(1);
                //cout << buffer << endl;
                hash[front]--;
            }
        }
    }
}