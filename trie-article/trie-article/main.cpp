#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <iterator>
#include <sstream>
#include <queue>
#include <iomanip>
#include<string>
//cs570 trie article23333
using namespace std;
const int nubofBreach = 256;

class Node {
public:
    int val;
    Node *next[nubofBreach];
    Node();
};
Node::Node() {
    for (int i = 0;i <= nubofBreach - 1;i++) {
        next[i] = nullptr;
    }
}
class countFun {
public:
    int hitNum;
    int countSame;
    int nubofn;
    countFun() ;
};
countFun::countFun()
{
    hitNum=0;
    countSame=0;
    nubofn=0;
}
class Trie {
public:
    Node *root;
    Node* put(Node* n, string str, int val, int level);
    Node* get(Node* n, string str, int level);
    unordered_map<string, int> wordNeednt;
    unordered_map<string, countFun> primary;
    unordered_map<string, string> synonym;
    vector<string> name;
    vector<vector<string>> companyName;
    int get(string str);
    int nubofword;
    int nubofother;
    int computeWord(string s);
    queue<string> keyofprefix(string p);
    queue<string> keytoprefix(string p, string primary);
    queue<string> getAllKeys();
    void constructCompanyTrie(string file);
    void parseTheArticle();
    void collect(Node* n,string pre,queue<string>* q);
    void put(string str, int val);
    bool isInTheArticle(vector<string> v, int start,string data);
    int theNumberOfWords(string s);
    vector<string> splitBySpace(string s);
    double theRelevance(int hit, int overlap, int theNum);
    Trie() {
        root = nullptr;
        wordNeednt["a"] = 0;
        wordNeednt["A"] = 0;
        wordNeednt["an"] = 0;
        wordNeednt["An"] = 0;
        wordNeednt["the"] = 0;
        wordNeednt["The"] = 0;
        wordNeednt["and"] = 0;
        wordNeednt["And"] = 0;
        wordNeednt["or"] = 0;
        wordNeednt["Or"] = 0;
        wordNeednt["but"] = 0;
        wordNeednt["But"] = 0;
        nubofother=0;
        nubofword=0;
    }
};
void Trie::put(string str, int val){
    root=put(root, str, val, 0);
}

Node* Trie::put(Node* n, string str, int val, int level){
    if (!n) n = new Node();
    if (level == str.size()) {
        n->val = val;
        return n;
    }
    char c=str[level];
    n->next[c]=put(n->next[c],str, val, level + 1);
    return n;
}

int Trie::get(string str){
    Node* node = get(root, str, 0);
    if(!node||node->val!=1) return 0;
    return node->val;
}

Node * Trie::get(Node * n, string str, int level){
    if (!n) return nullptr;
    if (level == str.size()) return n;
    char c = str[level];
    return get(n->next[c],str,level+1);
}

queue<string> Trie::getAllKeys(){
    return keyofprefix("");
}

void Trie::constructCompanyTrie(string file){
    ifstream infile(file); // for input file
    if (infile.fail()) {
        cout << "Input file \"" << file << "\" opening failed" << endl;
        return;
    }
    char symbol;
    string word= "";
    int flag = 0;
    vector<string> v;
    companyName.push_back(v);
    int changeline=0;
    string stemp="";
    while (getline(infile,stemp)) {
        if(stemp.size()<1)
            break;
        //cout<<stemp<<endl;
        for(int i=0;i<stemp.size();++i) {
            symbol=stemp[i];
            if (isalpha(symbol)||symbol == ' ') {
                word += symbol;
            } else if (symbol == '\t') {
                //cout<<word<<" ";
                companyName[flag].push_back(word);
                put(word, 1);
                word = "";
            }
        }
        companyName[flag].push_back(word);
        put(word, 1);
        word = "";
        flag++;
        vector<string> m;
        companyName.push_back(m);
        //cout<<"symbol "<<symbol<<endl;
    }
    infile.close();
    root->val = 0;
    for (int i = 0;i < companyName.size();i++) {
        if (companyName[i].size() != 0&&companyName[i][0]!="") {
            //cout << companyName[i][0]<<endl;
            name.push_back(companyName[i][0]);
            countFun c;
            primary[companyName[i][0]] = c;
            for (int l = 0;l < companyName[i].size();l++) {
                synonym[companyName[i][l]] = companyName[i][0];
                //cout<<"i="<<i<<"  l="<<l<<" "<<companyName[i][l]<<endl;
            }
        }
    }
}

