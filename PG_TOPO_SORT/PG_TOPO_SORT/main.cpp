//
//  main.cpp
//  PG_TOPO_SORT
//
//  Created by Lei Duan on 7/1/17.
//  Copyright © 2017 Lei Duan. All rights reserved.
//

#include <vector>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <queue>
using namespace std;

typedef map<char, set<char, greater<char>>, greater<char>> Gragh;
struct cmp {
    bool operator()(const pair<char, int>& p1, const pair<char, int>& p2) const{
        if(p1.second != p2.second) return p1.second > p2.second;
        else return p1.first > p2.first;
    }
};
typedef priority_queue<pair<char, int>, vector<pair<char, int>>, cmp> Heap; // char, outde

bool helper(Gragh& map, char cur, string& res, vector<int>& mark) {
    if(mark[cur - 97] == 1) return 0;
    if(mark[cur - 97] == 2) return 1;
    mark[cur - 97] = 1;
    for(auto nei : map[cur]) {
        if(helper(map, nei, res, mark) == 0) return 0;
    }
    mark[cur - 97] = 2;
    res.push_back(cur);
    return 1;
}

string topo(vector<string>& strs) {
    Gragh map;
    vector<int> mark(26, -1); // 2 = visited, 1 = visiting, 0 = not visited, -1 = not exist
    
    for(auto& str: strs) {
        for(int i = 0; i < str.size(); i++) {
            mark[str[i] - 97] = 0;
            if(i > 0 && str[i] != str[i - 1])
                map[str[i - 1]].emplace(str[i]);
        }
    }
    
    string res;
    
    for(int i = 25; i >=0; i--) {
        if(mark[i] == 0 && helper(map, i + 97, res, mark) == 0) return "/Invalid/";
    }
    
    reverse(res.begin(), res.end());
    for(int i = 0; i < 26; i++) {
        if(mark[i] == 0) res.push_back(i + 97);
    }
    return res;
}
string topo2(vector<string>& strs) {
    unordered_map<char, set<char>> map;
    unordered_map<char, int> inde;
    for(auto& str: strs) {
        for(int i = 0; i < str.size(); i++) {
            map[str[i]];
            if(i > 0 && str[i] != str[i - 1]){
                if(map[str[i - 1]].count(str[i]) == 0){
                    map[str[i - 1]].emplace(str[i]);
                    inde[str[i]] ++;
                }
            }
        }
    }
    Heap pq;
    for(auto in : inde) {
        pq.emplace(in);
    }
    
    string res;
    
    while(pq.size()) {
        if(pq.top().second != 0) return "";
        char cur = pq.top().first; pq.pop();
        for(auto nei : map[cur]) {
            inde[nei]--;
        }
        res.push_back(cur);
    }
    return res;
}


int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    vector<string> strs = {"abc", "bz", "fc","be", "gfqqqqp"};
    cout<<topo(strs);
    
    return 0;
}
