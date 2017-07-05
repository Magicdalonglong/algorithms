//
//  main.cpp
//  isupper
//
//  Created by Lei Duan on 4/27/17.
//  Copyright © 2017 Lei Duan. All rights reserved.
//

#include <iostream>
#include <string>
using namespace std;

struct pre{
    bool operator()(const int & i) const{
        return isupper(i);
    }
};
int main(int argc, const char * argv[]) {
    // insert code here...
    string ss = "HelaAA";
    string cust = find_first_of(ss.begin() + 1, ss.end(), pre());
    std::cout << "Hello, World!\n";
    return 0;
}
