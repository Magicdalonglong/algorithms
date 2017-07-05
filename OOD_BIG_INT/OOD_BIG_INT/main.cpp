//
//  main.cpp
//  OOD_BIG_INT
//
//  Created by Lei Duan on 5/3/17.
//  Copyright © 2017 Lei Duan. All rights reserved.
//

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class BIGINT {
private:
    vector<bool> data;
public:
    BIGINT(string d){
        for(auto c : d){
            
        }
    }
    void push_bakc(bool d){
        data.push_back(d);
    }
    void pop_back(){
        data.pop_back();
    }
    vector<bool>& getdata(){
        return data;
    }
    void print(){
        string res;
        int bit = 0, dig = 0, car = 0;
        for(auto d : data){
            dig += d ? pow(2, bit) : 0;
            if(dig + 1>= 10) {car = 1;
                res.push_back(dig + 48);
                dig = 0;
            }
        }
        if(car) res.push_back(1);
        reverse(res.begin(), res.end());
        cout<<res;
    }
    BIGINT operator & (BIGINT& other) const {
        BIGINT res;
        for(int i = 0; i < min(data.size(), other.getdata().size()); i++)
            res.getdata().push_back(other.getdata()[i] & data[i]);
        return res;
    }
};
int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    BIGINT big;
    big =
    
    return 0;
}
