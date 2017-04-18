#include <iostream>
#include <vector>
using namespace std;

int longest(vector<int>& nums){
    int res = 0, i = 0, j = 0;
    bool one;
    for(i = 0, j = 0; j < nums.size(); j++){
        if(nums[j] == one) i = j;
        res = max(res, nums[i] ? j - i : j - i + 1);
        one = nums[j];
   }
    return res;
    
}

class Solution {
public:
    int search(vector<int>& nums, int target) {
        int i = 0, len = nums.size();
        for(i = 0; i < nums.size() - 1 && nums[i] < nums[i + 1]; i++);
        nums.insert(nums.end(), nums.begin() + i + 1, nums.end());
        nums.resize(len);
        return binarysearch(nums.begin(), nums.end(), target);
    }
    int binarysearch(vector<int>::iterator begin, vector<int>::iterator end, int tar){
        auto left = begin, right = end - 1;
        while(left <= right){
            auto mid = left + (right - left) / 2;
            if(*mid < tar) left = mid + 1;
            else if(*mid > tar) right = mid - 1;
            else return int(mid - left);
        }
        return -1;
        
    }
};

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
 struct ListNode
 {
    int val; 
    ListNode* next;
    ListNode(int v): val(v), next(NULL){}
     
 };

class Solution2 {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        int len1 = 0, len2 = 0;
        ListNode* temp1 = l1, *temp2 = l2, *res = NULL;
        while(temp1){
            temp1 = temp1 -> next;
            len1 ++;
        }
        while(temp2){
            temp2 = temp2 -> next;
            len2 ++;
        }
        temp1 = l1; temp2 = l2;
        while(len2 && len1){
            int sum = 0;
            if(len1 == len2){
                sum = temp2 -> val + temp1 -> val;
                len1--; 
                len2--;
                temp1 = temp1 -> next;
                temp2 = temp2 -> next;
            }else if(len1 > len2){
                 sum = temp1 -> val;
                 len1--;
                 temp1 = temp1 -> next;
            }
            else {
                 sum = temp2 -> val;
                 len2--;
                 temp2 = temp2 -> next;
            }
            push_front(res, sum);
        }
        ListNode* pre = NULL;
        int car = 0;
        while(res){
            ListNode* temp = res -> next;
            res -> next = pre;
            int val = res -> val + car;
            car = (val) / 10;
            res -> val = (val) % 10;
            pre = res;
            res = temp;
            
        }
        return pre;
    }
    void push_front(ListNode* &res, int sum){
        ListNode* temp = res;
        res = new ListNode(sum);
        res -> next = temp;
    }
    
    
    
    
    
};


void pmt(vector<int>& needle){
    vector<int> table(needle.size(), 0);
    int nsize = needle.size();
    for (int i = 1, j = 0; i < nsize - 1;){
            if (needle[i] != needle[j]){
                if (j>0){
                    j = table[j - 1];
                }
                else{
                    i++;
                }
            }
            else{
                table[i] = j + 1;
                i++;
                j++;
            }
        }
    for(auto t : table) cout<<t <<" ";
}
int main() {
    cout<<"Hello\n";
    

     vector<int> n = {1,2,3,1,2,3};
    pmt(n);

    return 0;
}
