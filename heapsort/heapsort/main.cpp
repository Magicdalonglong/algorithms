//
//  main.cpp
//  heapsort
//
//  Created by Lei Duan on 4/22/17.
//  Copyright © 2017 Lei Duan. All rights reserved.
//

#include <iostream>
#include <vector>

using namespace std;

void heapify(vector<int>& nums, int n, int i){
    int largestindex = i;
    int left = i * 2 + 1, right = i * 2 + 2;
    if(left < n && nums[left] > nums[largestindex])
        largestindex = left;
    if(right < n && nums[right] > nums[largestindex])
        largestindex = right;
    if(largestindex != i){
        swap(nums[i], nums[largestindex]);
        heapify(nums, n, largestindex);
    }
}
void heapsort(vector<int>& nums){
    int len = nums.size();
    for(int i = len / 2 - 1; i >= 0; i--)
        heapify(nums, len, i);
    
    for(int i = len - 1; i >= 0; i--)
    {
        swap(nums[0], nums[i]);
        heapify(nums, i, 0);
    }
}


int main(int argc, const char * argv[]) {
    // insert code here...
    vector<int> nums(20);
    srand((unsigned)time(NULL));
    for(int i = 0; i < 20; i++)
        nums[i] = rand()%50;
    
    auto test = nums;
    
    cout<<"before: ";
    for(auto n : nums)cout<<n<<" ";
    
    heapsort(nums);
    sort(test.begin(), test.end());
    
    cout<<"\nafter : ";
    for(auto n : nums)cout<<n<<" ";
    
    cout<<"\nStand : ";
    for(auto n : test)cout<<n<<" ";
    
    std::cout << "\nHello, World!\n";
    return 0;
}
