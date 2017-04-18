#include <iostream>
#include <map>
#include <set>
#include <stack>
#include <list>
#include <vector>
#include <queue>
#include <unordered_set>
#include <unordered_map>
using namespace std;

class Solution {
public:
    unordered_map<int ,char> dict;
    Solution(){
        dict[1] = 'I';dict[5] = 'V';dict[10] = 'X';dict[50] = 'L';dict[100] = 'C';dict[500] = 'D';dict[1000] = 'M';
    }
    string intToRoman(int num) {
        string res;
        for(int i = 3; i >=0 ; --i){
            int base = pow(10,i);
            int val = num / base;
            if(val == 0)continue;
            if(val == 9){
                res.push_back(dict[base]);
                res.push_back(dict[base * 10]);
            }else if(val > 5){
                res.push_back(dict[base * 5]);
                res.insert(res.end(), val - 5, dict[base]);
            }else{
                res.insert(res.end(), val, dict[base]);
            }
        }
        return res;
        
    }
};

class NumArray {
private:
    struct Node {
        int sum;
        int low;
        int high;
        Node* left, *right;
        Node(int l, int r): sum(0), low(l), high(r), left(NULL),right(NULL){}
    };
    Node* root;
public:
    NumArray(vector<int> nums) {
        root = buildTree(nums,0,nums.size() - 1);
    }
    Node* buildTree(vector<int>& nums, int i, int j){
        if(i > j) return NULL;
        Node* res = new Node(i, j);
        if(i == j){
            res -> sum = nums[i];
            return res;
        }
        int mid = i + (j - i) / 2;
        res -> left = buildTree(nums, i, mid);
        res -> right = buildTree(nums, mid + 1, j);
        int leftsum = res -> left? res -> left -> sum : 0;
        int rightsum = res -> right? res -> right -> sum : 0;
        res -> sum = leftsum + rightsum;
        return res;
    }
    void update(int i, int val) {
        updateTree(i, val, root);
    }
    void updateTree(int i, int val, Node* root){
        if(root -> low == root -> high)
            root -> sum = val;
        else{
            int mid = root -> low + (root -> high - root -> low) / 2;
            if(i <= mid) updateTree(i, val, root -> left);
            else if(i > mid) updateTree(i, val, root -> left);
            root -> sum = root -> left -> sum + root -> right -> sum;
        }
        
    }
    
    int sumRange(int i, int j) {
        return queryTree(i, j, root);
    }
    int queryTree(int i, int j, Node* root){
        if(i == root -> low && j == root -> high)
            return root -> sum;
        else{
            int mid = root -> low + (root -> high - root -> low) / 2;
            if(j <= mid) return queryTree(i, j ,root -> left);
            else if(i > mid) return queryTree(i, j ,root -> right);
            else return queryTree(i, mid ,root -> right) + queryTree(mid + 1, j ,root -> right);
        }
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray obj = new NumArray(nums);
 * obj.update(i,val);
 * int param_2 = obj.sumRange(i,j);
 */
class Solution1 {
    typedef vector<int>::iterator it;
public:
    int reversePairs(vector<int>& nums) {
        it b = nums.begin(), e = nums.end();
        return merge(nums,b,e);
    }
    int merge(vector<int>& nums, it begin, it end){
        if(begin >= end) return 0;
        it mid = begin + (end - begin) / 2;
        int res = merge(nums, begin, mid) + merge(nums, mid, end);
        for(it i = begin; i < mid; ++i){
            for(it j = (end - 1); j >= mid + 1; --j){
                if(*i > 2.0 * *j)
                {
                    res += (j - mid);
                    break;
                }
            }
        }
        inplace_merge(begin,mid, end);
        return res;
        
    }
};
struct TreeNode{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int a): val(a), left(NULL), right(NULL) {}
};


class Solution5 {
private:
    struct Node {
        int low, high;
        int count;
        Node* left;
        Node* right;
        Node(int a, int b, int c): low(a), high(b), count(c), left(NULL), right(NULL){}
    };
    Node* root;
public:
    vector<int> countSmaller(vector<int>& nums) {
        int low = INT_MAX, high = INT_MIN, index = 0;
        for(auto n : nums)
        {
            low = min(low, n);
            high = max(high, n);
        }
        root = buildtree(low, high);
        for(auto n : nums)
            addnode(root, n);
        vector<int> res(nums.size());
        for(auto n : nums){
            deletenode(root,n);
            res[index++] = sum(root,low, n-1);
        }
        return res;
        
    }
    void addnode(Node* root, int val){
        if(!root) return ;
        if(root ->low == val && root -> high == val){
            root -> count ++ ;
            return;
        }
        int mid = root ->low + (root ->high - root ->low) / 2;
        if(val <= mid) addnode(root -> left, val);
        else if(val > mid) addnode(root -> right, val);
        root -> count = root -> left -> count + root -> right -> count;
    }
    void deletenode(Node* root, int val){
        if(!root) return ;
        if(root ->low == val && root -> high == val){
            root -> count --;
            return ;
        }
        int mid = root ->low + (root ->high - root ->low) / 2;
        if(val <= mid) deletenode(root -> left, val);
        else if(val > mid) deletenode(root -> right, val);
        root -> count = root -> left -> count + root -> right -> count;
    }
    int sum(Node* root, int low, int high){
        if(!root) return 0;
        if(root ->low == low && root -> high == high){
            return root -> count;
        }
        int mid = root ->low + (root ->high - root ->low) / 2;
        if(high <= mid) return sum(root -> left, low, high);
        else if(low > mid) return sum(root -> right, low, high);
        else return sum(root -> right, low, mid) + sum(root -> right, mid + 1, high);
    }
    Node* buildtree(int low, int high){
        if(low > high) return NULL;
        Node* res = new Node(low, high, 0);
        if(low == high) return res;
        int mid = low + (high - low) / 2;
        res -> left = buildtree(low, mid);
        res -> right = buildtree(mid + 1, high);
        return res;
    }
    
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


class LFUCache {
private:
    typedef pair<int, int> P;
    
