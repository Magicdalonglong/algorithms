#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
using namespace std;
//
//  main.cpp
//  Pg_Maze
//
//  Created by Lei Duan on 6/11/17.
//  Copyright © 2017 Lei Duan. All rights reserved.
//

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <locale>
#include <cctype>


// 0 = water 1 = land 2 = start 3 = goal  lowercase = key   uppercase = door

struct info {
    unordered_set<char> keys;
    vector<pair<int, int>> path;
    info(unordered_set<char> k, vector<pair<int, int>> p) : keys(k), path(p) {}
    info() {}
};
/*
 '02a11'
 '0100A',
 '01001',
 '03001',
 '01111']
 */
class Solution {
public:
    vector<int> largestDivisibleSubset(vector<int>& nums) {
        if(nums.empty()) return {};
        int len = nums.size(), reslen = 0, index = 0;
        vector<pair<int, int>> dp(len); // len, pre

        for(int i = 0; i < len; i++) {
            for(int j = i - 1; j >= 0; j--) {
                if(nums[i] % nums[j] == 0 && dp[j].first + 1 > dp[i].first) {
                    dp[i].first = dp[j].first + 1;
                    dp[j].second = nums[j];
                }                
            }
            if(dp[i].first == 0) {
                dp[i].first = 1;
                dp[i].second = i;
            }
            if(reslen < dp[i].first) {
                reslen = dp[i].first;
                index = i;                
            }
        }
        vector<int> res;
        for( int i = index; i != dp[i].second; i = dp[i].second) {
            res.push_back(nums[i]);
        }
        return res;
    }
};


int main(int argc, const char * argv[]) {
    // insert code here...
    stringstream ss;
    // ss << "1 ";
    // ss << "2 ";
    // ss << "3 ";
     ss << " ";
    while(!ss.eof()) {
        string val ;
        ss >> val;
        cout<<val<<endl;

    }
    return 0;
}


