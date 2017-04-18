#include <iostream>
#include <vector>
#include <set>
#include <vector>
#include <unordered_set>
#include <unordered_map>
using namespace std;

class NumMatrix {
private:
    vector<vector<int>> bit;
    vector<vector<int>> data;
    int m, n;
    void init(int i, int j, int val){
        i++; j++;
        while(i <= m){
            int temp = j;
            while(j <= n)
            {
                bit[i][j] += val;
                j += (j & -j);
            }
            j = temp;
            i += (i & -i);
        }
    }
    int getsum(int i, int j){
        i++; j++;
        int res = 0;
        while(i > 0){
            int temp = j;
            while(j > 0)
            {
                res += bit[i][j];
                j -= (j & -j);
            }
            j = temp;
            i -= (i & -i);
        }
        return res;
    }
public:
    NumMatrix(vector<vector<int>> matrix) {
        data = matrix;
        m = matrix.size();
        n = matrix.empty()? 0 : matrix[0].size();
        bit.assign(m + 1, vector<int>(n + 1, 0));
        for(int i = 0; i < m; ++i)
            for(int j = 0; j < m; ++j)
                init(i, j, matrix[i][j]);
        cout<<" initialed bit: \n";
        for(int i = 0; i <= m; ++i){
            for(int j = 0; j <= n; ++j)
                cout<<bit[i][j]<<" ";
            cout<<endl;
        }
        
    }
    
    void update(int row, int col, int val) {
        int diff = val - data[row][col];
        data[row][col] = val;
        init(row, col, diff);
    }
    
    int sumRegion(int row1, int col1, int row2, int col2) {
        int res = getsum(row2, col2);
        int upper = getsum(row1 - 1, col2);
        int left = getsum(row2, col1 - 1);
        int over = getsum(row1 - 1, col1 - 1);
        cout<<"res :" <<res<<endl;
        cout<<"upper :" <<upper<<endl;
        cout<<"left :" <<left<<endl;
        cout<<"over :" <<over<<endl;
        return res - upper - left + over;
    }
};

/**
 * Your NumMatrix object will be instantiated and called as such:
 * NumMatrix obj = new NumMatrix(matrix);
 * obj.update(row,col,val);
 * int param_2 = obj.sumRegion(row1,col1,row2,col2);
 */



class NumArray2 {
public:
    vector<int> bit;
    vector<int> data;
    int n;
    NumArray2(vector<int> nums) {
        data = nums;
        int n = nums.size() + 1;
        bit.assign(n, 0);
        for(int i = 0; i < n - 1; ++i)
            init(i,nums[i]);
    }
    void init(int i, int val){
        i ++;
        while(i < n){
            bit[i] += val;
            i += (i & -i);
        }
    }
    
    void update(int i, int val) {
        int diff = val - data[i];
        data[i] = val;
        init(i, diff);
    }
    
    int sumRange(int i, int j) {
        return getsum(j) - getsum(i - 1);
    }
    int getsum(int i){
        i ++;
        int res = 0;
        while(i > 0){
            res += bit[i];
            i -= (i & -i);
        }
        return res;
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray obj = new NumArray(nums);
 * obj.update(i,val);
 * int param_2 = obj.sumRange(i,j);
 */

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
            else if(i > mid) updateTree(i, val, root -> right);
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
            else return queryTree(i, mid ,root -> left) + queryTree(mid + 1, j ,root -> right);
        }
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray obj = new NumArray(nums);
 * obj.update(i,val);
 * int param_2 = obj.sumRange(i,j);
 */

int main() {
    vector<int> num = {1,3,5};
    NumArray n (num);
    NumArray2 n2 (num);
  
    
    cout<<" n2.sumRange(0,2): " << n2.sumRange(0,2);

    
    n2.update(1,2);
    cout<<" n2.sumRange(0,2): " << n2.sumRange(0,2);

    
    cout<<endl;
    
    vector<vector<int>> ma = {{1,2}};
    NumMatrix m(ma);
    int res = m.sumRegion(0, 1, 0, 1);
    cout<<" m.sumRegion(0, 1, 0, 1): "<< res<<endl;
    return 0;
}
