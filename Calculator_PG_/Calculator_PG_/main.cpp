#include <iostream>
#include <stack>
#include <vector>
#include <cmath>
#include <unordered_map>
using namespace std;

// 3 + 2 * 332
//2+3*2+3
void helper( stack<int>& operands, stack<char>& operators) {
    int right = operands.top(); operands.pop();
    int left = operands.top(); operands.pop();
    int res = 0;
    char op = operators.top(); operators.pop();
    
    switch (op) {
        case '+':
            res = left + right;
            break;
        case '*':
            res = left * right;
            break;
        case '^':
            res = pow(left, right);
            break;
        default:
            break;
    }
    operands.push(res);
}



int cal(string& s, int& i) {
    stack<int> operands;
    stack<char> operators;
    unordered_map<char, int> map;
    map['+'] = 1; map['*'] = 2; map['^'] = 3;
    string temp;
    for(; i < s.size(); i++) {
        if(s[i] == '(') operands.push(cal(s, ++i));
        else if(s[i] == ')') break;
        else if(isdigit(s[i])) temp.push_back(s[i]);
        else {
            if(temp.size())operands.push(stoi(temp));
            temp.clear();
            while(operators.size() && s[i] != '^' && map[s[i]] <= map[operators.top()]) {
                helper(operands, operators);
            }
            operators.push(s[i]);
        }
    }
    if(temp.size())operands.push(stoi(temp));
    while(operators.size()) {
        helper(operands, operators);
    }
    return operands.size() ? operands.top() : 0;
}
int calculator(string& str) {
    int index = 0;
    return cal(str, index);
}
int main() {
    vector<string> cases;
    string s = "4+1";
    string s2 = "1+1";
    string s33 = "1+1*4+3*2+2*3";
    string s3 = "1+1*4+3*2+2^3";
    string s4 = "(34*2)";
    string s5 = "(34*(2+1))";
    string s6 = "(1+1)*4+3*(2+2)^3";
    cases.push_back(s);
    cases.push_back(s2);
    cases.push_back(s33);
    cases.push_back(s3);
    cases.push_back("2^12+12^2");
    cases.push_back("2+3+4*4+32*23+3*2^2");
    cases.push_back("2^3^2");
    cases.push_back(s4);
    cases.push_back(s5);
    cases.push_back(s6);
    cases.push_back("(2^3)^2");
    cases.push_back("2^3^2");
    cases.push_back("2^3^2+123*123+123^3+23*12+3^12+2^2^3*12+12");
    cases.push_back("((2^3^2+123*(123+12*(3^3+2))+3*(2+(3^2+2^2))^3*12+12))");
    
    for(auto test_case : cases){
        cout<<test_case<<" : "<<calculator(test_case)<<endl;
    }
    return 0;
}
//4*3-3*5^2
/*
 Your last C# code is saved below:
 using System;
 
 public class Test
 {
 public static void Main()
 {
 Console.WriteLine("Hello");
 }
 }
 */
