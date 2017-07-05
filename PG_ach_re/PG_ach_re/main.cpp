//
//  main.cpp
//  PG_ach_re
//
//  Created by Lei Duan on 7/4/17.
//  Copyright © 2017 Lei Duan. All rights reserved.
//

#include <iostream>
#include <vector>
#include <list>
#include <map>
using namespace std;

class object {
public:

    int id;
};
class Player;
class achieveManager ;

class animal : public object {
    public:
    string type;
};

class coin : public object {
    public:
    int value;
};

class level : public object {
    public:
    int values;
};

class requirement {
    public:
    int ObjId;
    int val;
};

class reward {
    public:
    int ObjId;
    int val;
};

class AchieveType {
    public:
    int id;
    list<requirement> request;
    list<reward> rewards;
    bool checkPlayer(Player* p);
};

class achieve {
    public:
    int achTypeId;
    int PlayerId;
    bool isClaimed;
    time_t time;
};

class Player {
    public:
    int id;
    int lv;
    string name;
    map<object, int> items;
    void learnAchieve(achieveManager* AchM);
    list<achieve> ach;
};

class achieveManager {
    public:
    map<int, AchieveType> AchTypeList;
    bool checkAch(Player* p);
    void IssueAch(int AchTypeId, Player* p);
    void AddAch(AchieveType T);
    void AddAch(requirement req, reward rew);
};


int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
