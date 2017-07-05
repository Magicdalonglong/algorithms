//
//  bfs.cpp
//  Pg_Maze
//
//  Created by Lei Duan on 6/11/17.
//  Copyright © 2017 Lei Duan. All rights reserved.
//

#include "bfs.hpp"

//using namespace std;
//using maze_line = std::vector<char>;
//using maze      = std::vector< maze_line >;
//using position  = std::pair<int, int>;
//using item_map  = std::unordered_map< char , std::vector< position > >;
//
//
////globals
//static const position NULLE(-1,-1); //mark the end of a level on BFS
//static item_map door_map; //save doors positions
//static item_map key_map; //save keys positions
//
//int flood[4][2] = {
//    {-1,+0},
//    {+1,+0},
//    {+0,-1},
//    {+0,+1}
//};
//
//int DFS(maze &m , position &initial, position &final){
//    std::unordered_map< int, std::unordered_map<int, bool> > visited_position;
//    
//    std::queue<position> qp;
//    qp.push(initial);
//    qp.push(NULLE);
//    
//    int path_size_counter = 0;
//    int path_size_current = std::numeric_limits<int>::max();
//    int path_size_recur   = std::numeric_limits<int>::max(); //best path size in case of recursion
//    
//    while (!qp.empty()) {
//        position p = qp.front();
//        qp.pop();
//        
//        if(p == NULLE){
//            ++path_size_counter;
//            if(!qp.empty())
//            qp.push(NULLE);
//            continue;
//        }
//        
//        //invalid position
//        if(!(0 <= p.first && p.first < m.size() && 0 <= p.second && p.second < m[0].size())){
//            continue;
//        }
//        
//        if(visited_position[p.first][p.second] == true){
//            continue;
//        }
//        
//        if(p == final){
//            path_size_current = path_size_counter;
//            break;
//        }
//        
//        //its not a free path
//        if(m[p.first][p.second] != '.'){
//            //its a key
//            if('a' <= m[p.first][p.second] && m[p.first][p.second] <= 'g'){
//                maze copy (m);
//                
//                char key = m[p.first][p.second];
//                
//                //get the door that matches the key found
//                char door = std::toupper(key);
//                
//                //open all the doors mateched on the copy maze
//                std::vector<position> &posisd = door_map[door];
//                for (auto &pos_door : posisd) {
//                    copy[pos_door.first][pos_door.second] = '.';
//                }
//                
//                //erase this key from the copy maze
//                std::vector<position> &posisk = key_map[key];
//                for (auto &pos_key : posisk) {
//                    copy[pos_key.first][pos_key.second] = '.';
//                }
//                
//                //get minimum path for a recursion
//                int aux = DFS(copy,p,final);
//                if(aux != std::numeric_limits<int>::max())
//                path_size_recur = std::min(path_size_recur,path_size_counter + aux); //the path to the key + the path from key to exit
//                
//            }
//            else
//            continue;
//        }
//        
//        //here only keys and '.'
//        visited_position[p.first][p.second] = true;
//        
//        for (int i = 0; i < 4; ++i) {
//            int x = p.first  + flood[i][0];
//            int y = p.second + flood[i][1];
//            
//            position new_pos(x,y);
//            qp.push(new_pos);
//        }
//        
//    }
//    
//    return std::min(path_size_current, path_size_recur);
//}
//
//int helper(void){
//    maze     m ;
//    position initial;
//    position final;
//    
//    char ch;
//    for (int i = 0; (ch = getchar_unlocked()) != EOF ; ++i) {
//        maze_line l;
//        
//        for (int j = 0; ch != '\n'; ++j){
//            
//            if('A' <= ch && ch <= 'G'){ //it's a door
//                door_map[ch].push_back(std::make_pair(i, j));
//            }
//            
//            else if ('a' <= ch && ch <= 'g'){
//                key_map[ch].push_back(std::make_pair(i, j));
//            }
//            
//            else if(ch == '@'){
//                initial = std::make_pair(i, j);
//                ch = '.';
//            }
//            
//            else if(ch == '*'){
//                final = std::make_pair(i, j);
//            }
//            
//            l.push_back(ch);
//            ch = getchar_unlocked();
//        }
//        
//        m.push_back(l);
//    }
//    
//    int dfs = DFS(m, initial, final);
//    if(dfs == std::numeric_limits<int>::max())
//    puts("--");
//    else
//    printf("%d\n",dfs);
//}
