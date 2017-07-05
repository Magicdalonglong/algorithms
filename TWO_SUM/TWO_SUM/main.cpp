//
//  main.cpp
//  TWO_SUM
//
//  Created by Lei Duan on 4/29/17.
//  Copyright © 2017 Lei Duan. All rights reserved.
//

#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
using namespace std;


 
  struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode(int x) : val(x), left(NULL), right(NULL) {}
  };
 
class Solution {
private:
    struct info {
        TreeNode* node;
        int index1;
        int index2;
        int len;
        info(int i1, int i2, int l, TreeNode* n) : index1(i1), index2(i2), len(l), node(n) {}
    };
public:
    TreeNode* buildTree(vector<int>& pre, vector<int>& in) {
        if(pre.empty()) return NULL;
        unordered_map<int, int> map;
        for(int i = 0; i < in.size(); i++) map[in[i]] = i;
        queue<info> q;
        TreeNode* res;
        q.emplace(0, 0, pre.size(), res);
        while(q.size()){
            int index1 = q.front().index1,  index2 = q.front().index2, len = q.front().len;
            TreeNode* cur = q.front().node; q.pop();
            int val = pre[index1];
            if(len < 2){
                cur = len == 1 ? new TreeNode(val) : NULL;
            }else{
                //pre X-----
                //in  ---X--
                int mid = map[val];
                int len1 = mid - index2, len2 = len - len1 - 1;
                cur = new TreeNode(val);
                q.emplace(index1 + 1, index2, len1, ((cur) -> left));
                q.emplace(index1 + len1 + 1, mid + 1, len2, ((cur) -> right));
            }
        }
        return res;
    }
};

int main(int argc, const char * argv[]) {
    // insert code here...
    vector<int> nums = {3,2,4,123,12,3,12};
    
    std::cout << "\nHello, World!\n";
    return 0;
}
