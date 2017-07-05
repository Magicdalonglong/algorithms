//
//  main.cpp
//  Pg_Maze
//
//  Created by Lei Duan on 6/11/17.
//  Copyright © 2017 Lei Duan. All rights reserved.
//

#include <iostream>
#include <vector>
#include <time.h>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <locale>
#include <cctype>

using namespace std;
// 0 = water 1 = land 2 = start 3 = goal  lowercase = key   uppercase = door

struct info {
    int x, y;
    unordered_set<char> keys;
    vector<pair<int, int>> path;
    unordered_set<int> cur_path;
    info(int a, int b): x(a), y(b) {}
    info(int a, int b, unordered_set<char> k, vector<pair<int, int>> p, unordered_set<int> cur) : x(a), y(b), keys(k), path(p), cur_path(cur) {}
    info() {}
};
/*
 '02a11'
 '0100A',
 '01001',
 '03001',
 '01111']
 */
vector<pair<int, int>> find_path(vector<string>& maze) {
    int m = maze.size(), n = maze[0].size(), start = -1, dest = -1;
    
    for(int i = 0; i < m; i++)
        for(int j = 0; j < n; j++){
            if(maze[i][j] == '2') start = i * n + j;
            if(maze[i][j] == '3') dest = i * n + j;
        }
    int space = 1;
    queue<info*> q;
    pair<int, int> step[4] = {{1,0},{-1, 0}, {0, 1}, {0, -1}};
    info* init = new info(start / n, start % n);
    q.push(init);
    while(q.size()) {
        int len = q.size();
        while(len--) {
            info* cur = q.front(); q.pop();
            auto path = cur -> path;
            auto curpath = cur -> cur_path;
            auto keys = cur -> keys;
            
            path.emplace_back(cur -> x, cur -> y);
            curpath.emplace(cur -> x * n + cur -> y);
            
            if(cur -> x * n + cur -> y == dest) return path;
            
            if(maze[cur -> x][cur -> y] <= 'z' && maze[cur -> x][cur -> y] >= 'a') {
                keys.emplace(maze[cur -> x][cur -> y]);
                curpath.clear();
            }
            
            for(auto s : step) {
                int x = cur -> x + s.first, y = cur -> y + s.second;
                if(x < 0 || x >= m || y < 0 || y >= n || maze[x][y] == '0') continue;
                if(maze[x][y] <= 'Z' && maze[x][y] >= 'A' && keys.count(tolower(maze[x][y])) == 0) {
                    continue;
                }
                if(curpath.count(x * n + y)) continue;
            
                q.emplace(new info(x, y, keys, path, curpath));
            }
        }
    }
    
    
    return {};
}


int main(int argc, const char * argv[]) {
    // insert code here...
    vector<string> ma = {
        "02a11",
        "0100A",
        "01001",
        "03001",
        "01111"};
    vector<string> ma2 = {
        "02a11",
        "0100A",
        "01001",
        "01003",
        "01111"};
    
    vector<string> ma3 = {
        "02a11",
        "A100A",
        "3B001",
        "01001",
        "0111b"};
    
    vector<string> ma4 = {
        "b2a11",
        "0100A",
        "1Z001",
        "B1001",
        "1301z"};
    
    vector<string> ma5 = {
        "b2a11",
        "0100A",
        "1Z001",
        "BC001",
        "1301z"};
    
    
    vector<vector<string>> test_cases;
    
    test_cases.emplace_back(ma2);
    test_cases.emplace_back(ma);
    test_cases.emplace_back(ma3);
    test_cases.emplace_back(ma4);
    test_cases.emplace_back(ma5);
    
    for(auto t : test_cases){
        time_t s = time(0);
        for(auto row : t){
            for(auto c : row) cout<<c<<" ";
            cout<<endl;
        }
        
        auto res = find_path(t);
        double run = difftime(time(0), s);
        cout<<"Solution(time: "<<run<<", step: "<<res.size() - 1<<"):\n";
        for(auto r : res)cout<<r.first<<","<<r.second<<",  ";
        cout<<endl;cout<<endl;
    }
    std::cout << "Hello, World!\n";
    return 0;
}
