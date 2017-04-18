//
//  main.cpp
//  merge_interval
//
//  Created by Lei Duan on 4/9/17.
//  Copyright © 2017 Lei Duan. All rights reserved.
//

#include <unordered_set>
#include <map>
#include <iostream>
#include <vector>
#include <numeric>
using namespace std;
struct Interval{
    int start;
    int end;
    Interval(int a, int b): start(a), end(b){}
};

int trapRainWater(vector<vector<int>>& heightMap) {
    if(heightMap.empty()) return 0;
    int m = heightMap.size(), n = heightMap[0].size(), res = 0;
    pair<int, int> step[4] = {{0,1}, {0,-1}, {1,0},{-1,0}};
    unordered_set<int> set;
    multimap<int, pair<int,int>> map;
    for(int i = 0; i < m ; i++){
        map.emplace(heightMap[i][0],make_pair(i,0)); set.emplace(i * n);
        map.emplace(heightMap[i][n - 1],make_pair(i,n - 1));set.emplace(i * n + n - 1);
    }
    for(int j = 1; j < n - 1; j++){
        map.emplace(heightMap[0][j],make_pair(0,j)); set.emplace(j);
        map.emplace(heightMap[m - 1][j],make_pair(m - 1,j)); set.emplace((m - 1) * n +j);
    }
    while(set.size() < m * n){
        auto pos = map.begin() -> second;
        int bar = map.begin() -> first;
        map.erase(map.begin());
        for(auto s : step){
            int x = pos.first + s.first;
            int y = pos.second + s.second;
            if(x < 0 || x >= m || y < 0 || y >= n || set.count(x * n + y))continue;
            set.emplace(x * n + y);
            res += max(0, bar - heightMap[x][y]);
            map.emplace(max(bar, heightMap[x][y]), make_pair(x, y));
        }
    }
    return res;
    
}

int minMeetingRooms(vector<Interval>& intervals) {
    int min_  = INT_MAX, max_ = INT_MIN, res = 0, cur = 0;
    for(auto& in : intervals)
    {
        min_ = min(min_, in.start);
        max_ = max(max_, in.end);
    }
    vector<pair<int, int>> scan(max_ - min_ + 1,make_pair(0,0));
    for(auto& in : intervals){
        scan[in.start - min_].first++;
        scan[in.end - min_].second--;
    }
    for(auto& in : scan){
        cur -= in.second;
        cur += in.first;
        res = max(cur, res);
    }
    return res;
    
}

int main(int argc, const char * argv[]) {
    // insert code here...
    vector<string> m = {"XXXX","XOOX","XXOX","XOXX"};
    vector<vector<int>> h = {{1,4,3,1,3,2},{3,2,1,3,2,4},{2,3,3,2,3,1}};
    cout<<trapRainWater(h);
    cout<<endl;
    
        return 0;
}
