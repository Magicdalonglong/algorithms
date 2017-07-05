//
//  main.cpp
//  PG_String_re
//
//  Created by Lei Duan on 7/4/17.
//  Copyright © 2017 Lei Duan. All rights reserved.
//

#include <iostream>
#include <map>
#include <list>
#include <stack>
using namespace std;

struct action {
    int index;
    int len;
    pair<int, char> setchar;
    action(): index(-1), len(-1), setchar({-1, 0}){}
};

struct node {
    char* str;
    node* parent;
    action actions;
    
    string backtracking() {
        stack<action> stk;
        stk.push(actions);
        int index = 0;
        int len = 0;
        string res;
        map<int, char> setchars;
        node* temp = parent;
        while(temp) {
            stk.push(temp -> actions);
            temp = temp -> parent;
        }
        while(stk.size()) {
            index += (stk.top().index >= 0 ? stk.top().index : 0);
            len = (stk.top().len >= 0? stk.top().len : len);
            if(stk.top().setchar.first >= 0)
                setchars.emplace(index + stk.top().setchar.first, stk.top().setchar.second);
            stk.pop();
        }
        for(int i = index; i < index + len; i++) {
            if(setchars.count(i)) {
                res.push_back(setchars[i]);
            }else {
                res.push_back(str[i]);
            }
        }
        return res;
    }
    
    // for init
    node(char* str_) : str(str_), parent(NULL){
        actions.index = 0;
        int i;
        for(i = 0; str[i] != '\0'; i++);
        actions.len = i;
    }
    // for substr
    node(node* pa, int index, int len) : str(pa -> str), parent(pa){
        actions.len = len;
        actions.index = index;
    }
    
    // for setchar
    node(node* pa, int index, char c) : str(pa -> str), parent(pa){
        actions.setchar = {index, c};
    }
};


class Mstring {
private:
    
    node* Node;
public:
    Mstring (char* str_) {
        Node = new node(str_);
    }
    Mstring() {}
    Mstring substr(int index, int len) {
        Mstring res;
        res.Node = new node (Node, index , len);
        return res;
    }
    
    void setchar(int index, char c) {
        Node = new node (Node, index , c);
    }
    string toString() {
        
        return Node -> backtracking();
    }
};

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    Mstring str1 ("abcdefg");
    
    Mstring str2 = str1.substr(3,3);
    cout<<str1.toString()<<endl;
    cout<<str2.toString()<<endl<<endl;
    
    str1.setchar(4, 'P');
    str1.setchar(5, 'M');
    str2.setchar(2, 'X');
    
    cout<<str1.toString()<<endl;
    cout<<str2.toString()<<endl<<endl;
    
    Mstring str3 = str2.substr(1, 1);
    str3.setchar(0, '@');
    Mstring str4 = str1.substr(1, 5);
    
    cout<<str1.toString()<<endl;
    cout<<str2.toString()<<endl;
    cout<<str3.toString()<<endl;
    cout<<str4.toString()<<endl<<endl;
    return 0;
}
