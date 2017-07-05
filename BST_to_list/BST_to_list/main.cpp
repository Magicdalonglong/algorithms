//
//  main.cpp
//  BST_to_list
//
//  Created by Lei Duan on 4/19/17.
//  Copyright © 2017 Lei Duan. All rights reserved.
//

#include <iostream>
#include <queue>
#include <stack>
using namespace std;

struct TreeNode{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int v) : val(v), left(NULL), right(NULL){}
};

void helper(TreeNode* cur, TreeNode* & pre, TreeNode* & res){
    if(cur -> left) helper(cur -> left, pre, res);
    TreeNode* temp = cur -> right;
    if(res == NULL) res = pre = cur;
    else{
        pre -> left = NULL;
        pre -> right = cur;
        pre = cur;
    }
    if(temp) helper(temp, pre, res);
}
void flatten(TreeNode* &root){
    TreeNode* pre = NULL;
    TreeNode* res = NULL;
    helper(root, pre, res);
    root = res;
}
void flatten2(TreeNode* &root){
    if(!root) return ;
    TreeNode* res = NULL, *temp = root, *pre = NULL;
    stack<TreeNode*> stk;
    while(temp || stk.size()){
        while(temp){
            stk.emplace(temp);
            temp = temp -> left;
        }
        temp = stk.top();
        stk.pop();
        if(res == NULL) res = pre = temp;
        else{
            pre -> left = NULL;
            pre -> right = temp;
            pre = temp;
        }
        temp = temp -> right;
    }
    
    root = res;
}

void print_level_order(TreeNode* root){
    if(!root) return ;
    queue<TreeNode*> q;
    q.emplace(root);
    while(q.size()){
        int len = q.size();
        while(len --){
            TreeNode* cur = q.front();
            q.pop();
            cout<<cur -> val<<" ";
            if(cur -> left) q.push(cur -> left);
            if(cur -> right) q.push(cur -> right);
        }
        cout<<endl;
    }
}

int main(int argc, const char * argv[]) {
    // insert code here...
    
    TreeNode* r = new TreeNode(10);
    r -> left = new TreeNode(5);
    r -> left -> left = new TreeNode(3);
    r -> left -> right = new TreeNode(7);
    r -> right = new TreeNode(15);
    r -> right -> right = new TreeNode(20);
    r -> right -> left = new TreeNode(13);
    cout<<"before:"<<endl;
    print_level_order(r);
    
    flatten2(r);
    
    cout<<"after:"<<endl;
    print_level_order(r);
    
    
    std::cout << "\nHello, World!\n";
    return 0;
}
