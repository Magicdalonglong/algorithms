//
//  main.cpp
//  jumpping_nums
//
//  Created by Lei Duan on 4/1/17.
//  Copyright © 2017 Lei Duan. All rights reserved.
//

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

void helper(vector<int>& res, int i, int n){
    queue<int> q;
    q.push(i);
    while(q.size()){
        int cur = q.front();
        q.pop();
        if(cur > n) break;
        res.emplace_back(cur);
        int last = cur % 10;
        if(last == 9){
            q.push(cur * 10 + 8);
        }else if (last == 0)
            q.push(cur * 10 + 1);
        else{
            q.push(cur * 10 + last + 1);
            q.push(cur * 10 + last - 1);
        }
    }

}

vector<int> juamping_num(int n){
    vector<int> res;
    for(int i = 1; i <= 9; ++i)
        helper(res, i, n);
    return res;
    
}


void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
    
    for( int i = m - 1, j = n - 1, index = m + n - 1; i >=0 || j >= 0;){
        if(j < 0 || i >=0 && nums1[i] > nums2[j])
            nums1[index --] = nums1[i--];
        else
            nums1[index --] = nums2[j--];
    }
}

int main(int argc, const char * argv[]) {
    // insert code here...
    int n = 1300;
    auto res = juamping_num(n);
    for(auto r : res) cout<<r <<" ";
    cout<<endl;
    vector<int> n1 = {0,0,3,0,0,0,0,0,0};
    vector<int> n2 = {-1,1,1,1,2,3};
    merge(n1,3,n2,6);
    
    
    return 0;
}
