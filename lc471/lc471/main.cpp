//
//  main.cpp
//  lc471
//
//  Created by Lei Duan on 2/21/17.
//  Copyright © 2017 Lei Duan. All rights reserved.
//

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    string encode(string s) {
        if(s.size()<4)return s;
        const int len = s.size();
        vector<vector<string>> dp(len,vector<string>(len,""));
        helper(dp,0,len-1,s);
        return dp[0][len-1];
    }
    
    void helper(vector<vector<string>> &dp,int i, int j, string &s){
        dp[i][j]= s.substr(i,j-i+1);
        if(j-i<3)return ;
//        if(i==0&&j==9)
//        {
//            int aa;
//            cin>>aa;
//        }
        for(int len = 1;len*2<=j-i+1;len++)
        {
            if((j-i+1)%len==0){
                bool fine = 1;
                for(int num = 1;num<(j-i+1)/len;num++)
                    if(s.substr(i,len)!=s.substr(i+num*len,len)){
                        fine = false;
                        break;
                    }
                if(fine){
                    if(dp[i][i+len]=="")helper(dp,i,i+len-1,s);
                    int l = dp[i][i+len-1].size();
                    int rep = (j-i+1)/len;
                    if(to_string(rep).size()*l+len+2 < dp[i][j].size()) //worth to comp
                        dp[i][j] = to_string(rep)+"["+dp[i][i+len-1]+"]";
                }
                
            }
        }
        
        
//        if(i==0&&j==9)
//        {
//            int aa;
//            cin>>aa;
//        }
        if(j-i<4)return ;
        for(int len = 1;len<j-i+1;len++){
            if(dp[i][i+len-1]=="")helper(dp,i,i+len-1,s);
            if(dp[i+len][j]=="")helper(dp,i+len,j,s);
            if(dp[i][i+len-1].size()+dp[i+len][j].size()<dp[i][j].size())
                dp[i][j] = dp[i][i+len-1]+dp[i+len][j];
        }
        
//        if(i==0&&j==9)
//        {
//            int aa;
//            cin>>aa;
//        }
    }
    
    
};

int main(int argc, const char * argv[])

{
    // insert code here...
    std::cout << "Hello, World!\n";
    string st = "aaaaaaaaaac";
    Solution s;
    cout<<s.encode(st);
    return 0;
}
