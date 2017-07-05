//
//  main.cpp
//  PG_Monkey_grid
//
//  Created by Lei Duan on 6/18/17.
//  Copyright © 2017 Lei Duan. All rights reserved.
//

#include <iostream>
#include <vector>

using namespace std;
// print the reachable point in a matrix,
// print the number of reachable points

//13
// 1 - 10, 11 - 19, 21 - 29, 31, 38, 41 - ,48
int count_ = 0;
int bound(int k) {
    if(k < 9) return k;
    int x = (k - 8) % 9;
    k -= x;
    while(k > 9) {
        x = x * 10 + 9;
        k -= 9;
    }
    return x * 10 + k;
}
int digit_sum(int n) {
    string s = to_string(n);
    int res = 0;
    for(auto c : s) res += c - 48;
    return res;
}
void helper(vector<vector<bool>>& matrix, int i, int j, int k, int len) {
    count_++;
    matrix[i][j] = 1;
    pair<int, int> step[4] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};// {1, 1}, {1, -1}, {1, -1}, {-1, -1}};
    for(auto s : step) {
        int x = i + s.first, y = j + s.second;
        if(x < 0 || y < 0 || digit_sum(x) + digit_sum(y) > k || matrix[x][y]) continue;
        helper(matrix, x, y, k, len);
    }

}
void Monkey_gird(int k) {
    int len = bound(k);
    vector<vector<bool>> matrix (len + 1, vector<bool> (len + 1, 0));
    count_ = 0;
    helper(matrix, 0, 0, k, len);
    
    cout<<"count:" <<count_<<endl;
    
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
    Monkey_gird(12);
    Monkey_gird(13);
    return 0;
}
