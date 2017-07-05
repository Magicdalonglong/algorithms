#include "iostream"
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
using namespace std;

vector<string> readrecord(string& filename){
    
    ifstream ifile;
    ifile.open(filename);
    string line;
    unordered_map<string, int> hash; // hostname, freq
    
    if (ifile.is_open())
    {
        while ( getline (ifile,line) )
        {
            int index = line.find_first_of(32);
            string hostname = line.substr(0, index);
            hash[hostname]++;
        }
        ifile.close();
    }    
    ifile
    else {
        cout << "Unable to open dict file, check the path!!";
        exit(1);
    }
    return vector<string>(hash.begin(), hash.end());
}

void writtofile(string ofilename, vector<string>& records){
    
    ofstream myfile;
    myfile.open (ofilename);
    for(auto re :  records){
        myfile << re << endl;
    }
    
    myfile.close();
}
int main()
{
    // read the string filename
    string filename;
    cin >> filename;
    vector<string> res = readrecord(filename);
    writtofile("records_filename.txt", res);
    
    return 0;
}