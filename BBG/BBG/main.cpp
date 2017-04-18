#include <unordered_map>
#include <iostream>
#include <map>
#include <queue>
#include <sstream>
#include <stack>
#include <list>
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
    
    temp[0] = stk[0].top();
    temp[1] = stk[1].top();
    while(temp[0] && temp[1]){
        int val1 = temp[0] -> val, val2 = temp[1] -> val;
        if(val1 + val2 == tar) return true;
        if(val1 >= val2 ) return false;
        turn = val1 + val2 > tar;
        stk[turn].pop();
        temp[turn] = turn? temp[turn] -> left : temp[turn] -> right;
        while(temp[turn]){
            stk[turn].push(temp[turn]);
            temp[turn] = turn ? temp[turn] -> right : temp[turn] -> left;
        }
        if(stk[turn].empty()) return false;
        temp[turn] = stk[turn].top();
    }
    return false;
}


class PhoneDirectory {
private:
    typedef list<int> List;
    List dict;
    unordered_map<int, List::iterator> map;
public:
    /** Initialize your data structure here
     @param maxNumbers - The maximum numbers that can be stored in the phone directory. */
    PhoneDirectory(int maxNumbers) {
        for(int i = 0; i < maxNumbers; ++i)
        {
            dict.emplace_back(i);
            map[i] = (--dict.end());
        }
    }
    
    /** Provide a number which is not assigned to anyone.
     @return - Return an available number. Return -1 if none is available. */
    int get() {
        if(map.empty()) return -1;
        int res = *(dict.begin());
        map.erase(res);
        dict.erase(dict.begin());
        return res;
    }
    
    /** Check if a number is available or not. */
    bool check(int number) {
        return map.count(number);
    }
    
    /** Recycle or release a number. */
    void release(int number) {
        if(map.count(number)) return ;
        dict.emplace_back(number);
        map[number] = (--dict.end());
        
    }
};

/**
 * Your PhoneDirectory object will be instantiated and called as such:
 * PhoneDirectory obj = new PhoneDirectory(maxNumbers);
 * int param_1 = obj.get();
 * bool param_2 = obj.check(number);
 * obj.release(number);
 */

class Point {
public:
    Point CreatePointByXY(int a, int b){
        return Point(a,b);
    }
    Point CreatePointByA_R(int a, int r ){
        return Point(r * cos(a),r * sin(a));
    }
private:
    int x;
    int y;
protected:
    Point(int a , int b): x(a), y(b){}

};

class Solutionv {
public:
    bool isNumber(string s) {
        int d = 0, e = 0, i = 0, digit = 0;
        if(s == ".") return false;
        while(s[i] == 32) i++;
        int len = s.size();
        for(; i < len; i++)
        {
            if(s[i] == '-' && i != 0) return false ;
            else if(s[i] == '.' && (d++ >0 || i > 0 && !isdigit(s[i-1]) || i < len - 1 && !isdigit(s[i+1])))
                return false;
            else if(s[i] == 'e' && (i == 0 || i == s.size() - 1 || e++ > 0 || !isdigit(s[i-1]) || !isdigit(s[i+1])))
                return false;
            else if(s[i] == 32) {
                while(i < s.size()) if(s[i++] != 32) return false;
                break;
            }
            else if(!isdigit(s[i]) && s[i]!= '-' && s[i]!= '.' && s[i]!= 'e') return false;
            digit ++;
        }
        return digit > 0;
    }
};


int reversePairs(vector<int>& nums) {
    multiset<int,std::greater<int>> set;
    int len = nums.size();
    int res = 0;
    for(int i = len - 1; i >=0; --i){
        auto pos = lower_bound(set.begin(), set.end(), nums[i] / 2, std::greater<int>());
        if(pos != set.end()){
            if(*pos == nums[i] / 2)
                advance(pos, !(nums[i] & 1));
            res += distance(pos, set.end());
        }
        set.insert(nums[i]);
    }
    return res;
}
class Solution3 {
    typedef vector<int>::iterator it;
public:
    int reversePairs(vector<int>& nums) {
        return merge(nums.begin(),nums.end());
    }
    int merge(it begin, it end){
        if(end - begin <= 1) return 0;
        it mid = begin + (end - begin) / 2;
        int res = merge( begin, mid) + merge( mid, end);
        for(it i = begin; i != mid; ++i){
            for(it j = (end - 1); j >= mid; --j){
                if(*i > 2.0 * *j)
                {
                    res += (j - mid + 1);
                    break;
                }
            }
        }
        inplace_merge(begin,mid, end);
        return res;
        
    }
};


class LFUCache {
private:
    typedef pair<int, int> P;
    
