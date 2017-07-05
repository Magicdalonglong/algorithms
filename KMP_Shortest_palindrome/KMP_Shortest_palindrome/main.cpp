//
//  main.cpp
//  KMP_Shortest_palindrome
//
//  Created by Lei Duan on 4/26/17.
//  Copyright © 2017 Lei Duan. All rights reserved.
//

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    string shortestPalindrome(string s) {
        int len = s.size(), i, m;
        string rs = s;
        reverse(rs.begin(), rs.end());
        string ls = s + "*" + rs;
        vector<int> dp(ls.size(), 0);
        for(i = 1, m = 0; i < ls.size(); i++){
            if(ls[i] == ls[m]) dp[i] = ++m;
            else {
                while(m > 0 && ls[m] != ls[i]) m = dp[m - 1];
                dp[i] = m += (ls[i] == ls[m]);
            }
        }
        
        for(auto l : ls)cout<<l<<" ";
        cout<<endl;
        for(auto d : dp)cout<<d<<" ";
        cout<<endl;
        return rs.substr(0, len - m) + s;
    }
};


int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    string s = "babbbabbaba";
    Solution so;
    auto res = so.shortestPalindrome(s);
    return 0;
}
