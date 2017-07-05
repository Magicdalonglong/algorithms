//
//  main.cpp
//  Vtable_
//
//  Created by Lei Duan on 6/27/17.
//  Copyright © 2017 Lei Duan. All rights reserved.
//

#include <iostream>
#include <new>
#include <climits>
using namespace std;


int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    long l = 1, r = LONG_MAX;
    long mid;
    while(l <= r){
        
        try {
            mid = l + (r - l) / 2;
            int arr[mid];
            cout<<arr[mid - 1]<<" ";
            
        } catch (bad_array_new_length ) {
            
            r = mid - 1;
            continue;
        }
        l = mid + 1;
    }
    cout<<endl<<l<<endl;
    
    return 0;
 
}