    struct cmp {
        bool operator() (const P& p1, const P& p2) const {
            return (p1.first != p2.first)? (p1.first < p2.first) : (p1.second < p2.second);
        }
    };
    map<P,P,cmp> data;   // frep, call#, key, val;
    unordered_map<int, map<P, P>::iterator> hash;  // int -> iter
    int cap;
    int call;
public:
    LFUCache(int capacity) {
        cap = capacity;
        call = 0;
    }
    
    int get(int key) {
        if(hash.count(key) == 0) return -1;
        pair<P, P> item = *(hash[key]);
        item.first.first ++;
        item.first.second = call++;
        data.erase(hash[key]);
        hash[key] = data.insert(item).first;
        return hash[key] -> second.second;
        
    }
    
    void put(int key, int value) {
        if(hash.count(key)){ // exists key
            pair<P, P> item = *(hash[key]);
            item.first.first ++;
            item.first.second = call++;
            item.second.second = value;
            data.erase(hash[key]);
            hash[key] = data.insert(item).first;
        }else{
            if(data.size() == cap)
            {
                hash.erase(data.begin() -> second.first);
                data.erase(data.begin());
            }
            hash[key] = data.emplace(make_pair(1,call),make_pair(key,value)).first;
            
        }
    }
};
struct TreeLinkNode{
    int val;
    TreeLinkNode* left;
    TreeLinkNode* right;
    TreeLinkNode* next;
    TreeLinkNode(int a): val(a), left(NULL), right(NULL),next(NULL) {}
};

void zigzag_next(TreeLinkNode* root){
    
    if(root == NULL) return;
    queue<TreeLinkNode*> q;
    q.push(root);
    int lv = 0;
    TreeLinkNode* pre = new TreeLinkNode(0);
    while(q.size()){
        int len  = q.size();
        lv ++;
        if(lv % 2){ // -->
            while(len --){
                TreeLinkNode* cur = q.front();
                q.pop();
                pre-> next =cur;
                pre = cur;
                if(cur->left) q.push(cur->left);
                if(cur->right) q.push(cur->right);
            }
        }else {    // <--
            TreeLinkNode* newpre = NULL;
            while(len--){
                TreeLinkNode* cur = q.front();
                q.pop();
                if(len > 0) q.front() -> next = cur;
                if(len == 0) pre -> next = cur;
                if(newpre == NULL) newpre = cur;
                if(cur->left) q.push(cur->left);
                if(cur->right) q.push(cur->right);

            }
            pre = newpre;
            
        }
    }
}



int binarysearch(vector<pair<int, int>>::iterator begin, vector<pair<int, int>>::iterator end, int tar);
int search(vector<int>& num, int target) {
    int i = 0, len = num.size();
    vector<pair<int,int>> nums(len);
    for(auto n : num)nums[i] = make_pair(n, i++);
    for(i = 0; i < nums.size() - 1 && nums[i].first < nums[i + 1].first; i++);
    nums.insert(nums.begin(), nums.begin() + i + 1, nums.end());
    nums.resize(len);
    return binarysearch(nums.begin(), nums.end(), target);
}
int binarysearch(vector<pair<int, int>>::iterator begin, vector<pair<int, int>>::iterator end, int tar){
    auto left = begin, right = end - 1;
    while(left <= right){
        auto mid = left + (right - left) / 2;
        if(mid -> first < tar) left = mid + 1;
        else if(mid -> first > tar) right = mid - 1;
        else return mid -> second;
    }
    return -1;
    
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
class Codec {
public:
    
    string serialize(TreeNode* root) {
        stringstream ss;
        stack<TreeNode*> s;
        s.push(root);
        while(s.size()){
            TreeNode* cur = s.top();
            s.pop();
            if(!cur) ss << "X ";
            else{
                ss << to_string(cur -> val)<< " ";
                s.push(cur -> right);
                s.push(cur -> left);
            }
        }
        cout<<ss.str()<<endl;
        return ss.str();
    }
    
    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        stringstream ss(data);
        TreeNode* res = NULL;
        stack<pair<TreeNode*, bool>> s;  // node, leftchildchecked,
        string val;
        while(ss.eof() == false){
            ss >> val;
            cout<<val<<"  ";
            if(val == "X")
            {
                if(s.empty()) return res;
                else if(s.top().second == 0){
                    s.top().second = 1;
                }else{
                    do{
                        s.pop();
                    }
                    while(s.size() && s.top().second);
                }
            }else if(s.empty()){
                res = new TreeNode(stoi(val));
                s.emplace(res,0);
            }else if(s.top().second == false)
            {
                s.top().second = 1;
                s.top().first -> left = new TreeNode(stoi(val));
                s.emplace(s.top().first -> left, 0);
            } else{
                s.top().first -> right = new TreeNode(stoi(val));
                s.emplace(s.top().first -> right, 0);
            }
        }
        return res;
    }
};