void Trie::parseTheArticle(){
    cout << "Please input the article"<<endl;
    cout<<"(The input will end until you input a line that consists entirely of a period symbol (.) )" << endl;
    string all;
    string normalization;
    string input;
    vector<string> split;
    while (getline(cin , input)) {
        if(input.size()==1&&input[0]=='.')
            break;
        all += input+" ";
        string tem="";
        for (int i = 0;i < input.size();i++) {
            char symbol = input[i];
            if (isalpha(symbol)) {
                tem += symbol;
            }
        }
        split.push_back(tem);
        if (wordNeednt.count(tem)) {
            nubofother++;
            //cout<<nubofother<<endl;
        }
        normalization += tem+" ";
        // cout<<input<<"  finish"<<endl;
    }
    nubofword = split.size();
    //cout <<"nor  "<< normalization << endl;
    queue<string> temp;
    for (int h = 0;h < name.size();h++) {
        int f = 0;
        for (int m = 0;m < split.size();m+=f) {
            f = 0;
            string s = split[m];
            temp = keytoprefix(s, name[h]);
            if (temp.size() == 0) {
                f = 1;
                continue;
            }
            int mtemp=m;
            string stemp=s;
            while(mtemp<split.size()-1&&s.size()<temp.front().size())
            {
                mtemp++;
                s=s+" ";
                s=s+split[mtemp];
                if(s==temp.front())
                    break;
                if(s.size()>=temp.front().size()) {
                    f=1;
                    continue;
                }
            }
            unordered_map<string, countFun> map;
            for (int l = 0;l < name.size();l++) {
                countFun cf;
                map[name[l]] = cf;
                
            }
            while (temp.size() != 0) {
                string ss = temp.front();
                if (map[synonym[ss]].hitNum == 0 && isInTheArticle(split, m, ss)) {
                    map[synonym[ss]].hitNum = 1;
                    
                }
                
                if (map.count(synonym[ss])  && map[synonym[ss]].countSame < computeWord(ss) && isInTheArticle(split, m, ss)) {
                    map[synonym[ss]].countSame = computeWord(ss);
                    map[synonym[ss]].nubofn = theNumberOfWords(ss);
                }
                temp.pop();
            }
            f += map[name[h]].countSame;
            primary[name[h]].hitNum += map[name[h]].hitNum;
            primary[name[h]].countSame += map[name[h]].countSame;
            primary[name[h]].nubofn += map[name[h]].nubofn;
        }
        //cout<<"out loop h="<<h<<" size="<<name.size()<<endl;
        
    }
    
    
}

queue<string> Trie::keyofprefix(string p){
    queue<string> queue;
    Node* n = get(root, p, 0);
    collect(n,p,&queue);
    return queue;
}
queue<string> Trie::keytoprefix(string p, string primary) {
    queue<string> q = keyofprefix(p);
    queue<string> queue;
    while (q.size() != 0) {
        if (synonym[q.front()] == primary) {
            queue.push(q.front());
        }
        q.pop();
    }
    return queue;
}


void Trie::collect(Node * n, string pre, queue<string>* q){
    if (!n) return;
    if (n->val == 1) (*q).push(pre);
    char c = 0;
    for (int i = 0;i <= 255;i++) {
        collect(n->next[i], pre + c, q);
        c += 1;
    }
}


int Trie::computeWord(string s) {
    string buf;
    int length = 0;
    stringstream ss(s);
    while (ss >> buf) {
        length++;
    }
    return length;
}

bool Trie::isInTheArticle(vector<string> v, int start,string data){
    int length = computeWord(data);
    if (start + length-1 > v.size() - 1) return false;
    string end = "";
    for (int i = start;i < start + length;i++) {
        if (i != start + length - 1) {
            end += v[i] + " ";
        }
        else {
            end += v[i];
        }
        
    }
    
    return end==data;
}

