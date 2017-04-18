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

LinkedList* sortlist(LinkedList* head){
    LinkedList* dummy = new LinkedList(0);
    dummy -> next = head;
    LinkedList* temp = dummy;
    while(temp && temp -> next){
        if(temp -> next -> val < 0)
        {
            LinkedList* node = temp -> next;
            temp -> next = temp -> next -> next;
            node -> next = dummy -> next;
            dummy -> next = node;
        }
        temp = temp -> next;
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
    for(int i = 1; i < 20; i += 1)
    {
        temp -> next = new LinkedList(i&1? -i:i);
        temp = temp -> next;
    }
    print(h);
    h = sortlist(h);
    print(h);
    
    
    return 0;
}
