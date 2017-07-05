//
//  main.cpp
//  PG_Mutble_string
//
//  Created by Lei Duan on 6/19/17.
//  Copyright © 2017 Lei Duan. All rights reserved.
//

#include <iostream>
#include <vector>
#include <stack>
#include <map>

using namespace std;

struct Action {
    int index, len;
    map<int, char> setchar;
    Action(): index(0), len(0) {}
    Action(int i, int l): index(i), len(l) {}
};

struct TreeNode {
    char* str;
    TreeNode* parent;
    Action actions;
    
    // constructor for initial
    TreeNode(string* input) : parent(NULL) {
        str = &((*input)[0]);
        actions.len = (*input).size();
    }
    
    // constructor for substr
    TreeNode(int start_, int len_, TreeNode* p) : parent(p) {
        str = p -> str;
        actions.index = p -> actions.index + start_;
        actions.len = len_;
        actions.setchar = p -> actions.setchar;
    }
    
    
    // constructor for setchar
    TreeNode(int index, char c, TreeNode* p) : parent(p){
        str = p -> str;
        actions = p -> actions;
        actions.setchar.emplace(actions.index + index, c);
    }
};

class MutableString {
private:
    TreeNode* node;
public:
    MutableString(const string input) {
        string *s = new string(input);
        node = new TreeNode(s);
    }
    MutableString(TreeNode* in) : node(in){}
    MutableString() : node( NULL) {}
    //MutableString(MutableString& other){ node = other.node;}
    //MutableString(MutableString&& other){ node = other.node; other.node = nullptr; }

    
    string toString() {
        char* scr = node -> str;
        int index = node -> actions.index, len = node -> actions.len;
        auto set = node -> actions.setchar;
        string res = scr + index;
        res.resize(len);
        
        for(auto it = set.lower_bound(index); it != set.lower_bound(index + len); it++) {
            res[it -> first - index] = it -> second;
        }
        return res;
        
    }
    
    MutableString substr(int index, int len) {
        MutableString m;
        m.node = new TreeNode(index, len, node);
        return m;
    }
    
    void setchar(int index, char c) {
        node = new TreeNode(index, c, node);
    }
};

int main(int argc, const char * argv[]) {
    // insert code here...
    
    MutableString str1 ("abcdefg");
    MutableString str2 = str1.substr(3,3);
    cout<<str1.toString()<<endl;
    cout<<str2.toString()<<endl<<endl;
   
    str1.setchar(4, 'P');
    str1.setchar(5, 'M');
    str2.setchar(2, 'X');

    cout<<str1.toString()<<endl;
    cout<<str2.toString()<<endl<<endl;
    
    MutableString str3 = str2.substr(1, 1);
    str3.setchar(0, '@');
    MutableString str4 = str1.substr(1, 5);
    
    cout<<str1.toString()<<endl;
    cout<<str2.toString()<<endl;
    cout<<str3.toString()<<endl;
    cout<<str4.toString()<<endl<<endl;
    
    
    return 0;
}
