#include <iostream>
#include <vector>
#include <list>
using namespace std;

// Binary search (note boundaries in the caller)
int CeilIndex(std::vector<int> &v, int l, int r, int key) {
    while (r-l > 1) {
        int m = l + (r-l)/2;
        if (v[m] >= key)
            r = m;
        else
            l = m;
    }
    
    return r;
}

int LongestIncreasingSubsequenceLength(std::vector<int> &v) {
    if (v.size() == 0)
        return 0;
    
    std::vector<int> tail(v.size(), 0);
    int length = 1; // always points empty slot in tail
    
    tail[0] = v[0];
    for (size_t i = 1; i < v.size(); i++) {
        if (v[i] < tail[0])
            // new smallest value
            tail[0] = v[i];
        else if (v[i] > tail[length-1])
            // v[i] extends largest subsequence
            tail[length++] = v[i];
        else
            // v[i] will become end candidate of an existing subsequence or
            // Throw away larger elements in all LIS, to make room for upcoming grater elements than v[i]
            // (and also, v[i] would have already appeared in one of LIS, identify the location and replace it)
            tail[CeilIndex(tail, -1, length-1, v[i])] = v[i];
    }
    
    return length;
}

class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        if(nums.empty()) return 0;
        vector<int> ends(nums.size() + 1, 0); // index = length, val = end element of this length
        int res = 1;
        ends[1] = nums[0];
        for(int i = 1; i < nums.size(); i++){
            if(nums[i] > ends[res]){
                ends[++res] = nums[i];
            }else if(nums[i] < ends[1]){
                ends[1] = nums[i];
            }else{
                ends[BinarySearch(ends, 1, res, nums[i])] = nums[i];
            }
        }
        //[4,10,4,3,8,9]
        return res;
    }
    int BinarySearch(vector<int>& nums, int low, int high, int key){
        while(low <= high){
            int mid = low + (high - low) / 2;
            if(nums[mid] < key) low = mid + 1;
            else high = mid - 1;
        }
        return high;
    }
};
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int v) : val(v), left (NULL), right(NULL){}
};

TreeNode* helper(vector<int>& nums, int low, int high){
    if(high - low < 1) return high == low ? new TreeNode(nums[low]) : NULL;
    int mid = low + (high - low) / 2 + 1;
    TreeNode* res = new TreeNode(nums[mid]);
    res -> left = helper(nums, low, mid -1);
    res -> right = helper(nums, mid + 1, high);
    return res;
}
TreeNode* buildtree(vector<int>& nums){
    return helper(nums,  0,  nums.size() -1);
    
}
class Linkedlist{
private:
    struct Node{
        int val;
        Node* next;
        Node(int v): val(v), next(NULL){}
    };
    Node* head;
public:
    Linkedlist(int n){
    }
    Linkedlist(){
    }Linkedlist(vector<int> nums){
    }
    Node* next(Node* cur){
        if(!cur) throw exception();
        return cur -> next? cur -> next : NULL;
    }
    bool erase(Node* node){
        Node* temp = new Node(0);
        Node* dummy = temp;
        temp -> next = head;
        while(temp && temp -> next){
            if (temp -> next == node) {
                temp -> next = temp -> next -> next;
                delete node;
                head = dummy -> next;
                delete dummy;
                return true;
            }
        }
        delete dummy;
        return false;
        
    }
    void insert(Node* pos, int val){
        if(!pos) throw exception();
        Node* temp = pos -> next;
        pos -> next = new Node(val);
        pos -> next -> next = temp;
    }
    void push_back(int val){
        if(head == NULL){
            head = new Node(val);
        }else{
            Node* temp = head;
            while(temp && (temp = temp -> next));
            temp -> next = new Node(val);
        }
    }
    void push_front(int val){
        if(head == NULL){
            head = new Node(val);
        }else{
            Node* temp = head;
            head = new Node(val);
            head -> next = temp;
        }
    }
    void pop_front(int val){
        
    }
    
};
pair<int, int> helper(TreeNode* &ans, TreeNode* root, int q, int p, int & dist);

TreeNode* LCA(TreeNode* root, int q, int p){
    TreeNode* ans = NULL;
    int dist = INT_MAX;
    helper(ans, root, q, p, dist);
    return ans;
}

// return value = dist from this node to the node contains q / p (first / second)
pair<int, int> helper(TreeNode* &ans, TreeNode* root, int q, int p, int& dist){
    if(!root) return make_pair(INT_MAX, INT_MAX);
    pair<int, int> res = make_pair(INT_MAX, INT_MAX);
    if(root -> val == q) res.first = 0;
    if(root -> val == p) res.second = 0;
    pair<int, int> lpath = helper(ans, root -> left, q, p, dist);
    pair<int, int> rpath = helper(ans, root -> right, q, p, dist);
    res.first = min(res.first, min(lpath.first, rpath.first));
    res.second = min(res.second, min(lpath.second, rpath.second));
    if(res.first != INT_MAX && res.second != INT_MAX && dist > res.first + res.second){
        ans = root;
        dist = res.first + res.second;
    }
    return res;
}



int main() {
    
    TreeNode* r = new TreeNode(100);
    r -> left = new TreeNode(200);
    r -> right = new TreeNode(1);
    r -> right->left = new TreeNode(7);
    r -> left->left = new TreeNode(150);
    r -> left->left->left = new TreeNode(1);
    r -> left->left ->right= new TreeNode(2);
    r -> left->left ->right->right= new TreeNode(1);
    r -> left->right = new TreeNode(2);
    auto res = LCA(r, 150, 8);
    cout<<(res?res -> val : -100)<<endl;
    return 0;
}
