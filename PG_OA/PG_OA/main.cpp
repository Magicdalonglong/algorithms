/**
 Write your solution in this file.
 
 You can build, execute, and test your answer either by pressing 'Try Answer' in
 the side panel, or by running the following commands on the command line:
 
 To build your answer:
 make
 To run the previously built executable:
 ./answer <test_case_path>
 For example:
 ./answer tests/input_1.json
 
 You can organize your code as you wish (eg, use auxiliary files) as long as
 the binary `answer` produces the expected output.
 **/

#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>
#include <set>
#include <vector>
#include <unistd.h>
#include "answer.h"

using namespace std;

/**
 * Using Trie to store words from the dictionary,
 * check if a path can form a word during the 
 * dfs traverse upon the boggle_board
 */
struct TrieNode {
    vector<TrieNode*> next;
    bool flag;
    TrieNode() : flag(false) {next.assign(26, NULL); }
};

void dfs_helper(vector<string>& boggle_board, int i, int j, string& temp, set<string>& res, TrieNode *cur){
    int m = int(boggle_board.size()), n = int(boggle_board[0].size());
    if(cur -> next[boggle_board[i][j] - 97] == NULL) return;
    cur = cur -> next[boggle_board[i][j] - 97];
    
    temp.push_back(boggle_board[i][j]);
    if(cur -> flag) res.emplace(temp);
    
    pair<int, int> step[9] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}, {0, 0}};
    for(auto s : step){
        int x = i + s.first, y = j + s.second;
        if(x < 0 || x >=  m || y < 0 || y >=  n) continue;
        dfs_helper(boggle_board, x, y, temp, res, cur);
    }
    temp.pop_back();
}


/**
 * Implement your solution here.
 *
 * @param boggle_board Representation of a boggle board.
 * @param list_path Path to a .txt file containing the list of valid words to consider
 * @return List of valid words found in the given boggle board.
 */
std::vector<std::string> find_words(std::vector<std::string> boggle_board, std::string list_path)
{
    if(boggle_board.empty()) return {};
    int m = int(boggle_board.size()), n = int(boggle_board[0].size());
    TrieNode* root = new TrieNode;
    string path = getcwd(NULL, 0)/* Platform-dependent */, line;
    
    /***
     * Read from file to build the Trie
     */
    ifstream dictfile;
    dictfile.open(list_path);
    if (dictfile.is_open())
    {
        while(getline(dictfile, line))
        {
            TrieNode* temp = root;
            for(auto c : line){
                if(temp -> next[c - 97] == NULL){
                    temp -> next[c - 97] = new TrieNode();
                }
                temp = temp -> next[c - 97];
            }
            temp->flag = true;
        }
        dictfile.close();
    } else {
        cout << "Unable to open dict file, check the path!!";
        cout<<"Current work dir: \n"<<path<<endl;
        exit(1);
    }
    
    set<string> res;
    string temp;
    
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            dfs_helper(boggle_board, i, j, temp, res, root);
        }
    }
    std::vector<std::string> output(res.begin(), res.end());
    return output;
}
