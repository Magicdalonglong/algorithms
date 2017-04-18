#include <iostream>
#include <vector>
#include <set>
#include <stack>
#include <set>
#include <set>
#include <queue>
using namespace std;

struct TreeNode{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int a): val(a), left(NULL), right(NULL) {}
};


bool TwoSumBST(TreeNode* root, int tar){
    if(!root) return false;
    vector<stack<TreeNode*>> stk(2);
    vector<TreeNode* > temp = {root, root};
    while(temp[0]){
        stk[0].emplace(temp[0]);
        temp[0] = temp[0] -> left;
    }
    while(temp[1]){
        stk[1].emplace(temp[1]);
        temp[1] = temp[1] -> right;
    }
    while(stk[0].size() && stk[1].size()){
        temp[0] = stk[0].top();
        temp[1] = stk[1].top();
        if(temp[0] == temp[1]) return false;
        int val0 = temp[0] -> val;
        int val1 = temp[1] -> val;
        if(val1 + val0 == tar) return true;
        bool turn = (val1 + val0 > tar);
        stk[turn].pop();
        temp[turn] = turn ? temp[turn] -> left : temp[turn] -> right;
        while(temp[turn]){
            stk[turn].emplace(temp[turn]);
            temp[turn] = !turn ? temp[turn] -> left : temp[turn] -> right;
        }
    }
    return false;
    
}
int main() {
    cout<<"Hello\n";
    
    TreeNode* r  = new TreeNode(12);
    r -> left = new TreeNode(-1);
    r -> left -> right = new TreeNode(2);
    r -> left -> right -> right = new TreeNode(3);
    r -> left -> right -> right -> right = new TreeNode(4);
    r -> left -> right -> right -> right -> right = new TreeNode(5);
    r -> right = new TreeNode(15);
    r -> right -> right = new TreeNode(200);
    r -> right -> left = new TreeNode(14);
    cout<<"TwoSumBST(r,-13) " <<TwoSumBST(r,-13)<<endl;
    cout<<"TwoSumBST(r,-1) " <<TwoSumBST(r,-1)<<endl;
    cout<<"TwoSumBST(r,1) " <<TwoSumBST(r,1)<<endl;
    cout<<"TwoSumBST(r,212) " <<TwoSumBST(r,212)<<endl;
    cout<<"TwoSumBST(r,199) " <<TwoSumBST(r,199)<<endl;
    cout<<"TwoSumBST(r,17) " <<TwoSumBST(r,17)<<endl;
    cout<<"TwoSumBST(r,171) " <<TwoSumBST(r,171)<<endl;
    cout<<"TwoSumBST(r,19) " <<TwoSumBST(r,19)<<endl;
    return 0;
}
