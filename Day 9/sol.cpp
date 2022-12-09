#include <bits/stdc++.h>
#include <fstream>
#include <string>
using namespace std;

void adjust_tail(pair<int, int> &head, pair<int ,int> &tail){
    int diff_x = head.first - tail.first;
    int diff_y = head.second - tail.second;
    if (abs(diff_x) <= 1 && abs(diff_y) <= 1){
        return;
    }
    else{
        if (diff_x == 0){
            if (diff_y > 0){
                tail.second = head.second - 1;
            }
            else{
                tail.second = head.second + 1;
            }
        }
        else if (diff_y == 0){
            if (diff_x > 0){
                tail.first = head.first - 1;
            }
            else{
                tail.first = head.first + 1;
            }
        }
        else{
            if (diff_x > 0 && diff_y > 0){
                tail.first++;
                tail.second++;
            }
            else if (diff_x > 0 && diff_y < 0){
                tail.first++;
                tail.second--;
            }
            else if (diff_x < 0 && diff_y > 0){
                tail.first--;
                tail.second++;
            }
            else{
                tail.first--;
                tail.second--;
            }
        }
    }
}



int main(){
    fstream file;
    file.open("input.txt", ios::in);
    vector<pair<char, int>> commands;
    string line;
    while(file.peek() != EOF){
        getline(file, line);
        commands.push_back(make_pair(line[0], stoi(line.substr(1))));
    }
    /*
    for(auto &[c, n]: commands){
        cout << c << " " << n << endl;
    }
    */
    set<pair<int, int >> visited;
    visited.insert(make_pair(0, 0));
    pair<int, int> head, tail;
    head = make_pair(0,0);
    tail = make_pair(0,0);
    for(auto &[direc, qty]: commands){
        int c = qty;
        while(c){
            switch(direc){
                case 'R':
                    head.first++;
                    break;
                case 'L':
                    head.first--;
                    break;
                case 'U':
                    head.second++;
                    break;
                case 'D':
                    head.second--;
                    break;
            }
            adjust_tail(head, tail);
            visited.insert(tail);
            c--;
            //cout << "head: " << head.first << " " << head.second << endl;
            //cout << "tail: " << tail.first << " " << tail.second << endl;
        }
        //cout << "F" << endl;
    }
    cout << "Part 1:" << visited.size() << endl;
    visited.clear();
    vector<pair<int, int>> snake(10, make_pair(0,0));
    for(auto &[direc, qty]: commands){
        int c = qty;
        while(c){
            switch(direc){
                case 'R':
                    snake[0].first++;
                    break;
                case 'L':
                    snake[0].first--;
                    break;
                case 'U':
                    snake[0].second++;
                    break;
                case 'D':
                    snake[0].second--;
                    break;
            }
            for(int i = 0; i < snake.size() - 1; i++){
                adjust_tail(snake[i], snake[i + 1]);
            }
            visited.insert(snake[snake.size() - 1]);
            c--;
            //cout << "head: " << head.first << " " << head.second << endl;
            //cout << "tail: " << tail.first << " " << tail.second << endl;
        }
        //cout << "F" << endl;
    }
    cout << "Part 2:" << visited.size() << endl;
}