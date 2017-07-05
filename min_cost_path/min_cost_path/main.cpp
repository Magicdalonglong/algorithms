//

#include <iostream>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <cmath>
#include <iterator>

using namespace std;
int cost(int a, int b){
    if(a == 0 && b == 1 || a == 1 && b == 0) return 4;
    if(a == 0 && b == 2 || a == 2 && b == 0) return 3;
    if(a == 3 && b == 1 || a == 1 && b == 3) return 14;
    if(a == 2 && b == 3 || a == 3 && b == 2) return 15;
    if(a == 5 && b == 3 || a == 3 && b == 5) return 1;
    if(a == 5 && b == 4 || a == 4 && b == 5) return 1;
    if(a == 2 && b == 4 || a == 4 && b == 2) return 1;
    return 1;
}
int helper(unordered_set<int>& set, int m, int n, pair<int,int> start, pair<int, int> dest){
    if(dest == start) {
        return 0;
    }
    pair<int,int> step[4] = {{0,1},{0,-1},{1,0},{-1,0}};
    std::set<int> neighbor;
    for(auto s : step){
        int x = dest.first + s.first;
        int y = dest.second + s.second;
        if(x < 0 || x >= m || y < 0 || y >= n || set.count(x * n + y)) continue;
        set.insert(x * n + y);
        neighbor.emplace(cost(x * n + y, dest.first * n + dest.second) + helper(set, m, n, start, make_pair(x, y)));
        set.erase(x * n + y);
    }
    return neighbor.size()? *neighbor.begin() : 1000;
}

int min_cost_path(int m, int n, pair<int,int> start, pair<int, int> dest){
    unordered_set<int> set;
    set.emplace(dest.first * n + dest.second);
    return helper(set, m, n, start, dest);
}

int main()
{
    int m = 3, n = 2;
    auto res = min_cost_path(m, n, make_pair(0,1), make_pair(1,1));
    
    cout<<res<<endl;
    
    return 0;
}
