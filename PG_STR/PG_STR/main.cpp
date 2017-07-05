#include <iostream>
#include <vector>
#include <stack>
#include <map>

using namespace std;

struct Action {
    int index, len;
    map<int, char> setchar;
    Action(): index(0), len(0) {}
    Action(int i, int l): index(i), len(l) {}
};

struct TreeNode {
    char * str;
    int start, len; // base on the parent
    TreeNode* parent;
    Action actions;
    
    TreeNode(string & input) : str(&input[0]), start(0), len(input.size()), parent(NULL) {
        actions.len = len;
    }
    TreeNode(char* s, int start_, int len_, TreeNode* p) : str(s), start(start_), len(len_), parent(p), actions(start_, len_){
       
    }
};

class MutableString {
private:
    TreeNode* node;
public:
    //MutableString(string & input) : node(new TreeNode(input)){}
    MutableString(const string input) {
        string s = input;
        node = new TreeNode(s);
    }
    
    MutableString(TreeNode* in) : node(in){}
    MutableString() : node( NULL) {}
    //MutableString(MutableString& other){ node = other.node;}
    //MutableString(MutableString&& other){ node = other.node; other.node = nullptr; }
    friend ostream& operator<<(ostream& o, const MutableString& mstring) {
        stack<Action> As;
        TreeNode* temp = mstring.node;
        As.push(temp -> actions);
        
        while(temp -> parent) {
            temp = temp -> parent;
            As.push(temp -> actions);
        }
        
        Action overall;
        while(As.size()) {
            auto Action = As.top(); As.pop();
            overall.index += Action.index;
            overall.len = Action.len;
            
            //  3, c   4 x  5 d
            for(auto set : Action.setchar){
                overall.setchar.emplace(overall.index + set.first, set.second);
            }
        }
        for(int i = 0; i < overall.len; i++){
            if(overall.setchar.count(i + overall.index)){
                o<<overall.setchar[i + overall.index];
            }else {
                o<<temp -> str[i + overall.index];
            }
        }
        return o;
    }
    
    
    MutableString substr(int index, int len) {
        MutableString m;
       
        m.node = new TreeNode(node -> str, node -> start + index, len, node);
        return m;
    }
};

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    string input = "abcdef";
    MutableString str1 ("abcdef");
    cout<<str1<<endl;
    MutableString str2 = str1.substr(2,4);
    cout<<str2;
    
    
    return 0;
}
