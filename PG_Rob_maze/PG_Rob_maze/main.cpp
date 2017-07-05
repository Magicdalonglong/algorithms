//
//  main.cpp
//  Pg_Maze
//
//  Created by Lei Duan on 6/11/17.
//  Copyright © 2017 Lei Duan. All rights reserved.
//

#include <iostream>
#include <vector>
#include <map>
#include <time.h>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <locale>
#include <cctype>

using namespace std;
// 0 = water 1 = land 2 = start 3 = goal  lowercase = key   uppercase = door


/*
 '02a11'
 '0100A',
 '01001',
 '03001',
 '01111']
 */

bool helper(vector<string>& maze, vector<vector<int>>& mark, int i , int j, vector<pair<int, int>>& res, int remain) {
    int m = maze.size(), n = maze[0].size(), start;
    
    remain -= mark[i][j] ++ == 0;
    res.emplace_back(i, j);
    if(remain == 0) {
        return 1;
    }
    
    pair<int, int> step[4] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    int next = INT_MAX;
    pair<int, int> nextstep;
    for(auto s : step) {
        int x = i + s.first, y = j + s.second;
        if(x < 0 || x >= m || y < 0 || y >= n || maze[x][y] == '0') continue;
        if(mark[x][y] < next){
            nextstep = {x, y};
            next = mark[x][y];
        }
    }
    
    helper(maze, mark, nextstep.first, nextstep.second, res, remain);
   
    
    return 0;
}
vector<pair<int, int>> find_path(vector<string>& maze) {
    int m = maze.size(), n = maze[0].size(), start;
    vector<vector<int>> mark(m, vector<int> (n, 0));
    int remain = 0;
    for(int i = 0; i < m; i++)
    for(int j = 0; j < n; j++){
        if(maze[i][j] != '0') remain++;
        if(maze[i][j] == '2') start = i * n + j;
    }
    
    vector<pair<int, int>> res ;
    
    helper(maze, mark, start / n, start % n, res, remain);
    return res;
}


pair<int, int> find_shortest_path(vector<vector<int>>& mark, vector<string>& maze, int i , int j, vector<pair<int, int>>& res, int remain) {
    
    int m = maze.size(), n = maze[0].size();
    pair<int, int> tar;
    queue<pair<int, vector<pair<int, int>>>> q;
    pair<int, int> step[4] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    q.emplace(i * n + j, vector<pair<int, int>>{});
    mark[i][j]++;
    while (q.size()) {
        int x = q.front().first;
        auto path = q.front().second; q.pop();
        
        if(mark[x / n][x % n] == 0){
            for(auto p : path) {
                res.push_back(p);
            }
            return {x / n, x % n};
        }
        path.emplace_back(x / n, x % n);
        for(auto s : step) {
            int dx = x / n + s.first, dy = x % n + s.second;
            if(dx < 0 || dx >= m || dy < 0 || dy >= n || maze[dx][dy] == '0' || mark[dx][dy] == 2) continue;
            q.emplace(dx * n + dy, path);
        }
    }
    
    return tar;
}

bool helper2(vector<string>& maze, vector<vector<int>>& mark, int i , int j, vector<pair<int, int>>& res, int remain) {
    int m = maze.size(), n = maze[0].size(), start;
    
    remain --;
    res.emplace_back(i, j);
    if(remain == 0) {
        return 1;
    }
    
    pair<int, int> step[4] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    int next = INT_MAX;
    pair<int, int> nextstep;
    for(auto s : step) {
        int x = i + s.first, y = j + s.second;
        if(x < 0 || x >= m || y < 0 || y >= n || maze[x][y] == '0') continue;
        if(mark[x][y] == 0){
            nextstep = {x, y};
            next = mark[x][y];
        }
    }
    if(next == INT_MAX) {
        nextstep = find_shortest_path(mark, maze, i, j, res, remain);
    }
    
    helper(maze, mark, nextstep.first, nextstep.second, res, remain);
    
    
    return 0;
}


vector<pair<int, int>> find_path2(vector<string>& maze) {
    int m = maze.size(), n = maze[0].size(), start;
    vector<vector<int>> mark(m, vector<int> (n, 0));
    int remain = 0;
    for(int i = 0; i < m; i++)
        for(int j = 0; j < n; j++){
            if(maze[i][j] != '0') remain++;
            if(maze[i][j] == '2') start = i * n + j;
        }
    
    vector<pair<int, int>> res ;
    
    helper2(maze, mark, start / n, start % n, res, remain);
    return res;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    
    vector<string> ma = {
        "0210",
        "0a00"
    };
    
    vector<string> ma1 = {
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
    
    vector<string> ma6 = {
        "b2a11",
        "1111A",
        "11111",
        "11111",
        "11111"};
    
    vector<string> ma7 = {
        "b1a11",
        "1111A",
        "11211",
        "11111",
        "11111"};
    
    
    vector<vector<string>> test_cases;
    
    test_cases.emplace_back(ma);
        test_cases.emplace_back(ma1);
        test_cases.emplace_back(ma2);
        test_cases.emplace_back(ma3);
        test_cases.emplace_back(ma4);
        test_cases.emplace_back(ma5);
        test_cases.emplace_back(ma6);
    test_cases.emplace_back(ma7);
    
    for(auto t : test_cases){
        time_t s = time(0);
        for(auto row : t){
            for(auto c : row) cout<<c<<" ";
            cout<<endl;
        }
        
        auto res = find_path(t);
        double run = difftime(time(0), s);
        cout<<"Solution(time: "<<run<<", step: "<<res.size()<<"):\n";
        for(auto r : res)cout<<r.first<<","<<r.second<<",  ";
        cout<<endl;
        auto res2 = find_path2(t);
        double run2 = difftime(time(0), s);
        cout<<"Solution(time: "<<run2<<", step: "<<res2.size()<<"):\n";
        for(auto r : res2)cout<<r.first<<","<<r.second<<",  ";
 
        
        
        cout<<endl;cout<<endl;
    }
    std::cout << "Hello, World!\n";
    return 0;
}
