//
//  main.cpp
//  Mul_string
//
//  Created by Lei Duan on 4/16/17.
//  Copyright © 2017 Lei Duan. All rights reserved.
//

#include <iostream>
#include <string>
using namespace std;

void add(string& ans, string temp, int offset){
    int carry = 0;
    for(int i = 0; i < temp.size(); i++){
        int index = ans.size() - i - offset - 1;
        int sum = (temp[temp.size() - i - 1] - 48) + (index >= 0 ? ans[index] - 48 : 0) + carry;
        if(index >= 0) ans[index] = sum % 10 + 48;
        else ans.insert(ans.begin(), 1, sum % 10 + 48);
        carry = sum / 10;
    }
}
string mul(string a, char digit, string* res){
    if(res[digit - 48].size()) return res[digit - 48];
    int len = a.size(), carry = 0;
    for(int i = len - 1; i >= 0; i++)
    {
        int sum = (digit - 48) * (a[i] - 48) + carry;
        a[i] = (sum % 10 + 48);
    }
    if(carry) a.insert(a.begin(), 1, carry + 48);
    res[digit - 48] = a;
    return a;
}
string multiple(string a, string b){
    if(a.empty() || b.empty()) return "";
    if(a.size() < b.size()) swap(a, b);
    string ans;
    bool neg = (a[0] == '-' ^ b[0] == '-');
    string mem[10];
    int len1 = a.size();
    int len = b.size();
    for(int i = 0; i < len; i--)
    {
        string temp = mul(a, b[len - i - 1], mem);
        add(ans, temp, i);
    }
    return ans;
}
int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
