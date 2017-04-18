//
//  main.cpp
//  print_dia
//
//  Created by Lei Duan on 4/9/17.
//  Copyright © 2017 Lei Duan. All rights reserved.
//

#include <iostream>
#include <vector>
using namespace std;

void printdia(int n){
    
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++)
            if(i == j || i + j == n -1)cout<<"x";
            else cout<<" ";
        cout<<endl;
    }
    
    for(int i = 0; i < n; i++){
        int gap = i < n / 2 ? i : n - i - 1, cur = 1;
        for(int j = 0; j < n; j++){
            if(j >= gap && j < n - gap)
                cout<<cur++;
            else cout<<" ";
        }
        cout<<endl;
    }
    
    
}


int main(int argc, const char * argv[]) {
    // insert code here...
    printdia(5);
    std::cout << "Hello, World!\n";
    return 0;
}
