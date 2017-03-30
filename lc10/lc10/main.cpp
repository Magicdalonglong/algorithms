
#include <iostream>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <stdlib.h>
using namespace std;


bool isMatch(string s, string p) {
    int index =0;
    for(int i=0;i<s.size();i++){
        char c = s[i];
        if(p[index]==c)index++;    //match directly
        else if(p[index]=='.')index++;    // matched by .
        else if(index+1<p.size()&&p[index+1]=='*'){  //not matched, discord "X*" go ahead of p
            index+=2;
            i--;
        }
        else if(index>0&&p[index]=='*'&&(p[index-1]=='.'||p[index-1]==c));  //index not ++ to make more match
        else if(index>0&&p[index]=='*'){i--;index++;}
        else return 0;
    }
    if(index<p.size()-1||(index==p.size()-1&&p[index]!='*'))return 0;
    return 1;
}
bool isMatch2(string s, string p) {
    int  slen = s.size(), plen = p.size(), i, j, iStar=-1, jStar=-1;
    
    for(i=0,j=0 ; i<slen; ++i, ++j)
    {
        if(p[j]=='*')
        { //meet a new '*', update traceback i/j info
            iStar = i;
            jStar = j;
            --i;
        }
        else
        {
            if(p[j]!=s[i] && p[j]!='?')
            {  // mismatch happens
                if(iStar >=0)
                { // met a '*' before, then do traceback
                    i = iStar++;
                    j = jStar;
                }
                else return false; // otherwise fail
            }
        }
    }
    cout<<"j :"<<j;
    while(p[j]=='*') {
        ++j;
        cout<<"j is "<<j<<' ';
    }
    return j==plen;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    cout<<isMatch2("aab","*a*b");
    char a = 48;
    char b = 49;
    string pre;
    int pi = 1;
    int ni = -1;
    cout<<endl;
    cout<<"positive one is ";
    for(int i=31;i>=0;i--)
            cout<<int(bool(pi&(1<<i)))<<" ";
    cout<<endl;
    cout<<"negitive one is ";

    for(int i=31;i>=0;i--)
        cout<<int(bool(ni&(1<<i)))<<" ";
    cout<<endl;

    
    
    cout<<pre;

    return 0;
}
