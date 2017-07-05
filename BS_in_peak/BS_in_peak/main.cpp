//
//  main.cpp
//  BS_in_peak
//
//  Created by Lei Duan on 4/23/17.
//  Copyright © 2017 Lei Duan. All rights reserved.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>


using namespace std;

bool search(vector<int>& nums, int tar){
    int i = 0, j = nums.size() - 1;
    while(i < j){
        int mid = i + (j - i) / 2;
        if(nums[mid] < nums[mid + 1]) i = mid + 1;
        else j = mid;
    }
    int index = i;
    auto left = lower_bound(nums.begin(), nums.begin() + index, tar);
    if(left != nums.begin() + index && *left == tar) return 1;
    auto right = lower_bound(nums.begin() + index, nums.end(), tar, greater<int>());
    if(right != nums.end() && *right == tar) return 1;
    return 0;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    int n = 120;
    vector<int> num(n);
    srand((unsigned)time(NULL));
    for(int i = 0; i < n; i++){
        num[i] = i;
    }
    random_shuffle(num.begin(), num.end());
    int index = rand()%n;
    auto max = max_element(num.begin(), num.end());
    swap(*(max), num[index]);
    sort(num.begin(), num.begin() + index);
    sort(num.begin() + index, num.end(),greater<int>());
    

    for(auto n : num) cout<<n<<" ";
    for(int i = -50; i < 150; i++ )
    {
        bool res = search(num, i) == (i < n && i >= 0);
        if(res)cout<<"testing on "<<i<<" :"<< "True" <<endl;
        else {
            cout<<"testing on "<<i<<" :"<< "False" <<endl;
            break;
        }
    }
    
    cout<<endl;
    return 0;
}
