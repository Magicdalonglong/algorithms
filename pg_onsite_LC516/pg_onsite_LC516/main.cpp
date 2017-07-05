//
//  main.cpp
//  pg_onsite_LC516
//
//  Created by Lei Duan on 6/18/17.
//  Copyright © 2017 Lei Duan. All rights reserved.
//

#include <iostream>
#include <vector>

using namespace std;


int helper(vector<vector<int>>& mem, string& s, int l, int r) {
    if(l > r || mem[l][r] > 0) return mem[l][r];
    if(l == r) return (mem[l][r] = 1);
    if(s[l] ==s[r]) {
        return (mem[l][r] = helper(mem, s, l + 1, r - 1) + 2);
    }else {
        return (mem[l][r] = max(helper(mem, s, l + 1, r), helper(mem, s, l, r - 1)));
    }
}


int longestPalindromeSubseq(string s) {
    int len = s.size();
    vector<vector<int>> mem(len, vector<int> (len, 0));
    return helper(mem, s, 0, len - 1);
}

int main(int argc, const char * argv[]) {
    // insert code here...
    cout<<longestPalindromeSubseq("aa");
    return 0;
}
