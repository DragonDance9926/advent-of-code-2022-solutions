#include <bits/stdc++.h>
#include <fstream>
#include <string>

using namespace std;

int a_rank(char &c){
    if (c >= 'a' && c <= 'z'){
        return c - 'a' + 1;
    }
    return c - 'A' + 27;
}



int main(){
    fstream file;
    file.open("input.txt", ios::in);
    vector<pair<string,string>> sacks;
    string tmp;
    while(file >> tmp){
        int mid = tmp.size() / 2;
        sacks.push_back({tmp.substr(0, mid), tmp.substr(mid)});
        //cout << sacks.back().first << " " << sacks.back().second << endl;
    }
    int sum = 0;
    for(auto &[left, right]: sacks){
        unordered_map<char, int> hash;
        for(auto& ch: left){
            hash[ch]++;
        }
        for(auto& ch: right){
            if (hash[ch]){
                //cout << ch << endl;
                sum += a_rank(ch);
                break;
            }
        }
    }
    cout << "Part 1: " << sum << endl;

    sum = 0;
    int i = 0;
    for(; i < sacks.size(); i += 3){
        auto l = sacks[i].first + sacks[i].second;
        auto m = sacks[i + 1].first + sacks[i + 1].second;
        auto h= sacks[i + 2].first + sacks[i + 2].second;
        unordered_map<char, pair<bool, bool>> hash;
        for (auto &ch: l){
            hash[ch].first = true;
        }
        for (auto &ch: m){
            hash[ch].second = true;
        }
        for (auto &ch: h){
            if (hash[ch].first && hash[ch].second){
                //cout << ch << endl;
                sum += a_rank(ch);
                break;
            }
        }
    }
    cout << "Part 2: " << sum << endl;
    return 0;
}