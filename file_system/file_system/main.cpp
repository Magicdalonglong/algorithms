#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

class FileSystem {
    struct Node {
        string name, content;
        bool isdir;
        unordered_map<string, Node*> sub;
        Node(string n) : name(n), isdir(true) {}
    };
    Node* root;
    vector<string> split(const string &s, char delim) {
        vector<string> elems;
        stringstream ss(s);
        string item;
        while (getline(ss, item, delim)) {
            elems.push_back(item);
        }
        return elems;
    }
    Node* GotoNode(string& path) {
        Node* cur = root;
        vector<string> path_ = split(path, '/');
        for(auto p : path_) {
            if(cur -> sub[p] == NULL) {
                return NULL;
            }
            cur = cur -> sub[p];
        }
        return cur;
    }
public:
    FileSystem() {
        root = new Node("/");
    }
    vector<string> ls(string path) {
        Node* cur = GotoNode(path);
        vector<string> res;
        if(cur == NULL) {
            return res;
        }else if(cur -> isdir) {
            for(auto d : cur -> sub) {
                res.emplace_back(d.first);
            }
        }else {
            res.emplace_back(cur -> name);
        }
        return res;
    }
    void mkdir(string path) {
        vector<string> path_ = split(path, '/');
        Node* cur = root;
        for(auto p : path_) {
            if(cur -> sub[p] == NULL) {
                cur -> sub[p] = new Node(p);
            }
            cur = cur -> sub[p];
        }
    }
    
    void addContentToFile(string filePath, string content) {
        mkdir(filePath);
        Node* cur = GotoNode(filePath);
        cur -> isdir = false;
        cur -> content = content;
    }
    
    string readContentFromFile(string filePath) {
        
        return GotoNode(filePath) -> content;
    }
};

struct node {
    int a;
    int cal() {
        return a * a;
    }
};
int main(int argc, char* argv[]) {
    FileSystem fs;
    
    // should print ""
    auto res = fs.ls("/");
    for(auto l : res) cout<<l<<",";
    cout<<endl;
    fs.mkdir("/a/b/c");
    fs.addContentToFile("/a/b/c/d", "hello world");
    
    // should print a
    auto res2 = fs.ls("/");
    for(auto l : res2) cout<<l<<",";
    cout<<endl;
    // should print d
    auto res3 = fs.ls("/a/b/c");
    for(auto l : res3) cout<<l<<",";
    cout<<endl;
    // should print d
    auto res4 = fs.ls("/a/b/c/d");
    for(auto l : res4) cout<<l<<",";
    cout<<endl;
    // should print hello world
    cout << fs.readContentFromFile("/a/b/c/d") << endl;
    node a;
    a.a = 12;
    cout<< a.cal();
}
/**
 * Your FileSystem object will be instantiated and called as such:
 * FileSystem obj = new FileSystem();
 * vector<string> param_1 = obj.ls(path);
 * obj.mkdir(path);
 * obj.addContentToFile(filePath,content);
 * string param_4 = obj.readContentFromFile(filePath);
 */

