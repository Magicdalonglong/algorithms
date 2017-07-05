//
//  main.cpp
//  Pg_ JsontoDB
//
//  Created by Lei Duan on 6/18/17.
//  Copyright © 2017 Lei Duan. All rights reserved.
//

#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <list>
using namespace std;

class List {
};

class row {
public:
    string tablename;
    map<string, string> map;
};


class JSONValue;

typedef map<string, JSONValue> Map;

class JSONValue {
public:
    JSONValue() {}
    string getAsString();
    long getAsLong();
    Map getAsMap();
    List getAsList();
};

class Config {
private:
    
    unordered_map<string, std::function<string(JSONValue)>> Func_hashMap;
    unordered_map<string,string> TypeMap;  // key_name, type,   e.g.  name, string
public:
    Config() {
        Func_hashMap["string"] = getAsString;
        Func_hashMap["long"] = getAsLong;
    }
    string static getAsString(JSONValue J) {
        return J.getAsString();
    }
    string static getAsLong(JSONValue J) {
        return to_string(J.getAsLong());
    }
    void readConfigFile() {
        // fill TypeMap
    }
public:
    string operator() (string key_name, JSONValue data) {
        return Func_hashMap[TypeMap[key_name]](data);
    }
};

vector<row> parseToDB(list<JSONValue> events, Config c) {
    vector<row> res;
    for(auto event: events) {
        Map event_map = event.getAsMap();
        string typeName = event_map["type"].getAsString();
        Map data_map = event_map["data"].getAsMap();
        for(auto item : data_map) {
            string key_name = item.first;
            
        }
    }
    
    return res;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
