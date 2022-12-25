#include <bits/stdc++.h>
#include <fstream>
#include <utility>
using namespace std;

long long int numtoelf(string &num){
    long long int elf = 0;
    reverse(num.begin(), num.end());
    for(int i = 0; i < num.size(); i++){
        switch (num[i]){
            case '2':
                elf += 2 * pow(5, i);
                break;
            case '1':
                elf += pow(5, i);
                break;
            case '0':
                break;
            case '-':
                elf += -1 * pow(5, i);
                break;
            case '=':
                elf += -2 * pow(5, i);
                break;
        }
    }
    return elf;
}


string elftonum (long long int elf){
    string num = "";
    while(elf != 0){
        if(elf % 5 == 0){
            num += '0';
        }
        else if(elf % 5 == 1){
            num += '1';
        }
        else if(elf % 5 == 2){
            num += '2';
        }
        else if(elf % 5 == 3){
            num += '=';
            elf += 5;
        }
        else if(elf % 5 == 4){
            num += '-';
            elf += 5;
        }
        elf /= 5;
    }
    reverse(num.begin(), num.end());
    return num;
}




int main(){
    string line;
    fstream file;
    file.open("input.txt", ios::in);
    vector<string> numbers;
    while(getline(file, line)){
        numbers.push_back(line);
    }
    long long int sum = 0;
    for (auto &num : numbers){
        sum += numtoelf(num);
    }
    cout << elftonum(sum) << endl;
}