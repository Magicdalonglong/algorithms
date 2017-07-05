//
//  main.cpp
//  PG_Onsite_Regular_express
//
//  Created by Lei Duan on 6/16/17.
//  Copyright © 2017 Lei Duan. All rights reserved.
//
#include <iostream>
#include <vector>

using namespace std;

bool isMatch(string s, string p) {
    int len1 = s.size(), len2 = p.size();
    vector<vector<bool>> dp ( len1 + 1, vector<bool> (len2 + 1, 0));
    dp[0][0] = 1;
    for( int j = 1; j <= len2; j ++){
        for( int i = 0; i <= len1; i ++) {
            if (p[j - 1] == '*')
            dp[i][j] = dp[i][j - 2] || i > 0 && (p[j - 2] == s[i - 1] || p[j - 2] == '.') && dp[i - 1][j];
            else dp[i][j] = i != 0 && (p[j - 1] == s[i - 1] || p[j - 1] == '.') && dp[i - 1][j - 1];
        }
    }
    return dp.back().back();
    
}
int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    vector<pair<string, string>> testcaset = {{"ab","c*a*b"}};//, {"asasd","a*s.*"}, {"s",".*"}, {"esaxsd","a.*"}};
    for(auto t : testcaset) {
        cout << t.first << ", " << t.second << " : " << isMatch(t.first, t.second) << endl;
    }
    return 0;
}
