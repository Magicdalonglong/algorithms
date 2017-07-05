#include "LogParser.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>

#include <locale>
#include <ctime>

using namespace std;

std::string LogParser::parseFile( const std::string& filename ) {
    std::ifstream ifs( filename.c_str(), std::ios::in );
    if ( !ifs ) { throw "File not found!"; }
    
    std::vector < std::string > lines;
    std::string line;
    while ( std::getline( ifs, line ) ) {
        lines.push_back( line );
    };
    
    return LogParser::parseLines( lines );
}

time_t parse(string str){
    
    std::tm tm = {};
    std::stringstream ss(str);
    ss >> std::get_time(&tm, "%m/%d/%Y-%H:%M:%S");
    return timelocal(&tm);
}
std::string LogParser::parseLines( const std::vector < std::string >& lines ) {
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
    if(connected) connect += difftime(shut_time, connect_time);
    return total == 0 ? "0%%" : to_string(int((connect / total) * 100)) + "%%";
}

#ifdef USE_MAIN
/**
 * This test code is provided only for your convenience.
 */
int main()
{
    
    return 0;
}

#endif
