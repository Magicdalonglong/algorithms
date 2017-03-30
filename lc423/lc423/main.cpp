#include <iostream>
#include <vector>
using namespace std;


class Solution {
public:
    bool hasPath(vector<vector<int>>& maze, vector<int> start, vector<int> destination) {
        const int m = maze.size();
        const int n = maze[0].size();
        maze[start[0]][start[1]]=2;
        int inp;
        cout<<"start: "<<start[0]<<","<<start[1]<<endl;
        if(start[0]==4&&start[1]==2)
            cin>>inp;
        vector<pair<int,int>> step = {make_pair(0,-1),make_pair(0,1),make_pair(1,0),make_pair(-1,0)};
        
        for(auto s:step){
            int dx,x;
            dx = x = start[0]+s.first;
            int dy, y;
            dy = y = start[1]+s.second;
            
            if(!(x>=0&&x<m&&y>=0&&y<n&&maze[x][y]==0))continue;
            int i;
            for(i = (s.first?x:y);;i+=(s.first?s.first:s.second))
                if(s.first)
                {
                    if(i<0||i>=m||maze[i][y]==1){
                        dx = i-s.first;
                        break;
                    }
                }else {
                    if(i<0||i>=n||maze[x][i]==1){
                        dy = i-s.second;
                        break;
                    }
                }
            if(dx ==destination[0]&&dy==destination[1])return 1;
            if(maze[dx][dy]==2)continue;
            if(hasPath(maze,{dx,dy},destination)) return 1;
        }
        return 0;
    }
};
int main(){
    Solution s;
    vector<vector<int>> m = {{0,0,1,0,0},{0,0,0,0,0},{0,0,0,1,0},{1,1,0,1,1},{0,0,0,0,0}};

    cout<<s.hasPath(m, {0,4}, {4,4});
    return 0;

}
