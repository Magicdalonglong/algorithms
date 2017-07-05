//
//  main.cpp
//  nested_list
//
//  Created by Lei Duan on 6/10/17.
//  Copyright © 2017 Lei Duan. All rights reserved.
//

#include <iostream>
#include <vector>
#include <stack>
using namespace std;

struct NestedInteger{
};
class NestedIterator {
    stack<pair<vector<NestedInteger>::iterator, vector<NestedInteger>::iterator>> s;
    
public:
    NestedIterator(vector<NestedInteger> &nestedList) {
        s.emplace(nestedList.begin(), nestedList.end());
    }
    
    int next() {
        
        return (s.top().first++) -> getInteger();
    }
    
    bool hasNext() {
        while(s.size()) {
            if(s.top().first == s.top().second) {
                s.pop();
            }else {
                if(s.top().first -> isInteger()) {
                    return 1;
                }else {
                    s.emplace(s.top().first -> getList().begin(), s.top().first -> getList().end());
                }
            }
        }
        return 0;
    }
};

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
