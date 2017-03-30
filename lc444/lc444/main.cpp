//
//  main.cpp
//  lc444
//
//  Created by Lei Duan on 2/28/17.
//  Copyright © 2017 Lei Duan. All rights reserved.
//

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;
bool sequenceReconstruction(vector<int>& org, vector<vector<int>>& seqs) {
    if (seqs.size() == 0) return false;
    int n = org.size(), count = 0;
    unordered_map<int, unordered_set<int>> graph;   // record parents
    vector<int> degree(n+1, 0); // record out degree
    for (auto s : seqs) {   // build graph
        for (int i = s.size()-1; i >= 0; --i) {
            if (s[i] > n or s[i] < 0) return false; // in case number in seqs is out of range 1-n
            if (i > 0 and !graph[s[i]].count(s[i-1])) {
                graph[s[i]].insert(s[i-1]);
                if (degree[s[i-1]]++ == 0) count ++;
            }
        }
    }
    if (count != n-1) return false; // all nodes should have degree larger than 0 except the last one
    for (int i = n-1; i >= 0; --i) {    // topological sort
        if (degree[org[i]] > 0) return false;   // the last node should have 0 degree
        for (auto p : graph[org[i]])
            if (--degree[p] == 0 and p != org[i-1]) // found a node that is not supposed to have 0 degree
                return false;
    }
    return true;
}



bool sequenceReconstruction2(vector<int>& org, vector<vector<int>>& seqs) {
    if(seqs.empty())return 0;
    const int n = org.size();
    vector<int> degree(n+1,-1);  //out- degree  , -1 means never appear in seqs
    vector<vector<int>> map(n+1);   // index = 1 val = {2,3,4}  means 2 3 4 are parents of 1
    int count=0;
    for(auto &s: seqs){
        for(int i=s.size()-1;i>=0;i--){
            if(s[i]>n || s[i]<=0)return 0;
            if(degree[s[i]]==-1)degree[s[i]] = 0;
            if(i==0)continue;
            if(degree[s[i]]==-1)degree[s[i]] = 0;
            map[s[i]].emplace_back(s[i-1]);
            if(degree[s[i-1]]++ == 0)count++;
        }
    }
    for(int i=1;i<=n;i++)
        if(degree[i]==-1)return 0;
    if(count!=n-1)return 0;
    
    for(int i=n-1;i>=0;i--){
        if(degree[org[i]]>0)return 0;
        for(auto p:map[org[i]])
            if(--degree[p]==0&&p!=org[i-1])return 0;
        //any parent that is not cur node's directly parents, and it has only one out degree, we return 0;
    }
    return 1;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    vector<int> o = {1,2,3};
    vector<vector<int>> se = {{1,2},{2,3},{1,3}};
    
    cout<<sequenceReconstruction(o, se);
    cout<<sequenceReconstruction2(o, se);
    return 0;
}
