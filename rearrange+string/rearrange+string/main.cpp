//
//  main.cpp
//  rearrange+string
//
//  Created by Lei Duan on 2/27/17.
//  Copyright © 2017 Lei Duan. All rights reserved.
//

#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>


using namespace std;
string rearrangeString(string s, int k) {
    if(s.empty()||k==0)return s;
    int len = s.size();
    vector<int> dict(26,0); // index -> char    val -> freq
    for(auto c:s)
        dict[c-97]++;
    priority_queue<pair<int,char>> pq;// freq , char
    
    for(int i=0;i<26;i++)
        if(dict[i])
            pq.push(make_pair(dict[i],i));
    string res;
    
    while(res.size()<s.size()){
        vector<pair<int,char>> cache;
        for(int i=0;i<min(k,len);i++){
            if(pq.empty())return "";
            auto temp = pq.top();
            pq.pop();
            res.push_back(temp.second+97);
            len--;
            if(--temp.first>0)
                cache.emplace_back(temp);
        }
        for(auto c:cache) pq.push(c);
    }
    return res;
}
int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    cout<<rearrangeString("aa",2);
    return 0;
}
