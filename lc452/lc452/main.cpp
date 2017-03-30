//
//  main.cpp
//  lc452
//
//  Created by Lei Duan on 2/18/17.
//  Copyright © 2017 Lei Duan. All rights reserved.
//

#include <iostream>
#include <vector>
using namespace std;


int findMinArrowShots(vector<pair<int, int>>& points) {
    sort(points.begin(),points.end(),[](const pair<int,int>& p1, const pair<int,int>& p2)->bool {return p1.first<p2.first;});
    int res = 0;
    int index = 0;
    while(index < points.size()){
        int end = points[index].second;
        int i;
        for(i=index+1;i<points.size()&&points[i].first<=end;i++);
        res ++;
        index = i;
    }
    return res;
}


int findMinArrowShots2(vector<pair<int, int>>& points) {
    sort(points.begin(),points.end(),[](const pair<int,int>& p1, const pair<int,int>& p2)->bool {return p1.first<p2.first;});
    int res = 0;
    int index = 0;
    while(index < points.size()){
        int end = points[index].second;
        int i;
        for(i=index+1;i<points.size()&&points[i].first<=end;i++);
        res ++;
        index = i;
    }
    return res;
}
int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    vector<pair<int,int>> v = {make_pair(3,9),make_pair(7,12),make_pair(3,8),make_pair(6,8),make_pair(9,10),make_pair(2,9),make_pair(0,9),make_pair(3,9),make_pair(0,6),make_pair(2,8)};
    
    cout<<findMinArrowShots(v)<<endl  ;
    cout<<findMinArrowShots2(v) <<endl ;
    return 0;
}
