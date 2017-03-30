//
//  main.cpp
//  lc441
//
//  Created by Lei Duan on 2/6/17.
//  Copyright © 2017 Lei Duan. All rights reserved.
//


#include <iostream>

class Solution {
public:
    int arrangeCoins(int n) {
        
        int l=1,r=n;
        while(l<r-1){
            int m = l+(r-l)/2;
            int sum = comp(m);
            if(sum==-1)r=m;
            else if(sum>n)r=m;
            else if(sum<n)l=m;
            else return m;
            
        }
        if(comp(r)>n)return l;
        return comp(r);
        
    }
    double comp(double n){
        
        double res = n*(n+1)/2;
        if(res>INT_MAX) return -1;
        return res;
    }
};
int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    Solution s;
    std::cout<<s.arrangeCoins(15);
    return 0;
}
