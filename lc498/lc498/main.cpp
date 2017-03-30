//
//  main.cpp
//  lc498
//
//  Created by Lei Duan on 2/13/17.
//  Copyright © 2017 Lei Duan. All rights reserved.
//

#include <iostream>
#include <vector>
using namespace std;

vector<int> findDiagonalOrder(vector<vector<int>>& matrix) {
    if(matrix.empty())return {};
    const int m = matrix.size();
    const int n = matrix[0].size();
    
    bool up = 1; //direction, up or down
    int dia = 0;
    vector<int> res;
    
    while(dia < (m+n-1)){
        int i,j;
        if(up){ // up
            for( i=min(dia,m-1),j=(dia<m?0:dia-m+1);i>=0&&j<=min(dia,n-1);i--,j++)
                res.emplace_back(matrix[i][j]);
            up=0;
            
        }else { // down
            
            for( i=(dia<n?0:(dia-n+1)),j=min(dia,n-1);i<=(dia,m-1)&&j>=0;i++,j--)
                res.emplace_back(matrix[i][j]);
            up=1;
        }
        dia++;
        
    }
    return res;
}
int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    vector<vector<int>> m = {{1,2,3},{4,5,6},{7,8,9}};
    vector<int> res = findDiagonalOrder(m);
    for(auto v:res)
        cout<<v<<" ";
    return 0;
}
