//
//  main.cpp
//  PG_Monkey_re
//
//  Created by Lei Duan on 7/4/17.
//  Copyright © 2017 Lei Duan. All rights reserved.
//

#include <iostream>
#include <vector>
using namespace std;
int boundry(int n) {
    if(n < 9) return n;
    int x = (n - 8 ) % 9;
    n -= x;
    while(n > 9) {
        x = x * 10 + 9;
        n -= 9;
    }
    return x * 10 + n;
}
int digitsum(int i) {
    int res = 0;
    while(i) {
        res += i % 10;
        i /= 10;
    }
    return res;
}
void helper(vector<vector<bool>>& matrix, int i, int j, int k) {
    matrix[i][j] = 1;
    pair<int, int> step[4] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};// {1, 1}, {1, -1}, {1, -1}, {-1, -1}};
    for(auto s : step) {
        int x = i + s.first, y = j + s.second;
        if( x < 0 || y < 0 || digitsum(x) + digitsum(y) > k || matrix[x][y]) continue;
        helper(matrix, x, y, k);
    }
}
void monkey_grid(int k) {
    int len = boundry(k);
    vector<vector<bool>> matrix (len + 1, vector<bool> (len + 1, 0));
    helper(matrix, 0, 0, k);
    
    for( int i = 0; i <= len; i++) {
        for(int j = 0; j <=len; j++) {
            cout<< (matrix[len - i][len - j] ? "X" : " ") << " ";
        }
        for(int j = 0; j <=len; j++) {
            cout<< (matrix[len - i][j] ? "X" : " ") << " ";
        }
        cout<<endl;
    }
    
    for( int i = 0; i <= len; i++) {
        for(int j = 0; j <=len; j++) {
            cout<< (matrix[i][len - j] ? "X" : " ") << " ";
        }
        for(int j = 0; j <=len; j++) {
            cout<< (matrix[i][j] ? "X" : " ") << " ";
        }
        cout<<endl;
    }
}


int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    monkey_grid(12);
    monkey_grid(13);
    return 0;
}
