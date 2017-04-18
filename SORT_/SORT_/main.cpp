//

#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <unordered_map>
#include <vector>
#include <cmath>
#include <iterator>

using namespace std;

// 2 0 0 0 2 2 2 2 0

bool onside(int n, pair<int, int> A){
    return A.first == 0 || A.first == n - 1 || A.second == 0 || A.second == n - 1;
}
int position(int n, pair<int, int> A){
    int res;
    if(A.first < 0 || A.first >= n || A.second < 0 || A.second >= n) return -1;
    if(A.first == 0) res = A.second;
    else if(A.second == n - 1) res = n - 1+ A.first;
    else if(A.first == n - 1) res = n * 2 - 3 + n - A.second;
    else if(A.second == 0) res = n * 3 - 4 + n - A.first;
    else return n * 4 - 4;
    return res;
}
bool has_non_intersecting_path(int n, pair<int, int> A, pair<int, int> B, pair<int, int> P, pair<int,int> Q) {
    n++;
    int point[4];
    vector<bool> set(n * 4 - 3, 0);
    if((point[0] = position(n, A)) == -1) return false;
    if((point[1] = position(n, B)) == -1) return false;
    if((point[2] = position(n, P)) == -1) return false;
    if((point[3] = position(n, Q)) == -1) return false;
    for(int i = 0; i < 4; i++)
    {
        if(set[point[i]]) return false; // overlop
        set[point[i]] = 1;
    }
    if(set[n * 4 - 4]) return true;
    
    if(point[0] > point[1]) swap(point[0], point[1]);
    if((point[2] > point[0] && point[2] < point[1]) ^ (point[3] > point[0] && point[3] < point[1])) return false;
    else return true;
    
}

int get_second_most_freq(vector<int>& the_list) {
    unordered_map<int, int> mp;
    for(auto i: the_list){
        mp[i]++;
    }
    int max1 = 0, max2 = 0;
    int res = 0;
    for(auto m : mp){
        if(m.second > max1) max1 = m.second;
        else if(m.second > max2) {
            max2 = m.second;
            res =  m.first;
        }
    }
    return res;
}


void asa(int n){
    for(int i = 0; i < n; i++){
        for(int j = 0 ; j < n ; j++)
        {
            if(j >= i){
                cout<<(n + n - i + 1) * i / 2 + j - i;
            }
            else cout<<"X";
        }
        cout<<endl;
    }
}
int main()
{
    
    // vector<int> nums = {1,2,2,3,3,3,43,43,43,43,43};
    // auto res = get_second_most_freq(nums);
    // cout<<res;
    // 2  0 0  0 2  2 2  2 0
    pair<int, int> a = {0,0};
    pair<int, int> b = {0,2};
    pair<int, int> p = {2,2};
    pair<int, int> q = {2,0};
    
   // cout<<has_non_intersecting_path(2,a,b,p,q);
    double d = -2.3;
    double d1 = -2.7;
    cout<<floor(d)<<endl;
    cout<<floor(d1)<<endl;
    asa(4);
    return 0;
}
