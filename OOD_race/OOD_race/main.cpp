//
//  main.cpp
//  OOD_race
//
//  Created by Lei Duan on 4/28/17.
//  Copyright © 2017 Lei Duan. All rights reserved.
//

#include <iostream>
#include <unordered_map>
#include <list>
#include <vector>
using namespace std;

class Race{
private:
    unordered_map<int, list<int>> freq; // freq, list of this freq;
    unordered_map<int, pair<int, list<int>::iterator>> hash;  // house, <freq, iter>
    int leader = 0;
public:
    void feed(vector<pair<int, int>>& input){
        for(auto i : input) feed(i);
    }
    void feed(pair<int, int> data){ // house #,  freq;
        freq[data.second].emplace_back(data.first);
        if(hash.count(data.first)){
            freq[hash[data.first].first].erase(hash[data.first].second);
        }
        hash[data.first].first = data.second;
        hash[data.first].second = --freq[data.second].end();
        leader = max(leader, data.second);
        DashBorad(3);
    }
    void DashBorad(int k){
        
        for(int count = 0, lead = leader; lead >= 0; lead--){
            for(auto i : freq[lead]){
                cout<<i<<" ";
                count++;
                if(count == k) {
                    cout<<endl;
                    return ;
                }
            }
        }
        cout<<endl;
    }
};

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    vector<pair<int, int>> input = {{1,1},{2,1},{3,1},{1,2},{4,1},{2,2},{2,3},{1,3},{3,2},{4,2},{4,3}};
    
    Race r;
    r.feed(input);
    return 0;
}