string shortestPalindrome2(string s) {
    string rev_s = s;
    reverse(rev_s.begin(), rev_s.end());
    string l = s + "#" + rev_s;
    
    vector<int> p(l.size(), 0);
    for (int i = 1; i < l.size(); i++) {
        int j = p[i - 1];
        while (j > 0 && l[i] != l[j])
            j = p[j - 1];
        p[i] = (j += l[i] == l[j]);
    }
    
    return rev_s.substr(0, s.size() - p[l.size() - 1]) + s;
}
string shortestPalindrome(string s) {
    int len = s.size();
    string rs = s;
    reverse(rs.begin(), rs.end());
    string ls = s + "#" + rs;
    int matched = 0;
    for(int i = 1; i < len * 2 + 1; i++){
        if(ls[i] == ls[matched])
            ++matched;
        else if(ls.substr(i - 1,matched) == ls.substr(i,matched));
        else matched = 0;
    }
    return s.substr(matched, len - matched) + s;
    
    
}

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));

int main() {
//    /*
//     TreeNode* r = new TreeNode(10);
//     r -> left = new TreeNode(5);
//     r -> right = new TreeNode(15);
//     r -> left ->left = new TreeNode(1);
//     r -> left->right = new TreeNode(7);
//     
//     
//     cout<<"removeBST "<<removeBST(r,4);
//     */
//    // auto res = jumping(100);
//    // for(auto r : res) cout<<r << " ";
//    srand((unsigned)time(NULL));
//    //    guaranteeJump();
//    string a = "a", b= "b";
//    string a1 = "aas", a2= "aas";
//    cout<<"\ncompare(a,b): "<<compare(&a,&b);
//    cout<<"\ncompare(aas,aas): "<<compare(&a1,&a2);
//    TreeNode * n = new TreeNode(0);
//    TreeNode * n2 = new TreeNode(0);
//    TreeNode * n3 = n;
//    TreeNode * n4 = NULL;
//    TreeNode * n5 = NULL;
//    
//    
//    cout<<"\ncompare(n,n2): "<<compare(&n,&n2);
//    cout<<"\ncompare(n,n3): "<<compare(&n,&n3);
//    cout<<"\ncompare(n4,n5): "<<compare(&n4,&n5)<<endl;
//    cout<<"\ncompare(n3,n5): "<<compare(&n3,&n5)<<endl;
//    
//    vector<int> num ={12,3,2103,201,21,776,123,223,433,54,5,4,98,5,65,53,1,8,3,0};
//    auto res = leadingnum(num);
//    for(auto r : res) cout<<r <<" ";
//    
//    vector<string> we = {"github","github","google","google","googlea","3cschool","github","google",
//        "leetcode","githubg","facebook","facebook","facebook","cpprefer","facebook","leetcode","facebook",
//        "github","githube","cpprefer","facebook","cpprefer","linkedin","ab","linkedin","b",
//        "githuba","githubf","cpprefera","facebook","cpprefera","linkedina","ab","linkedinb","f",
//        "githubc","githubd","cpprefer","facebooka","cpprefer","linkedin","ab","linkedin","c"};
//    auto resw = frequsing(we,8);
//    cout<<endl;
//    for(auto r : resw)cout<<r<<" ";
//    
//    
////    
    TreeNode * r = new TreeNode(50);
    r -> left = new TreeNode(25);
    r -> left -> left = new TreeNode(13);
    r -> left -> right = new TreeNode(38);
    r -> right = new TreeNode(75);
    r -> right -> left = new TreeNode(61);
    r -> right -> right = new TreeNode(88);
    
    
//    TreeNode * r2 = new TreeNode(1);
//    r2 -> left = new TreeNode(2);
//    r2 -> right = new TreeNode(3);
    
//    //
    TreeLinkNode * r2 = new TreeLinkNode(50);
    r2 -> left = new TreeLinkNode(25);
    r2 -> left -> left = new TreeLinkNode(13);
    r2 -> left -> right = new TreeLinkNode(38);
    r2 -> left -> right -> right = new TreeLinkNode(39);
    r2 -> left -> right -> right -> right= new TreeLinkNode(40);
    r2 -> left -> right -> right -> right -> right= new TreeLinkNode(41);
    r2 -> right = new TreeLinkNode(75);
    r2 -> right -> left = new TreeLinkNode(61);
    r2 -> right -> left -> left = new TreeLinkNode(60);
    r2 -> right -> right = new TreeLinkNode(88);
////
////    TreeNode * list = new TreeNode(7);
//    list -> right = new TreeNode(12);
//    list -> right -> right = new TreeNode(16);
//    list -> right -> right -> right = new TreeNode(23);
//    list -> right -> right -> right -> right  = new TreeNode(34);
//    list -> right -> right -> right -> right -> right = new TreeNode(65);
//    
//
//    cout<<endl;
    zigzag_next(r2);
    while(r2){
        cout<<r2 -> val<<" ";
        r2 = r2 -> next;
    }
    cout<<endl;
    return 0;
}

