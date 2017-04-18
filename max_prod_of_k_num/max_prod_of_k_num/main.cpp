//
//  main.cpp
//  max_prod_of_k_num
//
//  Created by Lei Duan on 4/9/17.
//  Copyright © 2017 Lei Duan. All rights reserved.
//

#include <iostream>
#include <vector>
using namespace std;


int min_(int a, int b, int c, int d){
    return min(a,min(min(b,c),d));
}
int max_(int a, int b, int c, int d){
    return max(a,max(max(b,c),d));
}
int maxprod(vector<int>& nums){
    vector<pair<int, int>> dp(4);
    dp = {{INT_MAX, INT_MIN},{1,1},{1,1},{1,1}};
    
    for(auto n : nums){
        for(int i = 1; i < 4; i ++){
            dp[i].first = min_(n, dp[i].first, dp[i - 1].first * n, dp[i - 1].second * n);
            dp[i].second = max_(n, dp[i].second, dp[i - 1].first * n, dp[i - 1].second * n);
        }
    }
    return dp[3].second;
}



int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    vector<int> v= {3,4,-100,13,-1,6};
    cout<<(maxprod(v))<<endl;
    
    return 0;
}
