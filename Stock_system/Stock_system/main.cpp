#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <unordered_map>
#include <list>
#include <map>

using namespace std;


//这题 用multimap做的，排序是unstable排序，不大完善，，
class stock {
private:
    struct info{
        int freq;
        bool in;
        multimap<int, string>::iterator it;
        info(): freq(0), in(false) {}
        info(int f, map<int, string>::iterator i) : freq(f), it(i) {}
    };
    multimap<int,string> top; // freq, company;
    unordered_map<string, info> hash; // company, ferq;
    int minfreq;
    int k;
public:
    stock(int k_) : k(k_), minfreq(0){}
    void feed(vector<pair<string, int>>& data){
        for(const auto& d : data) feed(d.first, d.second);
        
    }
    void feed(string name, int price){
        hash[name].freq++;
        if(hash[name].in){
            top.erase(hash[name].it);
            auto it = top.emplace(hash[name].freq, name);
            hash[name].it = it;
        }else if(top.size() < k){
            auto it = top.emplace(hash[name].freq, name);
            hash[name].it = it;
            hash[name].in = 1;
        }else if(hash[name].freq > top.begin() -> first){
            hash[top.begin() -> second].in = 0;
            top.erase(top.begin());
            auto it = top.emplace(hash[name].freq, name);
            hash[name].it = it;
            hash[name].in = 1;
        }
        dis();

        
    };
    void dis(){
        for(auto it = top.rbegin(); it != top.rend(); it++)
            cout<<it -> second<<" ";
        cout<<endl;
    }
};
int main(){
    
    stock s(3);
    vector<pair<string, int>> data = {{"a",9},{"b",1},{"b",4},{"b",4},{"c",4},{"c",5}};
    s.feed(data);
    vector<pair<string, int>> data2 = {{"a",1},{"b",1},{"b",1},{"c",4},{"d",33},{"d",33},{"d",31}};
    vector<pair<string, int>> data3 = {{"af",1},{"af",1},{"af",1},{"af",4},{"c",5},{"c",5}};
    s.feed(data2);
    s.feed(data3);
    cout<<endl;
    return 0;
}
