//
//  main.cpp
//  lc340
//
//  Created by Lei Duan on 4/9/17.
//  Copyright © 2017 Lei Duan. All rights reserved.
//

#include <iostream>
#include <vector>
using namespace std;

int longest_one(vector<int>& nums, int k){
    int res = 0, count = 0, left = 0;
    for(int i = 0; i < nums.size(); i++){
        count += (nums[i] == 0);
        if(count > k){
            while(nums[left++] != 0);
            count --;
        }
        if(count == k) res = max(res, i - left + 1);
    }
    return res;
}

vector<int> helper1(int sum){
    vector<int> res;
    for(int i = 1; i <= 9; i++){
        if(i > sum) break;
        if(sum - i > 18) continue;
        for(int j = 0; j <= 9; j++){
            if(i + j > sum) break;
            if(sum - i - j > 9)continue;
            res.emplace_back(i * 100 + j * 10 + sum - i - j);
        }
    }
    return res;
}
vector<int> helper2(int sum){
    vector<int> res;
    for(int i = 0; i <= 9; i++){
        if(i > sum) break;
        if(sum - i > 18) continue;
        for(int j = 0; j <= 9; j++){
            if(i + j > sum) break;
            if(sum - i - j > 9)continue;
            res.emplace_back(i * 100 + j * 10 + sum - i - j);
        }
    }
    return res;
}
vector<int> six_digit(){
    vector<int> res;
    for(int i = 1; i <= 27; i++){
        vector<int> front = helper1(i);
        vector<int> back = helper2(i);
        for(auto f : front)
            for(auto b : back)
                res.emplace_back(f * 1000 + b);
    }
    return res;
    
}

int main(int argc, const char * argv[]) {
    // insert code here...

    auto res = six_digit();
    for(auto r : res)cout<<r <<" ";
    return 0;
}
