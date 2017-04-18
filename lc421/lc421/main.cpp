//

#include <iostream>
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
            if(it != map.end()){
                res = max(res, i - distance(map.begin() - it));
            }
        }
        map.push_back(sum);
    }
    return res;
    
}
int main(){
    vector<int> n = {21,4,5,3,4,8,4,5,6};
    func(n, 12);
    
    cout<<"Hey \n";
    return 0;
}
