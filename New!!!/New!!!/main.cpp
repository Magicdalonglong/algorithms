#include <iostream>
#include <map>
#include <unordered_map>
#include <sstream>
#include <string>
#include <vector>
#include <climits>

using namespace std;

class Solution {
public:
    vector<vector<int>> matrixReshape(vector<vector<int>>& nums, int r, int c) {
        if(nums.empty()) return nums;
        vector<vector<int>> res (r, vector<int>(c));
        int x = 0, m = nums.size(), n = nums[0].size();
        if(m * n != r * c) return nums;
        for ( int i = 0; i < r; i++ ){
            for ( int j = 0; j < c; j++ ){
                cout<<i<<" "<<j<<",  ";
                cout<<(x / n)<<" "<<x % n<<endl;
                res[i][j] = nums[x / n][x++ % n];
            }
        }
        return res;
    }
};
#ifndef __main__
#define __main__

int main(int argc, char* argv[]) {
    Solution s;
    vector<vector<int>> nums = {{1,2}, {3,4}};
    auto res = s.matrixReshape(nums, 1, 4);
    
    for(auto r : res){
        for(auto c : r) cout<<c<<" ";
        cout<<endl;
    }
    
}

#endif


