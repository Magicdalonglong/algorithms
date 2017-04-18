//
//  main.cpp
//  lc315
//
//  Created by Lei Duan on 4/4/17.
//  Copyright © 2017 Lei Duan. All rights reserved.
//

#include <iostream>
#include <vector>
#include <iostream>
using namespace std;
class Solution {
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
        //   if(!root) return 0;
        if(root ->low == low && root -> high == high){
            return root -> count;
        }
        int mid = root ->low + (root ->high - root ->low) / 2;
        if(high <= mid) return sum(root -> left, low, high);
        else if(low > mid) return sum(root -> right, low, high);
        else return sum(root -> left, low, mid) + sum(root -> right, mid + 1, high);
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

int main(int argc, const char * argv[]) {
    // insert code here...
    vector<int> v = {5,2,6,1};
    Solution s;
    auto res = s.countSmaller(v);
    std::cout << "Hello, World!\n";
    return 0;
}
