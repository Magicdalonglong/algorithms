
#include <unordered_map>
#include <set>
#include <stack>
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <unistd.h>
using namespace std;


struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};


/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

class Codec {
public:
    
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        if(!root)return "";
        stack<TreeNode*> s;
        s.push(root);
        string res;
        while(s.size()){
            TreeNode * cur = s.top();
            s.pop();
            if(!cur){
                res+="x,";
                continue;
            }
            res+=(to_string(cur->val)+',');
            s.push(cur->right);
            s.push(cur->left);
        }
        return res;
        
    }
    
    // Decodes your encoded data to tree.
    
    TreeNode* deserialize(string data) {
        vector<string> prep = mysplit(data);
        TreeNode* res;
        stack<pair<TreeNode*,pair<bool,bool>>> s;  //cur node, bool = has leftchild been visited
        for(auto& p : prep){
            if(p == "x")
            {
                if(s.empty())return res;
                if(!s.top().second.first)
                    s.top().second.first = 1;
                else if(!s.top().second.second){
                    s.top().second.second = 1;
                    do{
                        s.pop();
                    }
                    while(s.size() and s.top().second.first && s.top().second.second);
                }
                
            }else{ // p == 123
                if(s.empty()){ // initial tree
                    res = new TreeNode(stoi(p));
                    s.push(make_pair(res,make_pair(0,0)));
                }else{
                    TreeNode * temp = new TreeNode(stoi(p));
                    if(!s.top().second.first){
                        s.top().first->left = temp;
                        s.top().second.first = 1;
                        s.push(make_pair(temp,make_pair(0,0)));
                    }else {  //left checked
                        s.top().first->right = temp;
                        s.top().second.second = 1;
                        s.push(make_pair(temp,make_pair(0,0)));
                    }
                }
            }
        }
        return res;
    }
    vector<string> mysplit(string s){
        vector<string> res;
        string temp;
        for(auto c : s){
            if(c == ','){
                res.emplace_back(temp);
                temp.clear();
            }else temp.push_back(c);
        }
        return res;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));
int main(){
    
    TreeNode* r = new TreeNode (0);
    r->left = new TreeNode (1);
    r -> right = new TreeNode(2);
    r->left->left = new TreeNode(3);
    r->left->left->left = new TreeNode(7);
    r->left->left->right = new TreeNode(8);
    Codec cc;
    string res = cc.serialize(r);
    cout<<res;
    auto tree = cc.deserialize(res);
    
    stack<TreeNode*> s;
    
    s.push(tree);
    cout<<endl;
    while(s.size()){
        auto cur = s.top();
        cout<<cur->val << ' ';
        s.pop();
        if(cur->right) s.push(cur->right);
        if(cur->left) s.push(cur->left);
        
        
    }
    
    return 0;
    
}
