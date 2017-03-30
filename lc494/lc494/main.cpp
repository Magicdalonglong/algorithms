//
//  main.cpp
//  lc494
//
//  Created by Lei Duan on 2/14/17.
//  Copyright © 2017 Lei Duan. All rights reserved.
//

#include <iostream>
#include <vector>
using namespace std;


int subsetSum(vector<int>& nums, int s) {
    vector<int> dp (s+1,0);
    dp[0] = 1;
    for (int n : nums)
        for (int i = s; i >= n; i--)
            dp[i] += dp[i - n];
    return dp[s];
}
int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    vector<int> v = {1,2,3,4,5};
    //123
    //24
    //15
    cout<<subsetSum(v, 6);
    return 0;
}
