#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

void helper(unordered_set<int>& set,vector<vector<int>>& res, vector<int>& temp){
    int recent = temp.back();
    bool end = 1;
    vector<int> cache;
    for(auto i : temp)
    {
        int add = abs(i - recent);
        if(add == 0) continue;
        if(!set.count(add))
        {
            cache.emplace_back(add);
            end = 0;
        }
    }
    for(auto c : cache){
        set.insert(c);
        temp.push_back(c);
        helper(set,res,temp);
    }
    if(end){
        res.push_back(temp);
    }
    
}
vector<vector<int>> printpath(vector<int>& nums){
    unordered_set<int> set;
    vector<vector<int>> res; vector<int> temp;
    for(auto n : nums) set.insert(n);
    temp = nums;
    helper(set,res,temp);
    return res;
}

vector<int> lexicalOrder(int n) {
    vector<int> res;
    int cur = 1;
    while(res.size() < n){
        res.emplace_back(cur);
        if(cur * 10 <= n)
            cur *= 10;
        else{
            if(cur == n)
                cur /= 10;
            cur ++;
        }
    }
    return res;
}

int main() {
    cout<<"Hello";
    
    // RegisterCenter* Regis = &RegisterCenter::getinstace();
    vector<int> num = {1,0,0,1,1,0,1,0,1,0,1,0,0,0,0,1,0,0,1};
    vector<int> nums = {5,30};
    auto res = printpath(nums);
    for(auto r : res){
        for(auto i : r) cout<<i<<' ';
        cout<<endl;
    }
    lexicalOrder(34);
    return 0;
}
