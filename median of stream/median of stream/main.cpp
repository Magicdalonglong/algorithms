#include<iostream>
#include<vector>
#include<cstdlib>
#include<queue>
#include<set>
#include<stack>
#include<stack>
#include<unordered_map>
#include<cstdlib>
#include<string>
#include<fstream>
#include<cstdio>
#include <fstream>
#include <unistd.h>

using namespace std;
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

struct TreeNode
{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int a):val(a), left(NULL), right(NULL){}
    
};

class MedianFinder {
private:
    priority_queue<int> maxheap;
    multiset<int> minheap;
public:
    /** initialize your data structure here. */
    
    MedianFinder() {
        
    }
    
    void addNum(int num) {
        if(maxheap.size() < minheap.size()){   // right head has more element
            if(num > *(minheap.begin()))      // comming num fit in right
            {
                int trans = *(minheap.begin());
                minheap.erase(minheap.begin());
                maxheap.push(trans);
                minheap.insert(num);
            }
            else maxheap.push(num);
            
        }else if(maxheap.size() > minheap.size()){ // left has more
            if(num < maxheap.top())      // comming num fit in left
                int trans = maxheap.top();
            maxheap.pop();
            minheap.insert(trans);
            maxheap.push(num);
            else minheap.insert(num);
            
        }else {
            if(maxheap.empty())
                maxheap.push(num);
            else if(num > minheap.begin())      // comming num fit in right{
                minheap.insert(num);
            else
                maxheap.push(num);
        }
    }
    
    double findMedian() {
        if(maxheap.size() != minheap.size())
            return maxheap.size() < minheap.size()? minheap.begin() : maxheap.top();
        else return double(minheap.begin() + maxheap.top()) / 2.0;
    }
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder obj = new MedianFinder();
 * obj.addNum(num);
 * double param_2 = obj.findMedian();
 */



class Solution {
private:
    struct Node{
        TreeNode* node;
        bool left;
        bool right;
        Node(TreeNode* r): node(r),left(false),right(false){}
    };
public:
    int maxPathSum(TreeNode* root) {
        if(!root)return 0;
        stack<Node> stk;
        int res = 0;
        unordered_map<TreeNode*, int> map;
        stk.emplace(root);
        while(stk.size()){
            TreeNode* cur = stk.top().node;
            if(cur->right && !stk.top().right){
                stk.top().right = 1;
                stk.emplace(cur->right);
            }
            else if(cur->left && !stk.top().left ){
                stk.top().left = 1;
                stk.emplace(cur->left,-1,-1);
            }
            else {
                stk.pop();
                int left = cur->left? map[cur->left]:0;
                int right = cur->right? map[cur->right]:0;
                int val = cur->val;
                res = max(res,left+right+val);
                map[cur] = max(0,max(left,right)+val);
            }
        }
        return res;
        
    }
};

int main()
{
    int i = -1294;
    
    
    return 0;
}
