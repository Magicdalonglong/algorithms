//

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class Solution {
private:
    struct Node{
        bool f;
        vector<Node*> next;
        Node(){
            f = false;
            next.assign(26,NULL);
        }
    };
    Node* root;
    void init(vector<string>& words){
        root = new Node();
        for(auto& w : words){
            Node* temp = root;
            for(auto c : w){
                if(temp -> next[c - 97] == NULL)
                    temp -> next[c - 97] = new Node();
                temp = temp -> next[c - 97];
            }
            temp -> f = 1;
        }
    }
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        if(board.empty()) return {};
        int m = board.size(), n = board[0].size();
        init(words);
        vector<string> res;
        for(int i = 0; i < m; i++)
            for(int j = 0; j < n; j++)
            {
                Node* temp = root;
                string str;
                while((temp = temp -> next[board[i][j] - 97]))
                    str.push_back(board[i][j]);
                if(temp -> f) res.emplace_back(str);
            }
        return res;
    }
};
int man(int arg){

    cout<<"Hey \n";
    return 0;
}