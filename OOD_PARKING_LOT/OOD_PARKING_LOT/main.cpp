//
//  main.cpp
//  OOD_PARKING_LOT
//
//  Created by Lei Duan on 5/3/17.
//  Copyright © 2017 Lei Duan. All rights reserved.
//


//用户可以输入location，pick-up time&date, return time&date，可以返回number of cars  takingilable。设计所需的table及table的内容。.

#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>
#include <cmath>
#include <list>



using namespace std;

class table{
private:

    struct rent{
        int rentID;
        string location;
        int start;
        int end;
        rent(){}
        rent(int id, string l, int s, int e):rentID(id), location(l), start(s), end(e){}
    };
    struct data{
        int sum;
        int id;
        list<rent> rents;
        vector<int>  taking;
        data(){
            sum = 0; id = 0;  taking.assign(100, 0);
        }
    };
    unordered_map<string, data> hash;
    unordered_map<int, list<rent>::iterator> renthash;
public:
    void add(string l, int sum){
        hash[l].sum += sum;
    }
    int query(string l, int a, int b){
        int overlop = 0;
        data *d = &(hash[l]);
        for(int i = a; i <= b; i++){
            overlop = max(d ->  taking[i], overlop);
        }
        return d -> sum - overlop;
        
    }
    int book(string l, int a, int b){
        for(int i = a; i <= b; i++)
            hash[l]. taking[i]++;
        int id = ++hash[l].id;
        hash[l].rents.emplace_back(id, l, a, b);
        renthash[id] = --hash[l].rents.end();
        return id;
    }
    
    void cancel(int id){
        string l = renthash[id] -> location;
        int s = renthash[id] -> start, e = renthash[id] -> end;
        hash[l].rents.erase(renthash[id]);
        for(int i = s; i <= e; i++){
            hash[l]. taking[i]--;
        }
    }
};


int main(int argc, const char * argv[]) {
    // insert code here...
    table t;
    t.add("LA", 120);
    t.add("NY", 100);
    t.book("LA", 13, 16);
    t.book("LA", 15, 20);
    cout<<t.query("LA", 1, 10)<<endl;
    cout<<t.query("LA", 14, 15)<<endl;
    cout<<t.query("LA", 17, 30)<<endl;
    std::cout << "\nHello, World!\n";
    
    return 0;
}
