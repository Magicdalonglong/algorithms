#include <unordered_map>
#include <iostream>
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


int main() {
    /*
    TreeNode* r = new TreeNode(10);
    r -> left = new TreeNode(5);
    r -> right = new TreeNode(15);
    r -> left ->left = new TreeNode(1);
    r -> left->right = new TreeNode(7);
    

    cout<<"removeBST "<<removeBST(r,4);
    */
    // auto res = jumping(100);
    // for(auto r : res) cout<<r << " ";
    srand((unsigned)time(NULL));
//    guaranteeJump();
    string a = "a", b= "b";
    string a1 = "aas", a2= "aas";
    cout<<"\ncompare(a,b): "<<compare(&a,&b);
    cout<<"\ncompare(aas,aas): "<<compare(&a1,&a2);
    TreeNode * n = new TreeNode(0);
    TreeNode * n2 = new TreeNode(0);
    TreeNode * n3 = n;
    TreeNode * n4 = NULL;
    TreeNode * n5 = NULL;


    cout<<"\ncompare(n,n2): "<<compare(&n,&n2);
    cout<<"\ncompare(n,n3): "<<compare(&n,&n3);
    cout<<"\ncompare(n4,n5): "<<compare(&n4,&n5)<<endl;

    vector<int> num ={12,3,2103,201,21,776,123,223,433,54,5,4,98,5,65,53,1,8,3,0};
    auto res = leadingnum(num);
    for(auto r : res) cout<<r <<" ";

    vector<string> we = {"github","github","google","google","googlea","3cschool","github","google",
"leetcode","githubg","facebook","facebook","facebook","cpprefer","facebook","leetcode","facebook",
"github","githube","cpprefer","facebook","cpprefer","linkedin","ab","linkedin","b",
"githuba","githubf","cpprefera","facebook","cpprefera","linkedina","ab","linkedinb","f",
"githubc","githubd","cpprefer","facebooka","cpprefer","linkedin","ab","linkedin","c"};
    auto resw = frequsing(we,8);
    cout<<endl;
    for(auto r : resw)cout<<r<<" ";
    return 0;
}

