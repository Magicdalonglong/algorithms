//
//  main.cpp
//  lc143
//
//  Created by Lei Duan on 4/16/17.
//  Copyright © 2017 Lei Duan. All rights reserved.
//

#include <iostream>

using namespace std;
  struct ListNode {
      int val;
      ListNode *next;
      ListNode(int x) : val(x), next(NULL) {}
  };

class Solution {
public:
    void reorderList(ListNode* head) {
        if(!head || !head -> next) return;
        ListNode* slow = head, *fast = head;
        while(fast && fast -> next)
        {
            slow = slow -> next;
            fast = fast -> next -> next;
        }
        ListNode* mid = slow -> next;
        slow -> next = NULL;
        reverselist(mid);
        ListNode* temp = head;
        while(temp && mid){
            ListNode* next = mid -> next;
            mid -> next = temp -> next;
            ListNode* next2 = temp -> next;
            temp -> next = mid;
            temp = next2;
            mid = next;
        }
    }
    void reverselist(ListNode* &head){
        ListNode* pre = NULL;
        while(head){
            ListNode* temp = head -> next;
            head -> next = pre;
            pre = head;
            head = temp;
        }
        head = pre;
    }
};
void print(ListNode* head){
    while (head) {
        cout<<head -> val<<" ";
        head = head -> next;
    }
    cout<<endl;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    
    ListNode* head = new ListNode(1);
    head -> next = new ListNode(2);
    head -> next -> next = new ListNode(3);
    Solution s;
    s.reorderList(head);
    print(head);

    std::cout << "Hello, World!\n";
    return 0;
}
