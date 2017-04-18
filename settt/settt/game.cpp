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
    minheap(int type){
        
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
    
};
                 
class maxheap {
private:
    multiset<int,vector<int>,std::greater<int>> data;
public:
    maxheap(){}
    int top(){
        return *(data.begin();
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
};


vector<int> median(vector<int>& nums){   
    
    minheap minhp;
    maxheap maxhp;
    vector<int> res;
    for(auto n : nums){
        if(minhp.size() < maxhp.size()){
            if(n > minhp.top()){ // fit in right
                maxhp.push(minhp.pop());
                minhp.push(n);                
            }else{
                maxhp.push(n);                
            }                     
        }else if(minhp.size() > maxhp.size()){
            if(n < maxhp.top()){ // fit in left
                minhp.push(maxhp.pop());
                maxhp.push(n);                
            }else {
                minhp.push(n);                
            }                     
        }else{ 
            if(n < maxhp.top()){ // fit in left
                maxhp.push(n);                
            }else
                minhp.push(n);
        }       
        if(minhp.size() == maxhp.size())
            return (minhp.top() + maxhp.top()) / 2;
        else return minhp.size() > maxhp.size() ? minhp.top() : maxhp.top();
        
    }
    
    
    
    
}

int main() {
   
    return 0;
}
