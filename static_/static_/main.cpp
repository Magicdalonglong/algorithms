//
//  main.cpp
//  static_
//
//  Created by Lei Duan on 2/23/17.
//  Copyright © 2017 Lei Duan. All rights reserved.
//

#include <iostream>
#include <vector>
using namespace std;

void fuc(int i){
     int count =0;
     int count2 =0;
    count++;
    count2+=2;
    cout<<"i is "<<i<<"  count is "<<count<<"  count2 is "<<count2<<endl;;
}


bool valid(int num){
    if(num<10&&num!=0)return 1;
    if(num>=10&&num<=26)return 1;
    return 0;
}
int numDecodings(string s) {
    if(s=="0"||s.empty()) return 0;
    if(s.size()==1)return 1;
    int dp1 =1, dp2 =1;   //      i-2(dp1) i-1(dp2) | i(waiting for decide)
    
    int cur = 1, temp;
    for(int i=1;i<s.size();i++)
    {
        bool lasttwo = valid(stoi(s.substr(i-1,2)));
        bool lastone = valid(stoi(s.substr(i,1)));
        if(lasttwo&&lastone) cur = dp1+dp2;
        else if(!lasttwo&&!lastone)return 0;
        else cur = lastone? dp2:dp1;
        temp = dp2;
        dp2 = cur;
        dp1 = temp;
    }
    return cur;
}



bool isOneEditDistance(string s, string t) {
    
    const int len1 = int(s.size());
    const int len2 = int(t.size());
    if(s==t||abs(len1-len2)>1)return 0;
    
    for(int i=0;i<min(len1,len2);i++){
        if(s[i]==t[i])continue;
        // dif
        if(len1==len2)
            return s.substr(i+1)==t.substr(i+1);
        else if(len1>len2)
            return s.substr(i+1)==t.substr(i);
        else
            return t.substr(i+1)==s.substr(i);
    }
    return 1;
    
    
    
}


int minDistance(string word1, string word2) {
    if(word1.empty()||word2.empty())return max(word1.size(),word2.size());
    const int len1 = word1.size();
    const int len2 = word2.size();
    vector<vector<int>> dp (len1+1,vector<int>(len2+1,0));
    
    for(int i=0;i<=len1;i++) dp[i][0]=i;
    for(int i=0;i<=len2;i++) dp[0][i]=i;
    
    for(int i=0;i<=len1;i++)
        for(int j=0;j<=len2;j++)
        {
            if(word1[i]!=word2[j])
                dp[i][j] = min(min(dp[i][j-1],dp[i-1][j]),dp[i-1][j-1])+1;
            else
                dp[i][j] = dp[i-1][j-1];
            
        }
    return dp.back().back();
    
    
    
}

vector<int> numIslands2(int m, int n, vector<pair<int, int>>& positions) {
    if(m*n==0)return {};
    vector<int> unionfind (m*n,-1);
    vector<pair<int,int>> step = {{1,0},{-1,0},{0,-1},{0,1}};
    
    vector<int> res(int(positions.size()));
    int index = 0;
    int cur = positions[0].first*n+positions[0].second;
    unionfind[cur]=cur;
    res[0] = 1;
    for(int i=1;i<positions.size();i++){
        int x = positions[i].first;
        int y = positions[i].second;
        cur = x*n+y;
        unionfind[cur] = cur;
        int connect = 0;
        for(auto s:step){
            int dx = x+s.first;
            int dy = y+s.second;
            int around = dx*n+dy;
            
            if(dx>=0&&dx<m&&dy>=0&&dy<n&&unionfind[around]!=-1){
                while(cur != unionfind[cur])cur = unionfind[unionfind[cur]];
                while(around != unionfind[around])around = unionfind[unionfind[around]];
                
                connect += (cur!=around);   // found new connected island,
                unionfind[cur] = around;
            }
        }
        res[index+1] = res[index++]+1-connect;
        
    }
    return res;
    
}
int main(int argc,
         
         const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
 
    vector<pair<int,int>> vec = {{0,0},{0,1},{1,2},{2,1}};
    
    auto res = numIslands2(3,3,vec);
    return 0;
}
