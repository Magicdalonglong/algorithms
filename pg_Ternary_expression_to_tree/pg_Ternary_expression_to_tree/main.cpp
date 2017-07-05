//
//  main.cpp
//  pg_Ternary_expression_to_tree
//
//  Created by Lei Duan on 6/4/17.
//  Copyright © 2017 Lei Duan. All rights reserved.
//

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;
struct node {
    char val;
    node* left;
    node* right;
    node(int v) : val(v), left(NULL), right(NULL) {}
};
node* ternary_to_tree2(string& s) {
    if(s.empty()) return NULL;
    node* res = new node(s[0]);
    node* temp = res;
    stack<node*> stk;
    
    for(int i = 1; i < s.size(); i += 2) {
        if(s[i] == '?') {
            stk.push(temp);
            temp = temp -> left = new node(s[i + 1]);
        }else if (s[i] == ':') {
            while(stk.top() -> right) {
                stk.pop();
            }
            temp = stk.top() -> right = new node(s[i + 1]);
        }
    }
    return res;
}

node* ternary_to_tree(string& s) {
    if(s.empty()) return NULL;
    node* res = new node(s[0]);
    node* temp = res;
    stack<node*> st;
    for(int i = 1; i < s.size(); i += 2) {
        if (s[i] == '?') {
            st.push(temp);
            temp = temp -> left = new node(s[i + 1]);
        }else {
            while(st.top() -> right) st.pop();
            temp = st.top() -> right =  new node(s[i + 1]);
        }
    }
    return res;
}
void print (node* r) {
    if(r == NULL) return ;
    queue<node*> q;
    q.push(r);
    while(q.size()) {
        int len = q.size();
        while(len--) {
            node* cur = q.front();q.pop();
            cout<<cur -> val<<" ";
            if(cur -> left) q.push(cur -> left);
            if(cur -> right) q.push(cur -> right);
        }
        cout<<endl;
    }
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    vector<string> s = {"a?b:c", "a?b:c?d:e", "a?b?c:d:e"};
    for(auto test : s) {
        cout<<test<<":"<<endl;
        print(ternary_to_tree(test));
    }
    return 0;
}
