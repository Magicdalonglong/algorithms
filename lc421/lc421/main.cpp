//
//  main.cpp
//  lc421
//
//  Created by Lei Duan on 2/17/17.
//  Copyright © 2017 Lei Duan. All rights reserved.
//

#include <iostream>
#include <vector>

using namespace std;


class Solution {
public:
    struct node{
        node *next[2];
        node(){next[0]=NULL;next[1]=NULL;}
        
    };
    int findMaximumXOR(vector<int>& nums) {
        node *root = build(nums);
        int res = 0;
        for(int &n:nums)
            res = max(res,helper(n,root));
        return res;
    }
    node* build(vector<int>& nums) {
        node * res = new node();
        for(auto &n:nums){
            node * root = res;
            for(int i=30;i>=0;i--)
            {
                bool bi = (1<<i)&n;
                if(root->next[bi]==NULL)
                    root->next[bi] = new node();
                root=root->next[bi];
            }
        }
        return res;
        
    }
    int helper(int n, node* root){
        int res = 0;
        for(int i=30;i>=0;i--)
        {
            int bi = (n>>i)&1;
            if(root->next[bi?0:1]){
                res += (1<<i);
                root = root->next[bi?0:1];
            }else
                root = root->next[bi];
        }
        return res;
    }
};

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    Solution s;
    vector<int> v = {3,10,5,25,2,8};
    cout<<s.findMaximumXOR(v);
    return 0;
}
