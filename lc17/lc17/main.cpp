
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <fstream>
#include <stdlib.h>
using namespace std;


class Solution {
    string dict(int n){
        switch (n){
            case 2:return "abc";
            case 3:return "def";
            case 4:return "ghi";
            case 5:return "jkl";
            case 6:return "mno";
            case 7:return "pqrs";
            case 8:return "tuv";
            case 9:return "wxyz";
            default: return "";
        }
    }
public:
    vector<string> letterCombinations(string digits) {
        if(digits.empty())return {};
        vector<string> res = {""};
        for(auto d:digits){
            string btn = dict(d-48);
            int lenr = res.size();
            int len = btn.size();
            cout<<"before expand:";
            for(auto& r:res)cout<<r<<",";
            cout<<endl;
            for(int i =0;i<len-1;i++)
            {
                res.insert(res.end(),res.begin(),res.begin()+lenr);
            }
            cout<<"after expand: ";
            for(auto& r:res) cout<<r<<',';
            cout<<endl;            for(int i=0;i<res.size();i++){
                for(int p = 1;p<=len;p++)
                {
                    if(i<p*lenr&&i>=(p-1)*lenr){
                        res[i].push_back(btn[p-1]);break;
                    }
                }
            }
        }
        return res;
    }
};
int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    Solution s;
    auto res = s.letterCombinations("2234");
    cout<<endl;
    vector<string> ans = {"aadg","aadh","aadi","aaeg","aaeh","aaei","aafg","aafh","aafi","abdg","abdh","abdi","abeg","abeh","abei","abfg","abfh","abfi","acdg","acdh","acdi","aceg","aceh","acei","acfg","acfh","acfi","badg","badh","badi","baeg","baeh","baei","bafg","bafh","bafi","bbdg","bbdh","bbdi","bbeg","bbeh","bbei","bbfg","bbfh","bbfi","bcdg","bcdh","bcdi","bceg","bceh","bcei","bcfg","bcfh","bcfi","cadg","cadh","cadi","caeg","caeh","caei","cafg","cafh","cafi","cbdg","cbdh","cbdi","cbeg","cbeh","cbei","cbfg","cbfh","cbfi","ccdg","ccdh","ccdi","cceg","cceh","ccei","ccfg","ccfh","ccfi"};
    cout<<ans.size()<<endl;
    cout<<res.size();
    
    unordered_set<string> set;
    for(auto a:ans)
        set.insert(a);
    int m = 0;
    for(auto a:res)
        if(set.count(a))m++;
    cout<<"m is "<<m;
    
    

    
    return 0;
    
}
