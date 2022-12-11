#include <bits/stdc++.h>
#include <fstream>
#include <string>
#include <queue>
#define int uint64_t
using namespace std;

signed main(){
    fstream file;
    file.open("input.txt", ios::in);
    unordered_map<int, tuple<vector<int>, function<void(int&)>, function<void(int&)>>> instructions;
    /*
    int size = 4;
    auto &[arr, update, test] = instructions[0];
    arr = {79, 98};
    update = [](int &x){x *= 19;};
    test = [&instructions](int &x){
        get<0>(instructions[x % 23 == 0 ? 2: 3]).push_back(x);
    };
    auto &[arr1, update1, test1] = instructions[1];
    arr1 = {54, 65, 75, 74};
    update1 = [](int &x){x += 6;};
    test1 = [&instructions](int &x){
        get<0>(instructions[x % 19 == 0 ? 2: 0]).push_back(x);
    };

    auto &[arr2, update2, test2] = instructions[2];
    arr2 = {79, 60, 97};
    update2 = [](int &x){x *= x;};
    test2 = [&instructions](int &x){
        get<0>(instructions[x % 13 == 0 ? 1: 3]).push_back(x);
    };

    auto &[arr3, update3, test3] = instructions[3];
    arr3 = {74};
    update3 = [](int &x){x += 3;};
    test3 = [&instructions](int &x){
        get<0>(instructions[x % 17 == 0 ? 0: 1]).push_back(x);
    };
    */
    int size = 8;
    auto &[arr, update, test] = instructions[0];
    arr = {84, 66, 62, 69, 88, 91, 91};
    update = [](int &x){x *= 11;};
    test = [&instructions](int &x){
        get<0>(instructions[x % 2 == 0 ? 4: 7]).push_back(x);
    };
    auto &[arr1, update1, test1] = instructions[1];
    arr1 = {98, 50, 76, 99};
    update1 = [](int &x){x *= x;};
    test1 = [&instructions](int &x){
        get<0>(instructions[x % 7 == 0 ? 3: 6]).push_back(x);
    };

    auto &[arr2, update2, test2] = instructions[2];
    arr2 = {72, 56, 94};
    update2 = [](int &x){x += 1;};
    test2 = [&instructions](int &x){
        get<0>(instructions[x % 13 == 0 ? 4: 0]).push_back(x);
    };

    auto &[arr3, update3, test3] = instructions[3];
    arr3 = {55, 88, 90, 77, 60, 67};
    update3 = [](int &x){x += 2;};
    test3 = [&instructions](int &x){
        get<0>(instructions[x % 3 == 0 ? 6: 5]).push_back(x);
    };
    auto &[arr4, update4, test4] = instructions[4];
    arr4 = {69, 72, 63, 60, 72, 52, 63, 78};
    update4 = [](int &x){x *= 13;};
    test4 = [&instructions](int &x){
        get<0>(instructions[x % 19 == 0 ? 1: 7]).push_back(x);
    };
    auto &[arr5, update5, test5] = instructions[5];
    arr5 = {89, 73};
    update5 = [](int &x){x += 5;};
    test5 = [&instructions](int &x){
        get<0>(instructions[x % 17 == 0 ? 2: 0]).push_back(x);
    };
    auto &[arr6, update6, test6] = instructions[6];
    arr6 = {78, 68, 98, 88, 66};
    update6 = [](int &x){x += 6;};
    test6 = [&instructions](int &x){
        get<0>(instructions[x % 11 == 0 ? 2: 5]).push_back(x);
    };
    auto &[arr7, update7, test7] = instructions[7];
    arr7 = {70};
    update7 = [](int &x){x += 7;};
    test7 = [&instructions](int &x){
        get<0>(instructions[x % 5 == 0 ? 1: 3]).push_back(x);
    };
    vector<int> counters(size, 0);
    for(int turn = 0; turn < 20; turn++){
        //cout << "Turn: " << turn << endl;
        for(int i = 0; i < size; i++){
            auto &[arr, update, test] = instructions[i];
            reverse(arr.begin(), arr.end());
            while (!arr.empty()){
                //cout << "Before: " << arr.back() << " ";
                int x = arr.back();
                arr.pop_back();
                update(x);
                x /= 3;
                //cout << "After: " << x << '\n';
                test(x);
                counters[i]++;
            }
            //cout << endl;
        }
    }
    for(auto &counter: counters){
        cout << static_cast<double>(counter) << " ";
    }
    cout << endl;
    int f_max = 0, s_max = 0;
    for(auto &counter: counters){
        if(counter > f_max){
            s_max = f_max;
            f_max = counter;
        }
        else if(counter > s_max){
            s_max = counter;
        }
    }
    cout <<"Part 1: " << static_cast<double>(f_max) * static_cast<double>(s_max) << endl;
    /*
    arr = {79, 98};
    update = [](int &x){x *= 19;};
    test = [&instructions](int &x){
        get<0>(instructions[x % 23 == 0 ? 2: 3]).push_back(x);
    };
   
    arr1 = {54, 65, 75, 74};
    update1 = [](int &x){x += 6;};
    test1 = [&instructions](int &x){
        get<0>(instructions[x % 19 == 0 ? 2: 0]).push_back(x);
    };

    
    arr2 = {79, 60, 97};
    update2 = [](int &x){x *= x;};
    test2 = [&instructions](int &x){
        get<0>(instructions[x % 13 == 0 ? 1: 3]).push_back(x);
    };

    
    arr3 = {74};
    update3 = [](int &x){x += 3;};
    test3 = [&instructions](int &x){
        get<0>(instructions[x % 17 == 0 ? 0: 1]).push_back(x);
    };
    */
    arr = {84, 66, 62, 69, 88, 91, 91};
    update = [](int &x){x *= 11;};
    test = [&instructions](int &x){
        get<0>(instructions[x % 2 == 0 ? 4: 7]).push_back(x);
    };
    arr1 = {98, 50, 76, 99};
    update1 = [](int &x){x *= x;};
    test1 = [&instructions](int &x){
        get<0>(instructions[x % 7 == 0 ? 3: 6]).push_back(x);
    };
    arr2 = {72, 56, 94};
    update2 = [](int &x){x += 1;};
    test2 = [&instructions](int &x){
        get<0>(instructions[x % 13 == 0 ? 4: 0]).push_back(x);
    };
    arr3 = {55, 88, 90, 77, 60, 67};
    update3 = [](int &x){x += 2;};
    test3 = [&instructions](int &x){
        get<0>(instructions[x % 3 == 0 ? 6: 5]).push_back(x);
    };
    arr4 = {69, 72, 63, 60, 72, 52, 63, 78};
    update4 = [](int &x){x *= 13;};
    test4 = [&instructions](int &x){
        get<0>(instructions[x % 19 == 0 ? 1: 7]).push_back(x);
    };
    arr5 = {89, 73};
    update5 = [](int &x){x += 5;};
    test5 = [&instructions](int &x){
        get<0>(instructions[x % 17 == 0 ? 2: 0]).push_back(x);
    };
    arr6 = {78, 68, 98, 88, 66};
    update6 = [](int &x){x += 6;};
    test6 = [&instructions](int &x){
        get<0>(instructions[x % 11 == 0 ? 2: 5]).push_back(x);
    };
    arr7 = {70};
    update7 = [](int &x){x += 7;};
    test7 = [&instructions](int &x){
        get<0>(instructions[x % 5 == 0 ? 1: 3]).push_back(x);
    };
    counters = vector<int>(size, 0);
    for(int turn = 0; turn < 10000; turn++){
        //cout << "Turn: " << turn << endl;
        for(int i = 0; i < size; i++){
            auto &[arr, update, test] = instructions[i];
            reverse(arr.begin(), arr.end());
            while (!arr.empty()){
                //cout << "Before: " << arr.back() << " ";
                int x = arr.back();
                arr.pop_back();
                update(x);
                x %= 9699690;
                //cout << "After: " << x << '\n';
                test(x);
                counters[i]++;
            }
            //cout << endl;
        }
    }
    f_max = 0, s_max = 0;
    for(auto &counter: counters){
        if(counter > f_max){
            s_max = f_max;
            f_max = counter;
        }
        else if(counter > s_max){
            s_max = counter;
        }
    }
    cout <<"Part 2: " << static_cast<long long>(f_max) * static_cast<long long>(s_max) << endl;
}