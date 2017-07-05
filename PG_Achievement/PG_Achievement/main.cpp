//
//  main.cpp
//  PG_Achievement
//
//  Created by Lei Duan on 6/23/17.
//  Copyright © 2017 Lei Duan. All rights reserved.
//

#include <iostream>
#include <map>
#include <list>
#include <vector>
#include <set>


using namespace std;
class object {
public:
    int id;
    string name;
};
class friends : public object {
    int PlayerId;
    int degree;
};
class partner : public friends {
    //Business business;
};
class Animal : public object {
};
class Lion : public Animal {
};
class Tiger : public Animal {
};
class Coin : public object {
};
class Level : public object {
};
class item {
public:
    int ObjId;
    int value;
};
class AchieveType {
public:
    int id;
    string name;
    set<item> requests; // objectid, value;
    set<item> reward; // objectid, value;
    bool isMet(int PlayerID);
};

class Achieve {
public:
    Achieve(int PId, int AchID){
        
    }
    int id;
    int Playerid;
    int AchieveTypeid;
    bool isClaimed;
    time_t ClaimedTime;
};


class Player {
public:
    int id;
    int Lv;
    string name;
    map<int, Achieve> Gotachievelist; //  achieveTypeid, achieve
    set<item> itemsList;
    void addAchieve(int Achieveid);
    void claimReward(int Achieveid);
};


class AchievementMaster {
private:
    int id = 0;
public:
    map<int, AchieveType> AchieveTypeList;
    void addAch(AchieveType t) {
        AchieveTypeList[id++] = t;
    }
    void checkAchieve(Player p){
        for(auto ach : AchieveTypeList) {
            if(p.Gotachievelist.count(ach.second.id) == 0 && ach.second.isMet(p.id)) {
                AddAchtoPlayer(ach.second.id, p);
            }
        }
    }
    void AddAchtoPlayer(int AchieveTypeID, Player p){
        Achieve Ach(p.id, AchieveTypeID);
        p.addAchieve(AchieveTypeID);
    }
};

class World {
public:
    AchievementMaster achievementMaster;
    vector<Player> playerlist;
    void getitem(Player p, object o, int val) {
        // add item to player
        achievementMaster.checkAchieve(p);
    }
    void run();
};

int main(int argc, const char * argv[]) {
    // insert code here...
    
    World w;
    AchieveType t;
    w.achievementMaster.addAch(t);
    return 0;
}
