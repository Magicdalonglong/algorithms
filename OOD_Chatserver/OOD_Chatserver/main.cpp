#include <iostream>
#include <vector>
#include <set>
#include <vector>
#include <unordered_set>
using namespace std;

class minheap {
private:
    multiset<int> data;
public:
    minheap(){
        
    }
    int top(){
        return *(data.begin());
    }
    int size(){
        return data.size();
    }
    int pop(){
        int res = *(data.begin());
        data.erase(data.begin());
        return res;
    }
    void push(int x){
        data.insert(x);
    }
    bool empty(){
        return data.empty();
    }
};

class maxheap {
private:
    multiset<int,std::greater<int>> data;
public:
    maxheap(){}
    int top(){
        return *(data.begin());
    }
    int size(){
        return data.size();
    }
    int pop(){
        int res = *(data.begin());
        data.erase(data.begin());
        return res;
    }
    void push(int x){
        data.insert(x);
    }
    bool empty(){
        return data.empty();
    }
};


vector<int> median(vector<int>& nums){
    
    minheap minhp;
    maxheap maxhp;
    vector<int> res;
    for(auto n : nums){
        if(minhp.size() > maxhp.size()){  //rigth has more
            if(n > minhp.top()){ // fit in right
                maxhp.push(minhp.pop());
                minhp.push(n);
            }else{
                maxhp.push(n);
            }
        }else if(minhp.size() < maxhp.size()){ // left has more
            if(n < maxhp.top()){ // fit in left
                minhp.push(maxhp.pop());
                maxhp.push(n);
            }else {
                minhp.push(n);
            }
        }else{
            if(maxhp.empty() || n < maxhp.top()){ // fit in left
                maxhp.push(n);
            }else
                minhp.push(n);
        }
        if(minhp.size() == maxhp.size())
            res.emplace_back((minhp.top() + maxhp.top()) / 2);
        else res.emplace_back( minhp.size() > maxhp.size() ? minhp.top() : maxhp.top());
        
    }
    
    return res;
    
}

int main() {
    vector<int> v = {5, 15, 1, 3, 2, 8, 7, 9, 10, 6, 11, 4};
    auto res = median(v);
    for(auto r : res) cout<<r <<" ";
    cout<<endl;
    return 0;
}
