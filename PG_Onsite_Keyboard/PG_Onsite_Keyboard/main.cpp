//
//  main.cpp
//  PG_Onsite_Keyboard
//
//  Created by Lei Duan on 6/16/17.
//  Copyright © 2017 Lei Duan. All rights reserved.
//

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int key(int n) {

    vector<int> dp(n + 1);
    for(int i = 1; i < 7; i++) dp[i] = i;
    
    for(int i = 7; i <= n; i++){
        int res = 0;
        for(int b = i - 3; b >= 1; b--) {
            res = max(res, (i - b - 1) * dp[b]);
        }
        dp[i] = res;
    }
    return dp.back();
}
int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    for(int i = 1; i < 100; i++){
        cout << i << ": " << key(i) << " " << key(i) << endl;
    }
    
    return 0;
}
