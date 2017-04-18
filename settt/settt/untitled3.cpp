
#include <iostream>

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


bool hasPathSum(TreeNode* root, int sum) {
        if(!root) return 0;
        stack<TreeNode*, int> stk;
        stk.emplace(root, root -> val);
        while(stk.size()){
            TreeNode* cur = stk.top().first;
            int val = stk.top().second;
            stk.pop();
            if(cur -> left) stk.emplace(cur -> left, val * 10 + cur -> left -> val);
            if(cur -> right) stk.emplace(cur -> right, val * 10 + cur -> right -> val);
            if(!cur -> right && !cur -> left && val == sum) return true;
        }
        return false;        
}

 int longestConsecutive(TreeNode* root) {
        int res = 1;
        helper(root, &res);
        return res;
    }
    pair<int, int> helper(TreeNode* root, int* res){
        pair<int, int> res = make_pair(0, 0);
        if(!root) return res;
        pair<int, int> left = helper(root -> left, res);
        pair<int, int> right = helper(root -> right, res);
        res.first = root -> left && root -> left -> val + 1 == root -> val? left.first + 1 : 0;
        res.first = max(res.first, root -> right && root -> right -> val + 1 == root -> val? right.first + 1 : 0);
        res.second = root -> left && root -> left -> val - 1 == root -> val? left.second + 1 : 0;
        res.second = max(res.second, root -> right && root -> right -> val - 1 == root -> val? right.second + 1 : 0);
        *res = max(*res, res.first + res.second - 1);
        return res;
    }
class Solution {
public:
    void solve(vector<vector<char>>& board) {
        if(board.empty()) return ;
        int m = board.size(), n = board[0].size();
        vector<int> father(m * n + 1);
        vector<int> positions;
        iota(father.begin(), father.end(), 0);
        for(int i = 0; i < m; i++)
            for(int j = 0; j < n; j++)
            {
                if(board[i][j] == 'X') continue;
                int cur = i * n + j;
                positions.emplace_back(cur);
                if(i > 0 && board[i - 1][j] == 'O'){
                    int left = (i - 1) * n + j;
                    
                    while(left != father[left]) left = father[left];
                    while(cur != father[cur]) cur = father[cur];
                    father[cur] = left;
                    father[left] = (i * j == 0 || i == m - 1 || j == n - 1)? m * n : father[left];
                }
                if(j > 0 && board[i][j - 1] == 'O'){
                    int above = i * n + j - 1;
                    while(above != father[above]) above = father[above];
                    while(cur != father[cur]) cur = father[cur];
                    father[cur] = above;
                    father[above] = (i * j == 0 || i == m - 1 || j == n - 1)? m * n : father[above];
                }
            }
        for(auto p : positions){
            int pos = p;
            while(p != (p = father[p]));
            board[pos / n][pos % n] = p == m * n? board[pos / n][pos % n] : 'X';
        }
        
    }
};
int main() {
  // cout<<s.longestPalindrome("cbbd");
     
}

