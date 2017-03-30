#include <iostream>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <stdlib.h>
using namespace std;


string minWindow(string s, string t) {
    int todo = t.size();
    if(todo==0||s.empty())return "";
    int i=0,j=0;
    int index = 0, len = s.size()+1;
    vector<int> map(127,0);
    vector<int> dict(127,0);
    
    for(auto c:t){
        map[c]++;
        dict[c]=1;
    }
    
    while(j<=s.size()&&i<=j){
        if(todo==0){    //matched all, we shrink front
            if(j-i<len){
                index = i; len = j-i;
            }
            if(dict[s[i]]&&++map[s[i]]>0)
                todo++;
            i++;// start index
        }else{  //going forward to match more
            
            if(dict[s[j]]&&map[s[j]]-->0)todo--;
            j++;
        }
    }
  //  0123456789012
  //  ADOBECODEBANC
//    ABC
    return len == s.size()+1? "": s.substr(index,len);
}
int main(int argc) {
    // insert code here...
    auto res= minWindow("ADOBECODEBANC","ABC");
    cout<<res;
    return 0;
}
