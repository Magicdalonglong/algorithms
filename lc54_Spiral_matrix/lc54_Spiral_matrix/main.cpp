//
//  main.cpp
//  lc54_Spiral_matrix
//
//  Created by Lei Duan on 4/9/17.
//  Copyright © 2017 Lei Duan. All rights reserved.
//

#include <iostream>
#include <vector>
using namespace std;

vector<int> spiralOrder(vector<vector<int>>& matrix) {
    if(matrix.empty()) return {};
    int m = matrix.size();
    int n = matrix[0].size();
    vector<int> lens = {n, m - 1, n - 1, m - 2};
    int i = 0, j = 0;
    vector<pair<int, int>> step = {{0,1},{1,0},{0,-1},{-1,0}}; // right down left up
    vector<int> res;
    
    for(int p = 0;; p++){
        int k = p % 4;
        if(lens[k] <=0 ) return res;
        for(int count = 0; count < lens[k]; count ++, i += step[k].first, j += step[k].second)
            res.emplace_back(matrix[i][j]);
        i -= step[k].first; j -= step[k].second;
        i += step[(k + 1 )& 4].first; j += step[(k + 1 )& 4].second;
        lens[k] -= 2;
    }
    
    return res;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    vector<vector<int>> m = {{1,2,3},{4,5,6},{7,8,9}};
    auto res = spiralOrder(m);
    
    return 0;
}
