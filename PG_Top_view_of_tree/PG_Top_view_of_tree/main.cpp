//
//  main.cpp
//  PG_Top_view_of_tree
//
//  Created by Lei Duan on 6/18/17.
//  Copyright © 2017 Lei Duan. All rights reserved.
//

#include <iostream>
#include <vector>
#include <queue>
#include <map>
using namespace std;

struct node {
    int val;
    node* left, *right;
    node(int v) : val(v), left(NULL), right(NULL) {}
};

void top_view_of_tree(node* r) {
    
    queue<pair<node*, int>> q;
    q.emplace(r, 0);
    map<int, int> map;
    while(q.size()) {
        node* cur = q.front().first;
        int index = q.front().second; q.pop();
        if(map.count(index) == 0) {
            map[index] = cur -> val;
        }
        
        if(cur -> right) q.emplace(cur -> right, index + 1);
        if(cur -> left) q.emplace(cur -> left, index - 1);
        
        
        
    }
   for(auto m : map) cout<<m.second<<" ";
}
void top_view_tree2(node* r) {
    if(r == NULL) return;
    queue<pair<node*, int>> q;
    vector<int> right, left;
    q.emplace(r, 0);
    while (q.size()) {
        auto item = q.front(); q.pop();
        if(item.second < 0) {
            if(abs(item.second) > left.size()) {
                left.push_back(item.first -> val);
            }
        }else {
            if(item.second >= right.size()) {
                right.push_back(item.first -> val);
            }
        }
        if(item.first -> left) q.emplace(item.first -> left, item.second - 1);
        if(item.first -> right) q.emplace(item.first -> right, item.second + 1);
    }
    
    for(int i = left.size() - 1; i >= 0; i--) cout<<left[i]<<" ";
    for(auto n : right) cout<<n<<" ";
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    node* r = new node(5);
    r -> left = new node(3);
    r -> left -> left = new node(1);
    r -> left -> right = new node(11);
    r -> left -> right -> right = new node(7);
    r -> left -> right -> left = new node(-1);
    r -> left -> right -> left -> left = new node(-13);
    r -> left -> right -> left -> left -> left = new node(-15);
    r -> right = new node(4);
    top_view_of_tree(r);
    return 0;
}
