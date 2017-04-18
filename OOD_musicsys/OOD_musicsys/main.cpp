//
//  main.cpp
//  OOD_musicsys
//
//  Created by Lei Duan on 4/3/17.
//  Copyright © 2017 Lei Duan. All rights reserved.
//

#include <vector>
#include <iostream>
#include <stack>
#include <unordered_map>
#include <iostream>
using namespace std;

class Song {
public:
    Song(string n) : name(n){}
    Song(){}
    string name;
    string info;
};


class MusicSystem {
private:
    stack<Song> stk;
    vector<Song> list;
    int index;
public:
    MusicSystem(vector<Song> list_): list(list_){};
    MusicSystem(){
        srand((unsigned)time(NULL));
    }
    void shuffle(){
        int len = list.size();
        for(int i = 0; i < len; ++i)
            swap(list[i], list[i + rand()%(len - i)]);
        
    }
    Song previousSong(){
        Song res;
        if(stk.size()){
            res = stk.top();
            stk.pop();
        }else res = nextSong();
        return res;
    }
    Song nextSong(){
        if(stk.empty()) reset();
        stk.push(list[index]);
        return list[index++];
    }
    void add(Song s){
        list.emplace_back(s);
    }
    void reset(){
        while(stk.size())
            stk.pop();
        shuffle();
        index = 0;
    }
    
};
class User {
public:
    MusicSystem *sys = NULL;
    string name;
    void opensys(){
        sys = new MusicSystem();
    }
    Song nextSong(){
        return sys -> nextSong();
    }
    Song previousSong(){
        return sys -> previousSong();
    }
    void addSong(Song s){
        sys -> add(s);
    }
};


int main(int argc, const char * argv[]) {
    // insert code here...
    User u;
    vector<Song> s;
    s.emplace_back("Hello1");    s.emplace_back("Hello9");
    s.emplace_back("Hello2");
    s.emplace_back("Hello3");
    s.emplace_back("Hello4");
    s.emplace_back("Hello5");
    s.emplace_back("Hello6");
    s.emplace_back("Hello7");
    s.emplace_back("Hello8");
    u.opensys();
    for(auto song : s)
        u.addSong(song);
    cout<<u.nextSong().name<<endl;
    cout<<u.nextSong().name<<endl;
    cout<<u.nextSong().name<<endl;
    cout<<u.nextSong().name<<endl;
    cout<<u.nextSong().name<<endl;
    cout<<"\npres: \n";
    cout<<u.previousSong().name<<endl;
    cout<<u.previousSong().name<<endl;
    cout<<u.previousSong().name<<endl;
    cout<<u.previousSong().name<<endl;
    cout<<u.previousSong().name<<endl;
    cout<<u.previousSong().name<<endl;
    cout<<u.previousSong().name<<endl;
    cout<<u.previousSong().name<<endl;
    cout<<u.previousSong().name<<endl;
    
    
    std::cout << "\nHello, World!\n";
    return 0;
}
