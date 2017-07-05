//
//  main.cpp
//  traverse_matrix
//
//  Created by Lei Duan on 4/22/17.
//  Copyright © 2017 Lei Duan. All rights reserved.
//

#include <iostream>
#include <vector>

using namespace std;
int k = 0;

bool helper(vector<vector<int>>& res, int m , int n, int i, int j, int step, bool hash[]){
    k ++;
    res[i][j] = ++step;
    if(step == m * n){
        return 1;
    }
    hash[i * n + j] = 1;
    pair<int, int> direct[4] = {{0,1},{0,-1},{1,0},{-1,0}};
    
    for(auto d : direct){
        int x = i + d.first, y = j + d.second;
        if(x < 0 || x >= m || y < 0 || y >= n || hash[x * n + y]) continue;
        
        if(helper(res, m, n , x, y, step, hash)) return 1;
    }
    hash[i * n + j] = 0;
    res[i][j] = -1;
    return 0;
}

vector<vector<int>> traverse(int m , int n, int i , int j){
    vector<vector<int>> res(m, vector<int>(n,-1));
    bool hash[m * n];
    fill_n(hash, m * n, false);
    cout<<"can? : "<<helper(res, m, n, i, j, 0, hash)<<", "<<"call count: "<< k<< endl;
    
    return res;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    auto res = traverse(7,7,1,1);
    for(auto r : res){
        for(auto c : r)
            cout<<c<<" ";
        cout<<endl;
    }
    std::cout << "\nHello, World!\n";
    return 0;
}
