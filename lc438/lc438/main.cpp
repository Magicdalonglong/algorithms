//
//  main.cpp
//  lc438
//
//  Created by Lei Duan on 2/6/17.
//  Copyright © 2017 Lei Duan. All rights reserved.
//

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        unordered_map<char,int> map;
        for(auto &c:p)
            map[c]++;
        vector<int> res;
        int index =0;
        int len = p.size();
        while(index<s.size())
        {
            cout<<"try :"<<index<<endl;
            int match=0;
            unordered_map<char,int> temp=map;
            for(int i=index;i<s.size();i++){
                if(temp.count(s[i])==0){
                    index=i+1;
                    break;
                }
                if(temp[s[i]]==0){
                    index=i;
                    break;
                }
                if(temp[s[i]]>0){
                    temp[s[i]]--;
                    match++;
                    if(match==len){
                        res.emplace_back(index);
                        index=i+1;
                        break;
                    }
                }
                
            }
        }
        return res;
    }
};

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    Solution s;
    vector<int> res = s.findAnagrams("cbaebabacd", "abc");
    for(auto r:res)
        cout<<r<<" ";
    return 0;
}
