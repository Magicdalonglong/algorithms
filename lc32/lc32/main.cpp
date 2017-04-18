//
//  main.cpp
//  print_dia
//
//  Created by Lei Duan on 4/9/17.
//  Copyright © 2017 Lei Duan. All rights reserved.
//

#include <iostream>
#include <stack>
#include <vector>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* right;
    TreeNode* left;
    TreeNode(int v) : val(v), right(NULL),left(NULL){}
};


bool hasPathSum(TreeNode* root, int sum) {
    if(!root) return 0;
    stack<pair<TreeNode*, int>> stk;
    stk.emplace(root, root -> val);
    while(stk.size()){
        TreeNode* cur = stk.top().first;
        int val = stk.top().second;
        stk.pop();
        if(cur -> left) stk.emplace(cur -> left, val * 10 + cur -> left -> val);
        if(cur -> right) stk.emplace(cur -> right, val * 10 + cur -> right -> val);
        if(!cur -> right && !cur -> left && val == sum) return true;
    }
    return false;
    
}





int longestValidParentheses(string s) {
    stack<int> stk;
    stk.push(-1);
    int res = 0;
    for(int i = 0; i < s.size(); i++){
        if(stk.top() != -1 && s[i] == ')' && s[stk.top()] == '('){
            stk.pop();
            res = max(res, i - stk.top());
        }else stk.push(i);
    }
    return res;
}

int longestValidParentheses2(string s) {
    int len = s.size(), res = 0;
    vector<int> dp(len, 0);
    for(int i = 0; i < len; i++){
        if(s[i] == '(') dp[i] = 0;
        else {
            if(i > 0 && s[i - 1] == '(') dp[i] = dp[i - 2] + 2;
            else if(i - dp[i - 1] - 1 >= 0 && s[i - dp[i - 1] - 1] == '(')
                dp[i] = dp[i - 1] + 2 + dp[i - dp[i - 1] - 2];
        }
        res = max(res, dp[i]);
    }
    return res;
}


int main(int argc, const char * argv[]) {
    // insert code here...
    string s = "())()()";
    cout<<longestValidParentheses(s);
    cout<<"  "<<longestValidParentheses2(s);
    cout<<endl;
    TreeNode* r = new TreeNode(1);
    r -> left = new TreeNode(2);
    cout<<hasPathSum(r,3)<<endl;
    return 0;
}
