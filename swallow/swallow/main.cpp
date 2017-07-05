
#include <iostream>
#include <fstream>
#include <set>
#include <string>
#include <vector>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

class Trie {
private:
    struct TrieNode {
        TrieNode* Next[127] = {0};
        bool flag = false;
    };
    TrieNode* root;
public:
    Trie() {
        root = new TrieNode();
    }
    
    // Inserts a word into the trie.
    void add(string word) {
        
        TrieNode* temp = root;
        for(auto c:word){
            if(temp -> Next[c] == NULL)
                
                temp -> Next[c] = new TrieNode();
            temp = temp -> Next[c];
        }
        temp->flag = true;
        
    }
    
    // Returns if the word is in the trie.
    bool contains(string word) {
        TrieNode* temp = root;
        for(int i = 0;i<word.length();i++){
            if(temp->Next[word[i]] == NULL)
                return false;
            else
                temp = temp->Next[word[i]];
        }
        return temp->flag;
    }
    
    // Returns if there is any word in the trie
    // that starts with the given prefix.
    bool containsPrefix(string prefix) {
        TrieNode* temp = root;
        for(int i = 0;i<prefix.length();i++){
            if(temp->Next[prefix[i]] == NULL)
                return false;
            else
                temp = temp->Next[prefix[i]];
        }
        return true;
    }
};
void Bfs_Backtracking(vector<vector<char>>& matrix, int i, int j, string& temp, set<string>& res, Trie *t,vector<bool>& hash){
    int m = matrix.size(), n = matrix[0].size();
    hash[i * n + j] = 1;
    temp.push_back(matrix[i][j]);
    if(t -> containsPrefix(temp)){
        if(t -> contains(temp) && temp.size() >=  3) res.emplace(temp);
        pair<int, int> step[8] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0} ,
            {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};
        
        for(auto s : step){
            int x = i + s.first, y = j + s.second;
            if(x < 0 || x >=  m || y < 0 || y >=  n || hash[x * n + y]) continue;
            Bfs_Backtracking(matrix, x, y, temp, res, t, hash);
        }
    }
    hash[i * n + j] = 0;
    temp.pop_back();
}
set<string> Boggle(vector<vector<char>>& matrix, Trie* t){
    if(matrix.empty()) return {};
    set<string> res;
    int m = matrix.size(), n = matrix[0].size();
    vector<bool> hash(m * m, 0);
   
    for(int i = 0; i < m; i++)
        for(int j = 0; j < n; j++){
            string temp;
            Bfs_Backtracking(matrix, i, j, temp, res, t, hash);
        }
    
    return res;
}
int main(int argc, const char * argv[]) {
    
    string path = getcwd(NULL, 0); // Platform-dependent, see reference link below
    Trie t;
    ifstream dictfile;
    dictfile.open("dictionary.txt");
    int count = 0;
    string line;
    if (dictfile.is_open())
    {
        while ( getline (dictfile,line) )
        {
            t.add(line);
            count ++;
        }
        dictfile.close();
    }
    
    else {
        cout << "Unable to open dict file, check the path!!";
        cout<<"Current work dir: \n"<<path<<endl;
        exit(1);
    }
    cout<<"Complete loading dict!! "<<count<<" words loaded"<<endl<<endl;
    ifstream bogglefile;
    
    bogglefile.open("boggle.dat");
    vector<vector<char>> matrix;
    int len = -1, row = 0;
    if (bogglefile.is_open())
    {
        while ( getline (bogglefile,line) )
        {
            if(len == -1){
                len = stoi(line);
                matrix.assign(len, vector<char>(len));
            }else{
                for(int i = 0; i <len; i++)
                    matrix[row][i] = line[i * 2];
                row++;
            }
        }
        bogglefile.close();
    }
    else {
        cout << "\nUnable to open hw5 file, check the path!!";
        cout<<"Current work dir: \n"<<path<<endl;
        exit(1);
    }
    cout<<"Complete loading boggle!! "<<"Matrix: "<<endl<<endl;
    for(auto r : matrix){
        for(auto c : r) cout<<c<<" ";
        cout<<endl;
    }
    
    /*** 
     i am using set as result type instead of hash set
     in order to make the result easier for human to check
    ***/
    
    /*** 
     there are at least one mistake in the sample test file in
     https://drive.google.com/file/d/0Bwxfq4Y7f7vkYndOUlNkT0xEeUU/view?usp=sharing
     the word "tines" does not exist in the dictionary.txt.
     ***/

    auto res = Boggle(matrix, &t);
    cout<<"\nresult of calling Boggle(): \n";
    cout<<"size of result : "<<res.size()<<endl;
    for(auto r : res)cout<<r<<" ";
    
    cout<<endl;
    return 0;
}
