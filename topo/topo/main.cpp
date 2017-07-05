#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <unordered_map>
#include <unordered_set>
using namespace std;

class Solution {
public:
    string alienOrder(vector<string>& words) {
        int len = words.size();
        vector<int> mark(26, -1); // -1 = not exist, 0 = not visited, 1 = visiting, 2 = visited
        unordered_map<char, unordered_set<char>> hash; // a -> {b, c} = a in front of b and c,
        for(int i = 0; i < len; i++){
            bool comped = 0;
            for(int j = 0; j < words[i].size(); j++){
                mark[words[i][j] - 97] = 0;
                if(comped == 0 && i > 0 && j < words[i - 1].size() && words[i - 1][j] != words[i][j]){
                    hash[words[i - 1][j]].emplace(words[i][j]);
                    comped = 1;
                }
            }
        }
        string res;
        for(int i = 0; i < 26; i++){
            if(!helper(res, hash, mark, i + 97)) return "";
        }
        reverse(res.begin(), res.end());
        for(int i = 0; i < 26; i++){
            if(mark[i] == 0) res.push_back(i + 97);
        }
        return res;
    }
    bool helper(string& res, unordered_map<char, unordered_set<char>>& hash, vector<int>& mark, char cur){
        if(mark[cur - 97] == 1) return false;
        if(mark[cur - 97] == 2 || mark[cur - 97] == -1) return true;
        mark[cur - 97] = 1;
        for(auto n : hash[cur]) if(!helper(res, hash, mark, n)) return false;
        mark[cur - 97] = 2;
        res.push_back(cur);
        return true;
    }
};
int main() {
    
    Solution s;
    vector<string> d = {"za","zb","ca","cb"};
    auto res = s.alienOrder(d);
    for(auto r : res)cout<<r<<" ";
    
    return 0;
}
