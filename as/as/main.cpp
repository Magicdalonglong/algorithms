

#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <vector>

#include <locale>
#include <ctime>

using namespace std;


time_t parse(string str){
    
    std::tm tm = {};
    std::stringstream ss(str);
    ss >> std::get_time(&tm, "%m/%d/%Y-%H:%M:%S");
    return timelocal(&tm);
}

std::string parseLines( const std::vector < std::string >& lines ) {
    /*
     Your code goes here
     */
    vector<pair<time_t,string>> logs; //first = time, second: status  e.g. START SHUTDOWN
    for(auto& l : lines){
        time_t t = parse(l.substr(1, 20));
        string text = l.substr(25);
        logs.emplace_back(t, text);
    }
    bool connected = false;
    double total = 0, connect = 0;
    time_t start_time = 0, connect_time = 0, shut_time = 0;
    for(auto log : logs){
        if(log.second == "START"){
            
            start_time = log.first;
            connected = false;
            
        }else if(log.second == "CONNECTED"){
            
            connect_time = connected ? connect_time : log.first;
            connected = true;
            
        }else if(log.second == "DISCONNECTED"){
            
            connect += difftime(log.first, connect_time);
            connected = false;
            
        }else if(log.second == "SHUTDOWN"){
            

            shut_time = log.first;
            total += difftime(log.first, start_time);
            if(connected) connect += difftime(log.first, connect_time);
            connected = false;
        }
    }
    cout<<"\nconnect: " <<connect;
    cout<<"\ntotoal: " <<total<<endl;
    
    return total == 0 ? "0%" : to_string(int((connect / total) * 100)) + "%";
}

/**
 * This test code is provided only for your convenience.
 */
int main()
{
    vector<string> times = {
        "(02/03/2002-14:00:00) :: START",
        "(02/03/2002-14:00:00) :: CONNECTED",
        "(02/03/2002-14:08:00) :: DISCONNECTED",
        "(02/03/2002-14:10:00) :: CONNECTED",
        "(02/03/2002-14:15:00) :: SHUTDOWN"};
    
    auto res = parseLines(times);
    cout<<res<<endl;
    return 0;
}

