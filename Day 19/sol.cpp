#include <bits/stdc++.h>
#include <fstream>
using namespace std;
set<vector<int>>seen;
void dfs(int curr_ore, int curr_clay, int curr_obsidian, int curr_geode,int orer, int cr, int obsr, int gr, int ore_r, int clay_r, pair<int, int> obs_r, pair<int ,int> geode_r,int &best, int time = 24){
    if (time == 0){
        best = max(best, curr_geode);
        return;
    }
    if (curr_ore < 0 || curr_clay < 0 || curr_obsidian < 0 || curr_geode < 0){
        return;
    }
    vector<int> state = {curr_ore, curr_clay, curr_obsidian, curr_geode, orer, cr, obsr, gr,time};
    if (seen.find(state) != seen.end()){
        return;
    }
    seen.insert(state);
    int max_ore = max(ore_r, max(clay_r, max(obs_r.first, geode_r.first)));
    /*
    cout << "Ore: " << curr_ore << " Ore Robots: " << orer << endl;
    cout << "Clay: " << curr_clay << " Clay Robots: " << cr << endl;
    cout << "Obsidian: " << curr_obsidian << " Obsidian Robots: " << obsr << endl;
    cout << "Geode: " << curr_geode << " Geode Robots: " << gr << endl;
    cout << "Best: " << best << endl;
    */
   if (curr_ore >= geode_r.first && curr_obsidian >= geode_r.second){
        dfs(curr_ore  + orer - geode_r.first, curr_clay + cr, curr_obsidian - geode_r.second + obsr, curr_geode + gr, orer, cr, obsr, gr + 1, ore_r, clay_r, obs_r, geode_r, best, time - 1);
        return;
    }
    else{
        if (obsr < geode_r.second && curr_ore >= obs_r.first && curr_clay >= obs_r.second){
            dfs(curr_ore + orer - obs_r.first, curr_clay - obs_r.second + cr, curr_obsidian + obsr, curr_geode + gr, orer, cr, obsr + 1, gr, ore_r, clay_r, obs_r, geode_r, best, time - 1);
        }
        if (orer < max_ore && curr_ore >= ore_r){
            dfs(curr_ore + orer - ore_r, curr_clay+ cr, curr_obsidian + obsr , curr_geode + gr, orer + 1, cr, obsr, gr, ore_r, clay_r, obs_r, geode_r, best, time - 1);
        }
        if (cr < obs_r.second && curr_ore >= clay_r){
            dfs(curr_ore + orer - clay_r, curr_clay+ cr, curr_obsidian + obsr, curr_geode+ gr, orer, cr + 1, obsr, gr, ore_r, clay_r, obs_r, geode_r, best, time - 1);
        }
        curr_ore += orer;
        curr_clay += cr;
        curr_obsidian += obsr;
        curr_geode += gr;
        dfs(curr_ore, curr_clay, curr_obsidian, curr_geode, orer, cr, obsr, gr, ore_r, clay_r, obs_r, geode_r, best, time - 1);
    }
}


int main(){
    fstream file;
    file.open("input.txt",ios::in);
    string line;
    vector<vector<int>> blueprints;
    while(file.peek() != EOF){
        getline(file, line);
        vector<int> row(7);
        //cout << line << endl;
        sscanf(line.c_str(), "Blueprint %d: Each ore robot costs %d ore. Each clay robot costs %d ore. Each obsidian robot costs %d ore and %d clay. Each geode robot costs %d ore and %d obsidian.", &row[0], &row[1], &row[2], &row[3], &row[4], &row[5], &row[6]);
        blueprints.push_back(row);
    }
    int res = 0;
    for(auto &row: blueprints){
        int b_num = row[0];
        int ore_cost = row[1];
        int clay_cost = row[2];
        pair<int ,int> obs_cost = {row[3], row[4]};
        pair<int, int> geode_cost = {row[5], row[6]};
        int max_ore = max(ore_cost, max(clay_cost, max(obs_cost.first, geode_cost.first)));
        int max_geode = 0;
        dfs(0, 0, 0, 0, 1, 0, 0, 0, ore_cost, clay_cost, obs_cost, geode_cost, max_geode);
        res += b_num * max_geode;
        cout << "Blueprint " << b_num << ": " << max_geode << endl;
        seen.clear();
    }
    cout << "Part 1: " << res << endl;
    res = 1;
    for(int i = 0; i < 3; i++){
        seen.clear();
        //cout << i << endl;
        int ore_cost = blueprints[i][1];
        int clay_cost = blueprints[i][2];
        pair<int ,int> obs_cost = {blueprints[i][3], blueprints[i][4]};
        pair<int, int> geode_cost = {blueprints[i][5], blueprints[i][6]};
        int max_ore = max(ore_cost, max(clay_cost, max(obs_cost.first, geode_cost.first)));
        int max_geode = 0;
        dfs(0, 0, 0, 0, 1, 0, 0, 0, ore_cost, clay_cost, obs_cost, geode_cost, max_geode, 32);
        res *= max_geode;
        cout << "Blueprint " << i + 1 << ": " << max_geode << endl;
    }
    cout << "Part 2: " << res << endl;
}