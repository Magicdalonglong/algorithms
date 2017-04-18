//

#include <iostream>
#include <list>
#include <queue>
#include <unordered_map>
#include <vector>
#include <cmath>
#include <iterator>

using namespace std;
int helper(string& s, int i, int j, char key);
int nextGreaterElement(int n) {
    string s = to_string(n);
    int i;
    for(i = s.size() - 1; i > 0 && s[i] < s[i - 1]; i--);
    if(i == 0) return -1;
    int bigger = helper(s, i, s.size() - 1, s[i - 1]);
    swap(s[i - 1], s[bigger]);
    sort(s.begin() + 1, s.end());
    return stoi(s);
}
int helper(string& s, int i, int j, char key){
    while(i <= j){
        int mid = i + (j - i) / 2;
        if(s[mid] <= key) j = mid - 1;
        else i = mid + 1;
    }
    return j;
}
int func(vector<int>& n, int k){
    vector<int> map;
    int sum = 0, res = 0;
    for(int i = 0; i < n.size(); i++)
    {
        sum += n[i];
        if(sum <= k) res = i + 1;
        else{
            auto it = lower_bound(map.begin(), map.end(), sum - k);
            res = max(res, i - int(it - map.begin()) );
        }
        map.push_back(sum);
    }
    return res;
    
}



void add(string& ans, string temp, int offset){
    int carry = 0;
    for(int i = 0; i < temp.size(); i++){
        int index = ans.size() - i - offset - 1;
        int sum = (temp[temp.size() - i - 1] - 48) + (index >= 0 ? ans[index] - 48 : 0) + carry;
        if(index >= 0) ans[index] = sum % 10 + 48;
        else ans.insert(ans.begin(), 1, sum % 10 + 48);
        carry = sum / 10;
    }
}
string mul(string a, char digit, string* res){
    if(res[digit - 48].size()) return res[digit - 48];
    int len = a.size(), carry = 0;
    for(int i = len - 1; i >= 0; i--)
    {
        int sum = (digit - 48) * (a[i] - 48) + carry;
        a[i] = (sum % 10 + 48);
    }
    if(carry) a.insert(a.begin(), 1, carry + 48);
    res[digit - 48] = a;
    return a;
}
string multiple(string a, string b){
    if(a.empty() || b.empty()) return "";
    if(a.size() < b.size()) swap(a, b);
    string ans;
    bool neg = (a[0] == '-' ^ b[0] == '-');
    string mem[10];
    int len1 = a.size();
    int len = b.size();
    for(int i = 0; i < len; i++)
    {
        string temp = mul(a, b[len - i - 1], mem);
        add(ans, temp, i);
    }
    return ans;
}
/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache obj = new LFUCache(capacity);
 * int param_1 = obj.get(key);
 * obj.put(key,value);
 */
int main(){
    cout<<"hell0 \n";
    string a = "12312";
    string b = "12312";
    string res = multiple(a, b);
    cout<<res<<endl;
    list<int> data;
    data.push_back(123);
    cout<<"typeof end "<<typeid(data.end()).name();
    cout<<"\ntypeof rbegin "<<typeid(data.rbegin()).name();
    
    // }
    
    return 0;
}