int Trie::theNumberOfWords(string s){
    int number = 0;
    vector<string> v=splitBySpace(s);
    for (string str : v) {
        if (wordNeednt.count(str)) {
            number++;
        }
    }
    return number;
}

vector<string> Trie::splitBySpace(string s){
    string buf;
    stringstream ss(s);
    vector<string> tokens;  // vector
    while (ss >> buf) {
        tokens.push_back(buf);
    }
    return tokens;
    
}

double Trie::theRelevance(int hit, int overlap, int theNum){
    
    return (double)hit/(nubofword-overlap+hit-nubofother+theNum);
}
void show(Trie t)
{
    int allhit=0;
    float allpre=0;
    cout<<endl;
    cout<<"Company                         Hit Count        Relevance"<<endl;
    cout<<"----------------------------------------------------------"<<endl;
    for (int i = 0;i < t.name.size();i++) {
        allhit+=t.primary[t.name[i]].hitNum;
        allpre+= t.theRelevance(t.primary[t.name[i]].hitNum, t.primary[t.name[i]].countSame,
                                t.primary[t.name[i]].nubofn);
        cout << left<<setw(32)<<t.name[i];
        cout<<left<<setw(16)<<t.primary[t.name[i]].hitNum;
        cout<<right<<setw(8)<< t.theRelevance(t.primary[t.name[i]].hitNum, t.primary[t.name[i]].countSame,
                                              t.primary[t.name[i]].nubofn)*100;
        cout<<"%"<< endl;
    }
    cout<<"----------------------------------------------------------"<<endl;
    cout<<"   ";
    cout << left<<setw(29)<<"Total";
    cout<<left<<setw(16)<<allhit;
    cout<<right<<setw(8)<<allpre*100;
    cout<<"%"<<endl;
    cout<<"----------------------------------------------------------"<<endl;
    cout<<"   ";
    cout << left<<setw(37)<<"Total Words";
    cout<<left<<setw(13)<<t.nubofword-t.nubofother;
    
    cout <<endl<< left<<setw(37)<<"Other Words";
    cout<<left<<setw(13)<<t.nubofother;
    //cout<<endl<<t.nubofword<<" "<<t.nubofother<<endl;
}
void show2(Trie t)// I write two show function, that can show the relevance with different rule.
{
    float allhit=0;
    cout<<endl;
    cout<<"Company                         Hit Count        Relevance"<<endl;
    cout<<"----------------------------------------------------------"<<endl;
    for (int i = 0;i < t.name.size();i++) {
        allhit+=t.primary[t.name[i]].hitNum;
        cout << left<<setw(32)<<t.name[i];
        cout<<left<<setw(16)<<t.primary[t.name[i]].hitNum;
        cout<<right<<setw(8)<<(float)t.primary[t.name[i]].hitNum/(t.nubofword-t.nubofother)*100;
        cout<<"%"<< endl;
    }
    cout<<"----------------------------------------------------------"<<endl;
    cout<<"   ";
    cout << left<<setw(29)<<"Total";
    cout<<left<<setw(16)<<(int)allhit;
    cout<<right<<setw(8)<<allhit/(t.nubofword-t.nubofother)*100;
    cout<<"%"<<endl;
    cout<<"----------------------------------------------------------"<<endl;
    cout<<"   ";
    cout << left<<setw(37)<<"Total Words";
    cout<<left<<setw(13)<<t.nubofword-t.nubofother;
    //cout<<endl<<t.nubofword<<" "<<t.nubofother<<endl;
}
int main() {
    Trie t;
    //t.constructCompanyTrie("/Users/weizhengkai/Desktop/companies3.dat");
    t.constructCompanyTrie("/Users/Leigh/Downloads/main-4/companies.dat");
    t.parseTheArticle();
    queue<string> end = t.getAllKeys();
    show(t);
    cout<<endl;
    //show2(t);// I write two show function, that can show the relevance data with different rule.
    return 0;
}
