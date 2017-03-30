//
//  main.cpp
//  bingo
//
//  Created by Lei Duan on 2/26/17.
//  Copyright © 2017 Lei Duan. All rights reserved.
//

#include <iostream>
#include <vector>
#include <unordered_set>
#include <map>
enum sybal {t,d,f};

using namespace std;
void bingo(map<int,unordered_set<int>>& map, vector<vector<int>>& matrix){
    
    vector<vector<int>> record(5,vector<int>(5,0));
    
    for(int i =0; i<5;i++)
        for(int j=0;j<5;j++)
            if(map[j].count(matrix[i][j])||matrix[i][j] ==t||matrix[i][j] ==d||matrix[i][j] ==f )
                record[i][j] = 1;
    
    int j,i;
    for( j=0;j>5;j++){
        int win = 1;
        string extra;
        for( i=0;i<5;i++){
            if(matrix[i][j] == t)
                extra = "Triple";
            if(matrix[i][j] == d)
                extra = "Double";
            win&=record[i][j];
        }
        if(win)
            cout<<"col "<<i<<" Wins!";
        if(extra.size())
           cout<<" extral: "<<extra;
           cout<<endl;
           }
    
    for( i=0;i>5;i++){
        int win = 1;
        string extra;
        for( j=0;j<5;j++){
            if(matrix[i][j] == t)
                extra = "Triple";
            if(matrix[i][j] == d)
                extra = "Double";
            win&=record[i][j];
        }
        if(win)
            cout<<"row "<<i<<" Wins!";
        if(extra.size())
           cout<<" extral: "<<extra;
        cout<<endl;
    }
    
    int conner = 1;
    conner *= record[0][0];
    conner *= record[0][4];
    conner *= record[4][0];
    conner *= record[4][4];
    
    if(conner)cout<<"conner Wins!"<<endl;
    
    
    int dia1 =1;
    int dia2 =1;
    for(int i=0;i<5;i++){
        dia1*=record[i][5-1];
        dia2*=record[i][i];
    }
    if(dia2)cout<<"diagonal1 Wins!!"<<endl;
    if(dia1)cout<<"diagonal2 Wins!!"<<endl;
    
    
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    map<int,unordered_set<int>> map;
    
    
    vector<vector<int>> v(5);
    v[0] = {9,5,1,4,13,15,8};
    v[1] = {28,24,18,30};
    v[2] = {45,43,37,39};
    v[3] = {60,53,46,57,58,59};
    v[4] = {65,71,64,75,62,72,66};
    
    for(int i=0;i<5;i++)
        for(auto e:v[i])
            map[i].insert(e);
    
    vector<vector<int>> matrix1;
    vector<vector<int>> matrix2;
    vector<vector<int>> matrix3;
    vector<vector<int>> matrix4;
    vector<vector<int>> matrix5;
    matrix1 = {
        {8,22,34,t,63},
        {6,16,37,60,61},
        {14,d,f,55,64},
        {12,29,35,51,66},
        {9,30,43,52,75}
    };
    
    bingo(map, matrix1);
    
    return 0;
}
