#include "PathFinder.h"
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <fstream>

using namespace std;
typedef unordered_map<char, unordered_set<char>> Graph;

vector < string > PathFinder::parseFile( const string& filename ) {
    ifstream ifs( filename.c_str(), ios::in );
    if ( !ifs ) { throw "File not found!"; }
    
    vector < string > lines;
    string line;
    while ( getline( ifs, line ) ) {
        lines.push_back( line );
    };
    
    return PathFinder::parseLines( lines );
}

void helper(char cur, char end, Graph& graph, string& temp, vector<string>& res, unordered_set<char>& path){
    temp.push_back(cur);
    path.insert(cur);
    if(cur == end){
        res.push_back(temp);
    }else{
        for(auto dest : graph[cur]){
            if(!path.count(dest)){
                helper(dest, end, graph, temp, res, path);
            }
        }
    }
    temp.pop_back();
    path.erase(cur);
}

vector < string > PathFinder::parseLines( const vector < string >& lines ) {
    /*
     Your code goes here
     */
    char start = lines.front()[0], end = lines.front()[2];
    Graph graph;
    for(int i = 1; i < lines.size(); i++){
        for(int j = 3; j < lines[i].size(); j++)
            graph[lines[i][0]].insert(lines[i][j]);
    }
    vector<string> res;
    string temp;
    unordered_set<char> path;
    helper(start, end, graph, temp, res, path);
    return res;
}

#ifdef USE_MAIN
/**
 * This test code is provided only for your convenience.
 */
int main()
{
    cout<<"hey";
    
    
    return 0;
}

#endif