    struct cmp {
        bool operator() (const P& p1, const P& p2) const {
            return p1.first != p2.first? p1.first < p2.first : p1.second < p2.second;
        }
    };
    map<P,P,cmp> data;   // frep, call#, key, val;
    unordered_map<int, map<P, P>::iterator> map;  // int -> iter
    int cap;
    int call;
public:
    LFUCache(int capacity) {
        cap = capacity;
        call = 0;
    }
    
    int get(int key) {
        if(map.count(key) == 0) return -1;
        pair<P, P> item = *(map[key]);
        item.first.first ++;
        item.first.second = call++;
        data.erase(map[key]);
        map[key] = data.insert(item).first;
        return map[key] -> second.second;
        
    }
    
    void put(int key, int value) {
        if(map.count(key)){ // exists key
            pair<P, P> item = *(map[key]);
            item.first.first ++;
            item.first.second = call++;
            item.second.second = value;
            data.erase(map[key]);
            map[key] = data.insert(item).first;
        }else{
            if(data.size() == cap)
            {
                map.erase(data.begin() -> second.first);
                data.erase(data.begin());
            }
            map[key] = data.emplace(make_pair(1,call),make_pair(key,value)).first;
            
        }
        
    }
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache obj = new LFUCache(capacity);
 * int param_1 = obj.get(key);
 * obj.put(key,value);
 */

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache obj = new LFUCache(capacity);
 * int param_1 = obj.get(key);
 * obj.put(key,value);
 */

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache obj = new LRUCache(capacity);
 * int param_1 = obj.get(key);
 * obj.put(key,value);
 */
void print2(int n){
    for(int i = 0 ; i < n; i++){
        int num = 1, gap = min (i , n - i - 1);
        for(int j = 0; j < n; j++){
            if(j >= gap && j < n - gap)
                cout<<num ++;
            else cout<<" ";
        }
        cout<<endl;
    }
    
    
}


void print(int n){
    for(int i = 0 ; i < n; i++){
        for(int j = 0; j < n; j++){
            if(i == j || i + j == n - 1)
                cout<<"X";
            else cout<<" ";
        }
        cout<<endl;
    }
    
    
}
int mean(vector<int>& nums){
    int min_val = INT_MAX, min_count = 0, max_val = INT_MIN, max_count = 0;
    int sum = 0, n = nums.size();
    for(auto n : nums){
        if(n < min_val){
            min_val = n;
            min_count = 1;
        }else if(n == min_val)
            min_count ++;
        if(n > max_val){
            max_val = n;
            max_count = 1;
        }else if(n == max_val)
            max_count ++;
        sum += n;
    }
    return (sum - min_val * min_count - max_val * max_count ) / (n - min_count - max_count);
    
}
double mysqrt(double x, double p){
    double res = x;
    while(abs(x - res * res) >= p) res = (res + x / res) / 2.0;
    return res;
}



bool helper(int cur, int op, vector<vector<bool>>& map, vector<vector<pair<int,int>>>& res, int n){
    static int count = 0; count ++;
    if(cur == n - 2 && op == n) { cout<<"call count : "<<count<<endl ; return true;}
    if(op == n) {cur ++;op = cur + 1;}
    for(int i = 0; i < n-1; i ++) // date
    {
        if(map[i][cur] || map[i][op]|| res[i].size() == n / 2 ) continue;
        map[i][cur] = map[i][op] = 1;
        try{
            res[i].emplace_back(cur, op);
        }catch(std:: exception e){
            cout<<e.what();
            throw e;
        }
        if(helper(cur, op + 1, map, res, n)) return true;
        map[i][cur] = map[i][op] = 0;
        res[i].pop_back();
    }
    return false;
}

void schedule2(int n){
    vector<vector<bool>> map(n-1,vector<bool>(n,false));
    vector<vector<pair<int,int>>> res(n - 1);
    bool done = helper(0,1,map,res, n);
    cout<<n<<" teams, can schedule? :" <<done<<endl;
    for(auto d : res){
        for(auto m : d)
            cout<<m.first<<","<<m.second<<"  ";
        cout<<endl;
    }
}

class Solution11 {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        if(obstacleGrid.empty()) return 0;
        int m = obstacleGrid.size(), n = obstacleGrid[0].size();
        auto mat = obstacleGrid;
        if(obstacleGrid[0][0] | obstacleGrid[m - 1][n - 1]) return 0;
        mat[0][0] = 1;
        for(int i = 0 ;i < m; i++)
            for(int j = 0; j < n; j++)
                if(obstacleGrid[i][j] == 0 && (i | j) != 0) mat[i][j] = (i > 0?mat[i - 1][j] : 0) + (j > 0?mat[i][j - 1] : 0);
        return mat[m - 1][n - 1];
    }
};


int main() {
  
    //  schedule(9);
 //   schedule2(10);
//    vector<vector<int>> mat = {{0,0}, {1,0}};
//    
//    Solution11 s;
//    cout<<s.uniquePathsWithObstacles(mat);
    TreeNode* p = new TreeNode(123);
    TreeNode* p2 = p;
    delete p;
    cout<<p2->val;
    return 0;
}
