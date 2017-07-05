//
//  main.cpp
//  pg_interview
//
//  Created by Lei Duan on 6/12/17.
//  Copyright © 2017 Lei Duan. All rights reserved.
//

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>

using namespace std;

struct node {
    char val;
    vector<node*> neighbor;
    node(char v) : val(v) {}
};

node* search1(node* root, char v) {
    unordered_set<node*> hash;
    queue<node*> q;
    q.push(root);
    while(q.size()) {
        node* cur = q.front();
        q.pop();
        if(cur -> val == v) return cur;
        for(auto nei : cur -> neighbor) {
            if(hash.count(nei)) continue;
            q.push(nei);
        }
    }
    return NULL;
}

bool dfs(node* cur, string& s, int index, vector<node*>& res) {
    res.push_back(cur);
    if(res.size() == s.size()) return 1;
    for(auto nei : cur -> neighbor) {
        if(nei -> val == s[index + 1]) {
            if(dfs(nei, s, index + 1, res)) return 1;
        }
    }
    res.pop_back();
    return 0;
    
}
vector<node*> search(node* root, string s) {
    
    node* start = search1(root, s[0]);
    vector<node*> res;
    if(dfs(start, s, 0, res))
        return res;
    else return {};
}

int main(int argc, const char * argv[]) {
    // insert code here...
    node*
    std::cout << "Hello, World!\n";
    return 0;
}
