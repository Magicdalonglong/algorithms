#include <iostream>
#include <queue>
#include <stack>
#include <iostream>
#include <random>
#include <set>

using namespace std;

class MinStack {
public:
    /** initialize your data structure here. */
    stack<pair<int,int>> stk;
    MinStack() {
        
    }
    
    void push(int x) {
        int min_ = min (x, stk.top().second);
        stk.emplace(x,min_);
    }
    
    void pop() {
        stk.pop();
    }
    
    int top() {
        return stk.top().first;
    }
    
    int getMin() {
        return stk.top().second;
    }
};


int kill(int n, int k){
    int f = 0;
    for(int i = 1; i <= n; i++) f = (f + k) % i;
    return f;
}


int main(){    
   
    cout<<kill(5,3);

    MinStack stk;
    stk.push(12);stk.push(13);stk.push(1);stk.push(132);stk.push(1211);
    cout<<" stk.top() "<<stk.top();
    cout<<"\nmin "<<stk.top();


}

