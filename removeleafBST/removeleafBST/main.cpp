#include <unordered_map>
#include <iostream>
#include <vector>
#include <stack>
#include <vector>
#include <vector>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int v) : val(v), left(NULL),right(NULL){}
};
TreeNode* helper(TreeNode* root, int tar, bool* suc);

bool removeBST(TreeNode* root, int tar){
    bool res = false;
    root = helper(root, tar,&res);
    return res;
}

TreeNode* helper(TreeNode* root, int tar, bool* res){
    if(!root) return NULL;
    if(root->val == tar && !root->left && !root->right){
        *res = true;
        return NULL;
    }
    if(tar < root->val)root->left = helper(root->left,tar,res);
    else if(tar > root->val)root->right = helper(root->right,tar,res);
    return root;
    
    
}

bool removeBST2(TreeNode* root, int tar){
    if(!root) return false;
    if(root->val == tar && root->left == NULL && root->right == NULL){
        delete root;
        return true;
    }
    stack<TreeNode* > stk;
    stk.push(root);
    while(stk.size()){
        TreeNode* cur = stk.top();
        if(cur->val == tar){
            if(cur->left == NULL && cur->right == NULl){
                
            }
        }
    }
    
    
}


int main() {
    
    TreeNode* r = new TreeNode(10);
    r -> left = new TreeNode(5);
    r -> right = new TreeNode(15);
    r -> left ->left = new TreeNode(1);
    r -> left->right = new TreeNode(7);
    
    cout<<"removeBST(5):"<<removeBST(r,5)<<endl;
    cout<<"removeBST(1):"<<removeBST(r,1)<<endl;
    
    stack<TreeNode* > s;
    s.push(r);
    while(s.size()){
        TreeNode* cur = s.top();
        cout<<cur->val<<' ';
        s.pop();
        if(cur->right) s.push(cur->right);
        if(cur->left) s.push(cur->left);
    }
    
    return 0;
}




