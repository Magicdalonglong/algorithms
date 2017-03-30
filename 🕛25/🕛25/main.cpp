//
//  main.cpp
//  🕛25
//
//  Created by Lei Duan on 2/21/17.
//  Copyright © 2017 Lei Duan. All rights reserved.
//

#include <iostream>
#include <vector>
using namespace std;


class Solution {
public:
    
    struct Node{
        vector<int> index;
        vector<Node*> next;
        Node(){next.assign(26,nullptr);}
    };
    vector<vector<string>> wordSquares(vector<string>& words) {
        Node * root = buidtrie(words);
        vector<vector<string>>res;
        vector<string> temp(words[0].size(),"");
        for(auto& w:words){
            temp[0]=w;
            backtracking(root,1,temp,res,words);
        }
        return res;
        
    }
    
    
    void backtracking (Node* root, int level, vector<string>& temp, vector<vector<string>> &res, vector<string>& words){
        if(level>=temp.size()){
            res.emplace_back(temp);
            return;
        }
        
        string vertical;
        for(int i=0;i<level;i++)
            vertical.push_back(temp[i][level]);
        Node* temp_root = root;
        for(auto v:vertical)
            if(!(temp_root=temp_root->next[v-97]))return ;
        
        for(int i:temp_root->index){
            temp[level] = words[i];
            backtracking(root,level+1,temp,res,words);
        }
        
        
    }
    Node* buidtrie(vector<string>& words){
        Node *root = new Node();
        int curindex=0;
        for(auto &w:words){
            Node * temp = root;
            for(char c:w){
                if(temp->next[c-97]==NULL)
                    temp->next[c-97] = new Node();
                temp = temp->next[c-97];
                temp->index.push_back(curindex);
            }
            curindex++;
        }
        return root;
        
    }
};
int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    vector<string> v = {"area","lead","wall","lady","ball"};
    Solution s;
    auto res = s.wordSquares(v);
    
    
    return 0;
}
