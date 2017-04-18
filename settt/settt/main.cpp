#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <queue>
#include <stack>
#include <queue>
#include <set>
#include <vector>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* right;
    TreeNode* left;
    TreeNode(int v) : val(v), right(NULL),left(NULL){} 
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
void helper(vector<int>& res, int i, int tar){
    
    queue<int> q;
    q.push(i);
    while(q.size()){
        int cur = q.front();
        q.pop();
        if(cur > tar) continue;
        res.push_back(cur);
        int last = cur % 10;
        if(last == 0){
            q.push(cur * 10 + last + 1);
        }else if (last == 9){
            q.push(cur * 10 + last - 1);
        }else {
            q.push(cur * 10 + last - 1);
            q.push(cur * 10 + last + 1);
        }  
    }    
    
}


bool jump(){
    
    return rand()%2;    
}


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
    string longestPalindrome(string s) {
        if(s.empty()) return "";
        int index = 0, len = 1, size = s.size();
        for(int i = 1; i < size - 1; i++){
            // find max palindro from i as the pivot;
            int left = i - 1, right = i + 1;
            while(left >=0 && right < size && s[left] == s[right]){left --; right ++;}
            if((i - left) * 2 - 1 > len){
                cout<<"updating:  left, right is "<<left<<" "<<right;
                len = (i - left) * 2 - 1;
                index = left + 1;
            }
            
            left = i-1, right = i;
            while(left >=0 && right < size && s[left] == s[right]){left --; right ++;}
            if((i - left) * 2 > len){
                len = (i - left) * 2 ;
                index = left + 1;
            }
        }
        return s.substr(index, len);
        
    }
};

void guaranteeJump(){
    int lv = 0;
    int count = 0;
    while(lv != 1){
        lv +=(jump()? 1: -1);    
        cout<<"now lv is "<<lv<<endl;  
        if(count ++ > 200) break;
    }
    cout<<"finally lv is "<<lv;
    
    
}
vector<int> jumping(int n){
    vector<int> res = {0};
    for(int i = 0 ; i <= min(9,n); i++)
        helper(res,i,n);
    return res;
}


template<typename T>
bool compare(const T* a, const T* b){
    return *a == *b;
}


vector<int> leadingnum(vector<int>& nums){
    if(nums.empty()) return {};
    int len = nums.size();
    int cur_max = INT_MIN;
    vector<int> res;
    for(int i = len - 1; i >= 0; --i){
        if(i < len - 1 && nums[i] > cur_max)
            res.emplace_back(nums[i]);
        cur_max = max(cur_max, nums[i]);
        
    }
    return res;
    
}

vector<string> frequsing(vector<string>& webs, int k){
    
    unordered_map<string, int> map; // web, freq
    set<pair<int,string>> minheap;
    for(auto& w : webs) map[w] ++;
    for(auto& w : map){
        minheap.emplace(w.second,w.first);
        if(minheap.size() > k){
            minheap.erase(minheap.begin());
        }        
    }
    vector<string> res;
    for(auto m : minheap)
        res.emplace_back(m.second);
    return res;
    
    
}



bool Twosum(TreeNode* root, int tar){
    if(!root) return false;
    
    vector<stack<TreeNode*>> stk(2);
    TreeNode* temp[2] = {root, root};
    bool turn;
    while(temp[0]){
            stk[0].push(temp[0]);
            temp[0] = temp[0] -> left;
        }
    while(temp[1]){
            stk[1].push(temp[1]);
            temp[1] = temp[1] -> right;
        }
    
    while(temp[0] || stk[0].size() || temp[1] || stk[1].size()){
        
        temp[0] = stk[0].top();
        temp[1] = stk[1].top();
        if(temp[0] -> val + temp[1] -> val == tar)
            return 1;
        turn = temp[0] -> val + temp[1] -> val > tar;
        temp[turn] = turn ? temp[turn] -> left: temp[turn] -> right;
        while(temp[turn]){
            stk[turn].push(temp[turn]);
            temp[turn] = turn ? temp[turn] -> right : temp[turn] -> right;
        }     
        
    }  
    return 0;   
    
}



string sortletterandnum(string s) {
    set<char> set1, set2;
    for(auto c : s){
        if(isdigit(c)) set1.insert(c);
        else if (isalpha(c)) set2.insert(c);
    }
    set<char>::iterator it1 = set1.begin(), it2 = set2.begin();
    for(auto &c : s){
        if(isdigit(c)) c = *(it1++);
        else if (isalpha(c)) c= *(it2++);
    }
    return s;
    
}


    

int main() {
    Solution s;
  // cout<<s.longestPalindrome("cbbd");
      int *p = new int[123];
      for()

}

