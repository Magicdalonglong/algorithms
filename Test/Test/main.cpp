//
//  main.cpp
//  Test
//
//  Created by Lei Duan on 6/26/17.
//  Copyright © 2017 Lei Duan. All rights reserved.
//

#include <iostream>
#include <vector>
using namespace std;

long long s = 1000000000000000;
long long s2 = 10000;

int recur(int i) {
    cout << i << endl;
    int j = i + 1;
    int k = i + 1;
    string s = "12";
    //string s = to_string(i) ;
    return stoi(s) + recur(i + 1);
    
}

int recur1(int i) {
    cout << i << endl;
    return recur(i + 1);
}

int main(int argc, const char * argv[]) {
    // insert code here...
    cout << recur(1) << endl;
    
//    int arr[7];
//    int *arr2 = arr;
//    string* s;
//    int * p = arr;
//    cout<<sizeof(p)<<" ";
//    cout<<sizeof(int);
//    for (int i = 1; i < 100000000; i = i*2) {
//        int arr[i];
//        cout << i << " " ;
//        cout << arr[i - 1] << endl;;
    //}
    return 0;
}
