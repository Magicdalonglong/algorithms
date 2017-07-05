//
//  main.cpp
//  BST_to_list
//
//  Created by Lei Duan on 4/19/17.
//  Copyright © 2017 Lei Duan. All rights reserved.
//

#include <iostream>
#include <queue>
#include <stack>
using namespace std;

int getweight(int a, int b){
    return 1;
}
vector<int> directfriend(int a){
    return {1,2};
}
class s{
public:

vector<int> ws;
vector<int> ds;

void helper(int dist, int weight, int w, int k, int cur, vector<int>& res,vector<bool>& path){
    if(ws[cur] >= weight && ds[cur] <= dist) return;
    ws[cur] = weight;
    ds[cur] = dist;
    
    path[cur] = 1;
    res.push_back(cur);
    if(dist >= k) return ;
    for(auto f : directfriend(cur)){
        int we = weight + getweight(f, cur);
        if(we >= w && path[f] == 0) helper(dist + 1, we, w, k, f, res, path);
    }
    path[cur] = 0;
}

vector<int> find_friend(int w, int k, int ur){
    vector<int> res;
    vector<bool> path;
   
    helper(0, 0, w, k, ur, res, path);
    return res;
}
};
int main(int argc, const char * argv[]) {
   
    return 0;
}
