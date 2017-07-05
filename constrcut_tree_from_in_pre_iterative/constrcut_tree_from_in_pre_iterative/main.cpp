//
//  main.cpp
//  constrcut_tree_from_in_pre_iterative
//
//  Created by Lei Duan on 4/26/17.
//  Copyright © 2017 Lei Duan. All rights reserved.
//

#include <iostream>
#include <vector>
#include <unordered_map>
#include <stack>
using namespace std;

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */


  struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode(int x) : val(x), left(NULL), right(NULL) {}
  };

class Solution {
private:
    struct info{
        int len;
        int index1;
        int index2;
        TreeNode** node;
        info(int l, int i1, int i2, TreeNode**n) : len(l), index1(i1), index2(i2), node(n) {}
    };
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        if(preorder.empty()) return NULL;
        unordered_map<int, int> map;
        int index = 0;
        for(auto in : inorder) map[in] = index++;
        TreeNode* res;
        stack<info> s;
        s.emplace(preorder.size(), 0, 0, &res);
        while(s.size()){
            int len = s.top().len;
            int index1 = s.top().index1, index2 = s.top().index2;
            TreeNode** cur = s.top().node;
            s.pop();
            int val = preorder[index1];
            if(len < 2) *(cur) = (len == 1 ? new TreeNode(val) : NULL);
            else{
                *(cur) = new TreeNode(val);
                int mid = map[val], len1 = mid - index2, len2 = len - len1 - 1;
                s.emplace(len1, index1 + 1, index2, &((*cur) -> left));
                s.emplace(len2, index1 + len1 + 1, mid + 1, &((*cur) -> right));
            }
        }
        return res;
    }
};


int main(int argc, const char * argv[]) {
    // insert code here...
    
    vector<int> pre ={1,2,3};
    vector<int> in = {2,1,3};
    Solution s;
    auto res = s.buildTree(pre, in);
    std::cout << "Hello, World!\n";
    return 0;
}
