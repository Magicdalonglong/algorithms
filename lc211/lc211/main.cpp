//
//  main.cpp
//  lc211
//
//  Created by Lei Duan on 2/25/17.
//  Copyright © 2017 Lei Duan. All rights reserved.
//

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class WordDictionary2 {
    struct Trie{
        bool f;
        vector<Trie*> next;
        Trie():f(false){next.assign(26,NULL);}
    };
    Trie* root;
    vector<string> dict;
public:
    /** Initialize your data structure here. */
    WordDictionary2() {
        root = new Trie();
    }
    
    /** Adds a word into the data structure. */
    void addWord(string word) {
        dict.emplace_back(word);

        Trie* r = root;
        for(auto c:word){
            if(!r->next[c-97])
                r->next[c-97] = new Trie();
            r = r->next[c-97];
        }
        r->f = true;
    }
    
    /** Returns if the word is in the data structure. A word could contain the dot character '.' to represent any one letter. */
    bool search(string word) {
        cout<<"\n current dict: [";
        for(auto d:dict) cout<<d<<" ";
        cout<<"] search word: "<<word<<" :";

        Trie* r = root;
        return helper(word,r,0);
    }
    bool helper(string& word,Trie* r, int index){
        if(!r)return 0;
        if(index == word.size()){
            cout<<"in final r->f is "<<r->f;
            return r->f;
        }
        
        if(word[index] == '.') {
            for(int i=0;i<26;i++){
                if(helper(word,r->next[index],index+1))return 1;
            }
            return 0;
        }
        else if (r->next[word[index]-97])
            return helper(word,r->next[word[index]-97],index+1);
        
        return 0;
        
        
        
    }
};

/**
 * Your WordDictionary object will be instantiated and called as such:
 * WordDictionary obj = new WordDictionary();
 * obj.addWord(word);
 * bool param_2 = obj.search(word);
 */

class WordDictionary {
    
    struct trie{
       
        
        bool flag;
        vector<trie*> next;
        trie(){flag=false;next.assign(26,NULL);}
        
    };
    trie * root;
    
    vector<string> dict;
public:
    /** Initialize your data structure here. */
    WordDictionary() {
        root = new trie();
    }
    
    /** Adds a word into the data structure. */
    void addWord(string word) {
        dict.emplace_back(word);
        trie* r = root;
        for(auto c: word){
            if(!r->next[c-97])
                r->next[c-97] = new trie();
            r = r->next[c-97];
        }
        r -> flag = true;
    }
    
    /** Returns if the word is in the data structure. A word could contain the dot character '.' to represent any one letter. */
    bool search(string word) {
        cout<<"\n current dict: [";
        for(auto d:dict) cout<<d<<" ";
        cout<<"] search word: "<<word<<" :";
        if(!root)return 0;
        queue<pair<trie*,int>> q;  //node, index of word
        q.push(make_pair(root,0));
        
        while(!q.empty()){
            trie *cur = q.front().first;
            int index = q.front().second;
            q.pop();
            if(!cur)continue;
            if(index == word.size()){
                if(cur->flag == true){
                    cout<<" true;";
                    return true;
                }
                continue;
            }
            if(word[index] == '.')
            {
                for(int i=0;i<26;i++)
                    q.push(make_pair(cur->next[i],index+1));
            }else{
                if(cur->next[word[index]-97])
                    q.push(make_pair(cur->next[word[index]-97],index+1));
                else {
                    cout<<" (l) false";
                    
                    return 0;
                }
            }
        }
        cout<<"(f) false";
        
        return 0;
        
    }
};

/**
 * Your WordDictionary object will be instantiated and called as such:
 * WordDictionary obj = new WordDictionary();
 * obj.addWord(word);
 * bool param_2 = obj.search(word);
 */
int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
//    
//    WordDictionary s;
//    s.addWord("at");
//    s.addWord("and");
//    s.addWord("an");
//    s.addWord("add");
//    cout<<s.search("a");
//    cout<<s.search(".at");
//    s.addWord("bat");
//    cout<<s.search(".at");
//    cout<<s.search("an.");
//    cout<<s.search("a.d.");
//    cout<<s.search("b.");
//    cout<<s.search("a.d");
//    cout<<s.search(".");
    
    
    
    WordDictionary2 s2;
    s2.addWord("at");
    s2.addWord("and");
    s2.addWord("an");
    s2.addWord("add");
    cout<<s2.search("a");
    cout<<s2.search(".at");
    s2.addWord("bat");
    cout<<s2.search(".at");
    cout<<s2.search("an.");
    cout<<s2.search("a.d.");
    cout<<s2.search("b.");
    cout<<s2.search("a.d");
    cout<<s2.search(".");


    return 0;
}






}



