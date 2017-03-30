//
//  main.cpp
//  lc436
//
//  Created by Lei Duan on 2/18/17.
//  Copyright © 2017 Lei Duan. All rights reserved.
//

#include <iostream>
#include <vector>
using namespace std;


  struct Interval {
      int start;
      int end;
      Interval() : start(0), end(0) {}
      Interval(int s, int e) : start(s), end(e) {}
  };

class Solution {
public:
    vector<int> findRightInterval(vector<Interval>& intervals) {
        
        vector<pair<int,int>> map;
        int index=0;
        for(auto i:intervals)
            map.emplace_back(i.start,index++);
        sort(map.begin(),map.end());
        vector<int> res;
        for(auto i:intervals)
            res.emplace_back(helper(map,i.end));
        
        return res;
    }
    int helper(vector<pair<int,int>>& map, int tar){
        int i=0,j=map.size()-1;
        if(map.back().first<tar)return -1;
        
        while(i<j){
            int mid = i+(j-i)/2;
            if(map[mid].first>tar)
                j=mid;
            else if(map[mid].first<tar)
                i=mid+1;
            else return mid;
        }
        
        return j;
    }
    
};





int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    string s = "abcd";
    cout<<s.substr(3,-1)<<endl;
    return 0;
}
