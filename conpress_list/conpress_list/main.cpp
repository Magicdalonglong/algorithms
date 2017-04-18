//
//  main.cpp
//  sort_list_which_sorted_in_abs
//
//  Created by Lei Duan on 4/9/17.
//  Copyright © 2017 Lei Duan. All rights reserved.
//

#include <iostream>
using namespace std;
struct LinkedList {
    int val;
    LinkedList* next;
    LinkedList(int v) : val(v), next(NULL){}
};

LinkedList* compress(LinkedList* head){
    LinkedList* dummy = new LinkedList(0);
    LinkedList* temp = dummy;
    int count = 1;
    while(head && head -> next){
        if(head -> val == head -> next -> val)
            count ++;
        else {
            if(count > 1)
            {
                temp -> next = new LinkedList(count);
                temp -> next -> next = new LinkedList(head -> val);
                temp = temp -> next -> next;
                count = 1;
            }else{
                temp -> next = new LinkedList(head -> val);
                temp = temp -> next;
            }
        }
        head = head -> next;
    }
    
    if(count > 1)
    {
        temp -> next = new LinkedList(count);
        temp -> next -> next = new LinkedList(head -> val);
        count = 1;
    }else{
        temp -> next = new LinkedList(head -> val);
    }
    
    
    return dummy -> next;
}

void print(LinkedList* h){
    while(h){
        cout<<h -> val <<" ";
        h = h -> next;
    }
    cout<<endl;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    LinkedList * h = new LinkedList(1);
    LinkedList* temp = h;
    for(int i = 65; i < 85; i += 1)
    {
        temp -> next = new LinkedList(i > 79? 65: i < 70? 67 :i);
        temp = temp -> next;
    }
    print(h);
    h = compress(h);
    print(h);
    int x = INT_MIN;
    x = abs(x);
    cout<<x<<endl;
    
    return 0;
}
