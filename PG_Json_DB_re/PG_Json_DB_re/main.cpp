//
//  main.cpp
//  PG_Json_DB_re
//
//  Created by Lei Duan on 7/4/17.
//  Copyright © 2017 Lei Duan. All rights reserved.
//

#include <iostream>
#include <map>
#include <list>
#include <vector>

using namespace std;

class JSONValue;



class row {
public:
    string tablename;
    map<string, string> map;
};

class JSONValue {
    typedef map<string, JSONValue> Map;
public:
    JSONValue() {}
    string getAsString();
    long getAsLong();
    Map getAsMap();
    list<JSONValue> getAsList();
};

class Config {
private:
    map<string, map<string, string>> config;
    /* e.g.:
     seesion:
        sessionid: int
        playerid: int
        name: string
     battle: 
        playerid: int
        sessionid: int
        result: string
    */
    map<string, std::function<string(JSONValue)>> GetFunc;
    string static longToString(JSONValue J);
    string static stringToString(JSONValue J);
    
public:
    Config() {
        GetFunc["int"] = longToString;
        GetFunc["string"] = stringToString;
    }
    map<string, string> Extract(string type, JSONValue data) {
        map<string, string> res;
        map<string, JSONValue> map = data.getAsMap();
        for(auto item : config[type]) {
            string key = item.first;
            string val = GetFunc[key](map[key]);
        }
        return res;
    }
};

vector<row> parseToDB(list<JSONValue> events, Config c) {
    vector<row> res;
    for(auto event : events) {
        string type = event.getAsMap()["type"].getAsString();
        JSONValue data = event.getAsMap()["data"];
        map<string, string> datamap = c.Extract(type, data);
    }
    return res;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
