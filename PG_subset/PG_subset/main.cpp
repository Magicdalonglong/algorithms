//
//  main.cpp
//  PG_subset
//
//  Created by Lei Duan on 6/26/17.
//  Copyright © 2017 Lei Duan. All rights reserved.
//

#include <iostream>
#include <vector>
#include <stack>
using namespace std;

class subset {
private:
    vector<int> nums;
    vector<int> temp;
    
    // first = start_index of that step, second = current search index
    stack<pair<vector<int>::iterator,vector<int>::iterator>> s;
    bool init;
    
public:
    subset(vector<int>& nums_) {
        nums = nums_;
        sort(nums.begin(), nums.end());
        s.emplace(nums.begin(), nums.begin());
        init = 1;
    }
    bool hasnext(){
        
        if(init) {
            return 1;
        }
        while(s.size()) {
            if(s.top().second == nums.end()) {
                if(temp.size()) temp.pop_back();
                s.pop();
            }else {
                while(s.top().second != nums.end() && s.top().second != s.top().first && *(s.top().second) == *(s.top().second - 1)) {
                    s.top().second++;
                }
                if(s.top().second != nums.end()) return 1;
            }
        }
        return 0;
    }
    vector<int> next () {
        if(hasnext() == 0) return {};
        if(init) {
            init = 0;
            return  {};
        }
        temp.push_back(*(s.top().second++));
        s.emplace(s.top().second, s.top().second);
        return {};
    }
    
};
class vechile {
public:
    vechile(){
        cout<<"constr vechile"<<endl;
    }
    
    ~vechile(){
        cout<<"destor vechile"<<endl;
    }
    
    int getspeed(){
        return 100;
    }
};

class car : public vechile {
public:
    car(){
        cout<<"constr car"<<endl;
    }
    ~car(){
        cout<<"destory car"<<endl;
    }
    int getspeed(){
        return 200;
    }
};

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    vector<int> nums = {};
    subset obj( nums );
    int count = 0;
    while (obj.hasnext()) {
        count++;
        for(auto n : obj.next()) {
            cout<<n<<" ";
        }
        cout<<endl;
    }
//    //char* p;
//    int* i;
//    string* s;
//    vector<int> vec = {1,2,3,4,3,2,2,3,3};
////    int arr[123];
////    cout<<sizeof(p);
////    cout<<sizeof(i);
////    cout<<sizeof(s);
////    cout<<sizeof(arr);
////    cout<<sizeof(vec);
//    car c;
//    vechile * p =  &c;
//    cout<<p -> getspeed();
//    
////    car c;
////    cout << c.getspeed();
//    
    
 
    return 0;
}
