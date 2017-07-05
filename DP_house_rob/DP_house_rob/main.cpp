//
//  main.cpp
//  DP_house_rob
//
//  Created by Lei Duan on 5/9/17.
//  Copyright © 2017 Lei Duan. All rights reserved.
//

#include <iostream>
#include <vector>
#include <stack>
#include <unordered_map>

using namespace std;

struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
 
class Solution {
public:
    int islandPerimeter(vector<vector<int>>& grid) {
        
        for(int i = 0; i < grid.size(); i++)
            for(int j = 0; j < grid[0].size(); j++){
                if(grid[i][j] == 1) return helper(grid, i, j);
            }
        return 1;
    }
    int helper(vector<vector<int>>& nums, int i, int j){
        int m = nums.size(), n = nums[0].size(), res = 0;
        pair<int, int> step[4] = {{1, 0},{-1, 0}, {0, 1}, {0, -1}};
        stack<int> stk;
        stk.push(i * n + j);
        nums[i][j] = -1;
        while(stk.size()){
            int x = stk.top() / n, y = stk.top() % n; stk.pop();
           
            for(auto s : step){
                int dx = x + s.first, dy = y + s.second;
                if(dx < 0 || dx >= m || dy < 0 || dy >= n || nums[dx][dy] == 0) res++;
                else {
                    nums[i][j] = -1;
                    stk.push(dx * n + dy);
                }
            }
        }
        return res;
    }
};

int main(int argc, const char * argv[]) {
    // insert code here...
    vector<vector<int>> nums = {{1, 1}, {1, 1}};
    
    string* res = new string[12];
    cout<<sizeof(res);
    
    std::cout << "\nHello, World!\n";
    
    
    return 0;
}
