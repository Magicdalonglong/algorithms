//
//  main.cpp
//  PG_room_connection
//
//  Created by Lei Duan on 6/19/17.
//  Copyright © 2017 Lei Duan. All rights reserved.
//

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <stack>

using namespace std;

struct room {
    int id;
    int x, y;
    int len, wid;
    room(){}
    room(int i, int x_, int y_, int l, int w) : id(i), x(x_), y(y_), len(l), wid(w) {}
};
struct info {
    multimap<int, int>::iterator left, right, top, bot;
    info(multimap<int, int>::iterator l, multimap<int, int>::iterator r, multimap<int, int>::iterator t, multimap<int, int>::iterator b) : left(l), right(r), top(t), bot(b){}
};
/* 
1 1,   4 3 =
1 5,   3 1
4 4,   3 3
  0 1 2 3 4 5 6 7
0 x x x x x x x x
1 x O O O x 1 x 3
2 x O O O x 1 x
3 x O O O x 1 x
4 x O O O 2 2 2
5 x x x x 2 2 2
6 x x x x 2 2 2
*/

bool IsConnected(vector<room>& rooms) {
    multimap<int, int> left, right, top, bot;   // val, id
    unordered_map<int, info*> hash;   // id, iterators
    int len = rooms.size();
    
    for(auto r : rooms) {
        auto left_it = left.emplace(r.y, r.id);
        auto right_it = right.emplace(r.y + r.wid - 1, r.id);
        auto top_it = top.emplace(r.x, r.id);
        auto bot_it = bot.emplace(r.x + r.len - 1, r.id);
        hash[r.id] = new info(left_it, right_it, top_it, bot_it);
    }
    
    stack<int> stack;
    unordered_set<int> mark;
    stack.push(hash.begin() -> first);
    
    
    
    
    while(stack.size()) {
        len --;
        int id = stack.top(); stack.pop();
        mark.insert(id);
        int left_ = hash[id] -> left -> first;
        int top_ = hash[id] -> top -> first;
        int right_ = hash[id] -> right -> first;
        int bot_ = hash[id] -> bot -> first;
        
        auto range_right = right.equal_range(left_ - 1);
        for(auto it = range_right.first; it != range_right.second; it++) {
            auto bot_it = hash[it -> second] -> bot;
            if(bot_it -> first >= top_ && mark.count(bot_it -> second) == 0)
                stack.push(bot_it -> second);
        }
        
        auto range_top = top.equal_range(bot_ + 1);
        for(auto it = range_top.first; it != range_top.second; it++) {
            auto right_it = hash[it -> second] -> right;
            if(right_it -> first >= left_ && mark.count(right_it -> second) == 0)
                stack.push(right_it -> second);
        }
        
        auto range_left = left.equal_range(right_ + 1);
        for(auto it = range_left.first; it != range_left.second; it++) {
            auto bot_it = hash[it -> second] -> bot;
            if(bot_it -> first >= top_ && mark.count(bot_it -> second) == 0)
                stack.push(bot_it -> second);
        }
        
        auto range_bot = bot.equal_range(top_ - 1);
        for(auto it = range_bot.first; it != range_bot.second; it++) {
            auto right_it = hash[it -> second] -> right;
            if(right_it -> first >= left_ && mark.count(right_it -> second) == 0)
            stack.push(right_it -> second);
        }
    }
    
    return len == 0;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    room r1 (0, 1, 1, 4, 3);
    room r2 (1, 1, 5, 3, 1);
    room r3 (2, 4, 4, 3, 3);
    room r4 (3, 1, 7, 1, 1);
    
    vector<room> test = {r1, r2, r3, r4};
    cout<<IsConnected(test);

    return 0;
}
