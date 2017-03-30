//
//  main.cpp
//  lc352
//
//  Created by Lei Duan on 2/21/17.
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

class SummaryRanges {
public:
    /** Initialize your data structure here. */
    vector<Interval> data;
    SummaryRanges() {
        
    }
    
    void addNum(int val) {
        if(data.empty())
        {
            data.emplace_back(Interval(val,val));
            return ;
            
        }
        int i=0, j=data.size()-1;
        while(i<j){
            int mid = i+(j-i)/2;
            if(data[mid].start>val)
                j=mid;
            else i=mid+1;
        }
        if(data[i].start>val)
        {
            if(data[i-1].end+1==val&&data[i].start-1==val){
                data[i-1].end = data[i].end;
                data.erase(data.begin()+i);
            }
            else if(data[i].start-1==val)
                data[i].start = val;
            else if(data[i-1].end+1==val)
                data[i-1].end = val;
            else
                data.insert(data.begin()+i,Interval(val,val));
        }else{
            if(data[i].end+1==val)
                data[i].end=val;
            else data.emplace_back(Interval(val,val));
            
        }
    }
    
    vector<Interval> getIntervals() {
        return data;
    }
};

/**
 * Your SummaryRanges object will be instantiated and called as such:
 * SummaryRanges obj = new SummaryRanges();
 * obj.addNum(val);
 * vector<Interval> param_2 = obj.getIntervals();
 */
int main(int argc, const char * argv[]) {
    // inser
    
    std::cout << "Hello, World!\n";
    SummaryRanges s;
    s.addNum(1);
    s.addNum(3);
    s.addNum(7);
    s.addNum(2);
    s.addNum(6);
    s.addNum(9);
    s.addNum(4);
    s.addNum(10);
    s.addNum(5);
    
    
    for(auto p:s.getIntervals())
        cout<<" ["<<p.start<<","<<p.end<<"]";
        
    
    return 0;
}
