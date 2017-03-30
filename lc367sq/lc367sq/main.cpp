//
//  main.cpp
//  lc367sq
//
//  Created by Lei Duan on 2/25/17.
//  Copyright © 2017 Lei Duan. All rights reserved.
//

#include <iostream>
#include <vector>

using namespace std;
bool isPerfectSquare(int num) {
    int left = 0,right = num;
    while(left<=right){
        long mid = left+(right-left)/2;
        long long midsq = mid*mid;
        if(midsq>num)right = mid-1;
        else if(midsq<num)left = mid+1;
        else return 1;
    }
    return 0;
    
}


int strStr(string haystack, string needle) {
    const int len = needle.size();
    const int hlen = haystack.size();
    if(len==0&&hlen==0)return 0;
    vector<int> prep(len,0);
    int match = 0;
    for(int i=1;i<len;i++){
        if(needle[i]==needle[match])prep[i]=++match;
        else match=0;
    }
    cout<<"prep: ";
    for(auto p:prep)
        cout<<p<<" ";
    for(int i=0;i<hlen-len+1;){
        int k=0;
        while(k<len&&needle[k]==haystack[i+k])k++;
        if(k==len)return i;
        else i+=(k?(k-prep[k-1]):1);
    }
    return -1;
    
}
int main(int argc){
   
    // insert code here...
    cout<<strStr("aabaaabaaac", "aabaaac");
    return 0;
}
