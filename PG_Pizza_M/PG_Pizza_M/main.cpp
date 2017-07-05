//
//  main.cpp
//  PG_Pizza_M
//
//  Created by Lei Duan on 6/25/17.
//  Copyright © 2017 Lei Duan. All rights reserved.
//

#include <iostream>
#include <vector>
using namespace std;


class Solution{
public:
    int len;
    int count;
     // dp[i][j] = how mush more i can got than u if i pick first from range i j.
    vector<vector<int>> dp;
    vector<int> pizza;
    Solution(vector<int>& pizza_){
        pizza = pizza_;
        len = pizza.size();
        dp.assign(len, vector<int>(len, INT_MIN));
    }
    int MaxAreapizza2() {
        count = 0;
        int res = 0, sum = 0;
        for(int i = 0;i < pizza.size(); i++) {
            sum += pizza[i];
            int oponnent = helper2(i + 1, i - 1);
            res = max(res, pizza[i] - oponnent);
        }
        cout<<"size :" <<pizza.size()<< " count: "<<count<<" ";
        return (sum + res) / 2;
    }
    // 0 1 2 3 4 5 6 7 8 9
    // helper(i, j) means
    // how mush more i can got than u if i pick first from range i j.
    int helper2(int x, int y) {
        count++;
        if(x < 0) x += len;
        else if(x >= len) x -= len;
        if(y < 0) y += len;
        else if(y >= len) y -= len;
        
        if(x == y) return pizza[x];
        return  max(pizza[x] - helper2(x + 1, y), pizza[y] - helper2(x, y - 1));
    }
    int MaxAreapizza() {
        count = 0;
        int res = 0, sum = 0;
        for(int i = 0;i < pizza.size(); i++) {
            sum += pizza[i];
            int oponnent = helper(i + 1, i - 1);
            res = max(res, pizza[i] - oponnent);
        }
        cout<<"size :" <<pizza.size()<< " count: "<<count<<" ";
        return (sum + res) / 2;
    }
    // 0 1 2 3 4 5 6 7 8 9
    int helper(int x, int y) {
        count++;
        if(x < 0) x += len;
        else if(x >= len) x -= len;
        if(y < 0) y += len;
        else if(y >= len) y -= len;
        if(dp[x][y] != INT_MIN) return dp[x][y];
        if(x == y) return (dp[x][y] = pizza[x]);
        return  (dp[x][y] = max(pizza[x] - helper(x + 1, y), pizza[y] - helper(x, y - 1)));
    }
};
int main(int argc, const char * argv[]) {
    // insert code here...
    vector<int> test({1, 5, 2, 7, 3, 4, 4, 5, 23 , 56, 231,  44, 2, 11 ,34 ,  543 , 22});
    vector<int> test0({1, 5, 2, 7, 3, 4, 4, 5, 23 , 56, 231,  44, 2, 11 ,34 ,  543 , 22, 332, 4, 32});
    vector<int> test3({1, 5, 2, 7, 3, 4, 4, 5, 23 , 56, 231,  44, 2, 11 ,34 ,  543 , 22, 332, 4, 3,12, 4, 3, 4, 122});
    vector<int> test1({1, 5, 2, 7, 3, 8, 9});
    vector<int> test2({1, 2, 3, 4});
    Solution s(test3);
    cout<< s.MaxAreapizza()<<endl;
    cout<< s.MaxAreapizza2()<<endl;
    return 0;
}
