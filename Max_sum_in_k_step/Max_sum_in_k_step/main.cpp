//
//  main.cpp
//  Max_sum_in_k_step
//
//  Created by Lei Duan on 4/22/17.
//  Copyright © 2017 Lei Duan. All rights reserved.
//

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;

int call = 0;

int max_sum_path(vector<vector<int>>& matrix, int i, int j, int k){
    int  m = matrix.size(), n = matrix[0].size();
    int count = 1; // for counting steps from 1 to k
    
    
    /*** using one dimension index representing positions ***/
    
    // dp[i][j] means max sum can get at i step in position j
    vector<vector<int>> dp (k + 1, vector<int>(m * n, 0));
    pair<int, int> step[4] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    dp[0][i * n + j] = matrix[i][j];
    queue<int> q; //pos
    q.emplace(i * n + j);
    while(count <= k){
        int len = q.size();
        unordered_map<int, int> cache;  // position,  val
        while (len--) {
            int i = q.front() / n, j = q.front() % n;
            q.pop();
            for(auto s : step){
                int x = i + s.first, y = j + s.second;
                if(x < 0 || x >= m || y < 0 || y >= n) continue;
                int old = cache[x * n + y];
                /*** 
                 updating overlop position instead of
                 pushing all possible steps into the queue
                 as a normal BFS, this is the key to
                 lower complexity from pow(4, k) to (m * n * k)
                 ***/
                cache[x * n + y] = max(old, dp[count - 1][i * n + j] + matrix[x][y]);
                dp[count][x * n + y] = cache[x * n + y];
            }
        }
        for(auto c : cache)q.emplace(c.first);
        count++;
    }
    return *max_element(dp.back().begin(), dp.back().end());
}

int main(int argc, const char * argv[]) {
    // insert code here...
    int n = 1000;
    vector<vector<int>> m = {
        {4},{5},{1},{1},{1000}};
    auto res = max_sum_path(m, 0, 0, 3);
    cout<<"res is "<<res<<endl;
    return 0;
}
