//
//  main.cpp
//  lc84
//
//  Created by Lei Duan on 5/4/17.
//  Copyright © 2017 Lei Duan. All rights reserved.
//

#include <iostream>
#include <vector>
#include <unordered_map>
#include <cmath>
#include <stack>
using namespace std;
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        stack<int> s;
        heights.push_back(0);
        s.push(-1);
        int res = 0;
        for(int i = 0; i < heights.size(); i++){
            if(s.top() == -1 || heights[s.top()] <= heights[i]) s.push(i);
            else{
                while(s.top() >= 0 && heights[s.top()] > heights[i]){
                    int pre = heights[s.top()]; s.pop();
                    res = max(res, pre * (i - s.top() - 1));
                }
                s.push(i);
            }
        }
        return res;
    }
};
int main(int argc, const char * argv[]) {
    // insert code here...
    vector<int> num = {2,1,5,6,2,3};
    Solution s;
    cout<<s.largestRectangleArea(num);
    std::cout << "\nHello, World!\n";
    return 0;
}
