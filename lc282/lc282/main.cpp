#include <unordered_map>
#include <unordered_set>
#include <set>
#include <stack>
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <unistd.h>
#include "/Users/Leigh/Downloads/exprtk/exprtk.hpp"

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

class Solution {
public:
    vector<string> addOperators(string num, int target) {
        
        vector<string> res;
        string temp;
        helper(res,temp,num,0,target,0,0,'#');
        return res;
    }
    // index = index of num we have considered
    // cur = value we got so far
    // pre =  previous oprend
    // op = previous operator
    
    void helper(vector<string>& res, string temp,const string& num, int index, const int tar, long long cur, long long pre, char op){
    
//        if(temp == "12*3-4-5*6"){
//            int aaa;
//            cin>>aaa;
//        }
        if(index == num.size() and cur == tar)
        {
            res.emplace_back(temp);
            return ;
        }
        for(int l = 1; l <= num.size()-index; l++){
            if(num[index] == 48 and l>1)break;
            long long curnum = stol(num.substr(index,l));
            if(index == 0){
                helper(res,num.substr(index,l),num,index+l,tar,curnum,curnum,'#');
                continue;
            }
            helper(res,temp+"+"+num.substr(index,l),num,index+l,tar,cur+curnum,cur,'+');
            helper(res,temp+"-"+num.substr(index,l),num,index+l,tar,cur-curnum,cur,'-');
            long long tempcur;
            if(op == '+')
            {
                tempcur = (cur - pre) * curnum + pre;
                helper(res,temp+"*"+num.substr(index,l),num,index+l,tar,tempcur,pre,'+');
            }
            else if(op == '-') {
                tempcur = pre - (pre-cur) * curnum;
                helper(res,temp+"*"+num.substr(index,l),num,index+l,tar,tempcur,pre,'-');

            }
            else{ tempcur = cur*curnum;
            
                helper(res,temp+"*"+num.substr(index,l),num,index+l,tar,tempcur,cur,pre);
            }
        }
    }
};
// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));

int main(){
    vector<string> v1 = {"1+2+3+4+5+6-7","1+2-3-4+5+6+7","1+2-3*4+5*6-7","1+2*3+4*5-6-7","1+2+34-5*6+7","1-2+3+4-5+6+7","1-2*3+4*5+6-7","1-2*3-4+5*6-7","1-2-34+56-7","1*2*3+4+5+6-7","1+23-4-5+6-7","12*3+4*5-6*7","12*3-4-5-6-7","12*3-4-5*6*7","12*3+45-67"};
    vector<string> v2 = {"1*2*3+4+5+6-7","1+2*3+4*5-6-7","1+2+3+4+5+6-7","1+2+34-5*6+7","1+2-3*4+5*6-7","1+2-3-4+5+6+7","1+23-4-5+6-7","1-2*3*4+5*6+7","1-2*3*4-5+6*7","1-2*3+4*5+6-7","1-2*3-4+5*6-7","1-2+3+4-5+6+7","1-2-34+56-7","12*3+4*5-6*7","12*3+45-67","12*3-4-5-6-7"};
    
    unordered_set<string>  s;
    unordered_set<string>  s2;
    for(auto v:v1) s.insert(v);
    for(auto v:v2) s2.insert(v);
    
    cout<<"should has but miss: " ;
    for(auto v:v2) if(!s.count(v))cout<<v<<" ";
    
    cout<<"\n\nshould not has but has: "   ;
    for(auto v:v1) if(!s2.count(v))cout<<v<<" ";
    
    Solution so;
    auto newres = so.addOperators("1234567",14);
    cout<<"\n\nnew res :";
    for(auto n:newres) cout<<n<<" ";
    return 0;
    
}
