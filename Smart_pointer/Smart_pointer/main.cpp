#include <iostream>
#include <memory>
#include <memory>
#include <list>
#include <vector>
#include <stack>
#include <queue>

using namespace std;

int search(vector<int>& nums, int tar) {
    int lo = 0, hi = int(nums.size()) - 1;
    while(lo < hi){
        int mid = lo + (hi - lo) / 2;
        if(tar == nums[mid]) return mid;
        else if((tar < nums[0]) ^ (nums[mid] < nums[0]) ^ (tar < nums[mid])) hi = mid - 1;
        else lo = mid + 1;
    }
    return lo >= 0 && nums[lo] == tar? lo : -1;
    
}



int main(){
//{
//    int n = 3;
//    std::unique_ptr<double[]> d(new double[n]);
//    shared_ptr<int> p2 = make_shared<int>(112);
//    for(int i = 0; i < n; i++) d[i] =i * 3.3;
//    
//    for(int i = 0; i < n; i++) cout<<d[i]<<" ";
//    cout<<endl;
    vector<int> num = {4,5,6,7,0,1,2};
    vector<int> num2 = {0};
    cout<<search(num2, 5)<<endl;
}
