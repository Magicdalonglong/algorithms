//
//  main.cpp
//  PGOnsite1
//
//  Created by 李博 on 6/13/17.
//  Copyright © 2017 Libo. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
using namespace std;

void print(vector<string> input){
    for(auto & s: input){
        cout<<s<<" ";
    }
    cout<<endl;
}

class Solution {
    map<pair<int,int>, int> lookup;
    vector<int> nums;
    vector<int> sums;
    int AllSum;
    int len;
public:
    Solution(vector<int> num) : nums(num.begin(), num.end()), len(nums.size()), sums(nums.size()+1, 0) {
        for(int i=0; i<len; ++i){
            sums[i+1] = sums[i] + nums[i];
        }
        AllSum = sums[len];
    }
    
    int getSum(int i, int j){
        if(i <= j){
            return sums[j+1] - sums[i];
        }
        if( j == i-1)
        return AllSum;
        return AllSum - getSum(j+1, i-1);
    }
    
    int getMax2(){
        int result = 0;
        for(int i=0; i<len; ++i){
            int bestOther = bfs(i+1, i-1);
            cout<<"pick "<<i<<" first with other is "<<bestOther<<" ";
            cout<<"Curent max is "<< AllSum-bestOther<<endl;
            result = max(result, AllSum-bestOther);
        }
        
        //output();
        return result;
    }
    
    void output(){
        for(auto i:lookup){
            cout<<i.first.first<<" "<<i.first.second<<" is "<<i.second<<endl;
        }
    }
    
    int bfs(int i, int j){
        if(i==-1)
        i = len-1;
        if(i==len)
        i = 0;
        
        if(j==-1)
        j = len-1;
        if(j==len)
        j = 0;
        
        if(i==j){
            lookup[{i,i}] = nums[i];
            return lookup[{i,i}];
        }
        
        if(lookup.count({i,j}))
        return lookup[{i,j}];
        
        //int bestOther = max(bfs(i+1,j) , bfs(i,j-1));
        lookup[{i,j}] = getSum(i, j) - min(bfs(i+1,j) , bfs(i,j-1));
        
        return  lookup[{i,j}];
    }
    
    int getMax1(){
        int result = 0;
        for(int i=0; i<len; ++i){
            vector<int> cur;
            for(int j=i+1; j<len; ++j){
                cur.push_back(nums[j]);
            }
            for(int j=0; j<i; ++j){
                cur.push_back(nums[j]);
            }
            int bestOther = PredictTheWinner(cur);
            cout<<"pick "<<i<<" first with other is "<<bestOther<<" ";
            cout<<"Curent max is "<< AllSum-bestOther<<endl;
            result = max(result, AllSum-bestOther);
        }
        return result;
    }
    
    int PredictTheWinner(vector<int>& test) {
        int curLen = test.size();
        if(curLen==1)
        return test[0];
        vector<int> curSum(curLen+1,0);
        for(int i=0; i<curLen; ++i){
            curSum[i+1] = curSum[i]+test[i];
        }
        //DP
        vector<vector<int>> DP(curLen, vector<int>(curLen,0));
        for(int end=0; end<curLen; ++end){
            DP[end][end] = test[end];
            for(int start=end-1; start>=0; --start){
                int tmp1 = test[start] + (curSum[end+1] - curSum[start+1] - DP[start+1][end] );
                int tmp2 = test[end] + (curSum[end] - curSum[start] - DP[start][end-1] );
                DP[start][end] = max(tmp1, tmp2);
            }
        }
        return DP[0][curLen-1];
    }
};



void testPridictWin(){
    vector<int> test({1, 5, 2, 7, 3});
    
    Solution s(test);
    cout<<s.PredictTheWinner(test)<<endl;
}

void testGetSum(){
    vector<int> test({1, 5, 2, 7, 3, 4, 4, 5, 23 , 56, 231,  44, 2, 11 ,34 ,  543 , 22});
    
    Solution s(test);
    cout<<s.getSum(0, 0)<< " " << s.getSum(1, 1)<<endl;
    cout<<s.getSum(0, 2)<< " " <<  s.getSum(1, 4)<<endl;
    cout<<s.getSum( 2, 1)<< " " <<  s.getSum(3, 2)<<endl;
    cout<<s.getSum( 4, 2)<< " " <<  s.getSum(3, 1)<<endl;
}

void testCircle(){
    vector<int> test({1, 5, 2, 7, 3, 4, 4, 5, 23 , 56, 231,  44, 2, 11 ,34 ,  543 , 22});
    vector<int> test1({1, 5, 2, 7, 3, 8, 9});
    
    Solution s(test1);
    cout<<s.getMax1()<<endl;
    cout<<s.getMax2()<<endl;
}


int main(int argc, const char * argv[]) {
    //testGetSum();
    testCircle();
}



