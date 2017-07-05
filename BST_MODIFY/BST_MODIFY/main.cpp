#include <iostream>
#include <stack>
#include <unordered_map>
#include <vector>
#include <cmath>
using namespace std;
void sortColors2(vector<int> &colors, int k) {
    // write your code here
    int len = colors.size();
//    at i = 0:
//    3  2  1  1  4
//    1  2 -1  1  4
//    -1 2 -1  1  4
//     at i = 1:
//    -1 -1 -1  1 4
//    -2 -1 -1  0  4
    
    for (int i = 0; i < len; i++) {
        // Means need to deal with A[i]
        while (colors[i] > 0) {
            int num = colors[i];
            if (colors[num - 1] > 0) {
                // 1. There is a number in the bucket,
                // Store the number in the bucket in position i;
                colors[i] = colors[num - 1];
                colors[num - 1] = -1;
            } else if (colors[num - 1] <= 0) {
                // 2. Bucket is using or the bucket is empty.
                colors[num - 1]--;
                // delete the A[i];
                colors[i] = 0;
            }
        }
    }
    
    int index = len - 1;
    for (int i = len - 1; i >= 0; i--) {
        int cnt = -colors[i];
        // Empty number.
        if (cnt == 0) {
            continue;
        }
        while (cnt > 0) {
            colors[index--] = i + 1;
            cnt--;
        }
    }
}

int helper(stack<int>& stk, stack<char>& op){
    int b = stk.top(); stk.pop();
    int a = stk.top(); stk.pop();
    char oper = op.top(); op.pop();
    int res;
    switch (oper) {
        case '+':
            res=  a + b;
            break;
        case '-':
            res = a - b;
            break;
        case '*':
            res = a * b;
            break;
        case '/':
            res=  a / b;
            break;
        case '^':
            res = pow(a, b);
            break;
            
        default:
            break;
    }
    return res;
    
}



void sort(vector<int>& c, int K){
    int len = c.size();
    
    for(int i = 0; i < len; i++){
        while(c[i] > 0){
            int col = c[i];
            if(c[col - 1] > 0){
                c[i] = c[col];
                c[col - 1] = -1;
            }else{
                c[col - 1]-- ;
                c[i] = 0;
            }
        }
    }
    int index = len - 1;
    for(int k = K - 1; k >= 0; k--){
        int num = - c[k];
        while(num--){
            c[index--] = k + 1;
        }
    }
}



int calculator(string input){
    unordered_map<char, int> hash;
    hash['+'] = 1; hash['-'] = 1; hash['*'] = 2; hash['/'] = 2; hash['^'] = 3;
    stack<int> stk;
    stack<char> op;
    string temp;
    for(int i = 0; i <= input.size(); i++){
        if(i == input.size()){
            stk.push(stoi(temp));
            while(op.size()){
                stk.push(helper(stk, op));
            }
        }else if (isdigit(input[i])){
            temp.push_back(input[i]);
        }else{
            stk.push(stoi(temp)); temp.clear();
            
            while(op.size() && hash[op.top()] > hash[input[i]]){
                stk.push(helper(stk, op));
            }
            op.push(input[i]);
        }
    }
    return stk.top();
}




int main(int argc, const char * argv[]) {
    vector<int> c2 = {3,2,2,1,4};
    vector<int> c3 = {3,2,2,1,4};
    sortColors2(c2, 4);
    sort(c3, 4);
    for(auto c : c2)cout<<c<<" ";
    cout<<endl;

    for(auto c : c3)cout<<c<<" ";
    cout<<endl;
   
    return 0;
}
