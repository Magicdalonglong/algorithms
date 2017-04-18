//
//  main.cpp
//  template_class
//
//  Created by Lei Duan on 4/16/17.
//  Copyright © 2017 Lei Duan. All rights reserved.
//

#include <iostream>
#include <map>
#include <random>
#include <list>
using namespace std;

template<class Key,class Comp>
class Myheap{
private:
    list<Key> data;
public:
    Myheap();
    void Insert(Key key){
        if(data.empty()) data.emplace_back(key);
        else if (Comp(data.front(),key))
        {
            data.push_front(key);
        }else
            data.emplace_back(key);
    }
    void Pop(){
        if(data.empty()) throw;
        data.pop_front();
        auto it = data.begin();
        for(auto i = data.begin() + 1; i != data.end(); i++)
        {
            if(Comp(*it, *i)) it = i;
        }
        data.emplace_front(*it);
        data.erase(it);
    }
    Key Top(){
        return data.front();
    }
    

};

template <typename T>
struct cmp{
    bool operator()(const T& a, const T& b) const{
        return std::less<T>(a,b);
    }
};

int main(int argc, const char * argv[]) {
    // insert code here...
    
    
    Myheap<int,cmp<int>> h;
    for(int i = 0; i < 10; i++)
    {
        h.Insert(i);
    }
   
    cout<<h.Top();
    std::cout << "\nHello, World!\n";
    return 0;
}
