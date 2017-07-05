//
//  main.cpp
//  PG_lc_4_med_of_2_sorted_array
//
//  Created by Lei Duan on 6/19/17.
//  Copyright © 2017 Lei Duan. All rights reserved.
//

#include <iostream>
#include <vector>
using namespace std;
class Solution {
public:
    // 0 1 2 3
    // if(mid < m && mid2 > 0 && nums1[mid] <= nums2[mid2 - 1])
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        if(nums2.empty()) return nums1.size() & 1 ? nums1[nums1.size() / 2] : (nums1[nums1.size() / 2] + nums1[nums1.size() / 2 - 1]) / 2.0;
        int m = nums1.size(), n = nums2.size();
        int left = 0, right = m;
        // 0 .... mid - 1 | mid ... m - 1,
        // 0 .... mid2 - 1| mid2 ... n - 1,
        while(left <= right) {
            int mid = left + ( right - left ) / 2, mid2 = ( m + n + 1 ) / 2 - mid;
            //  cout<<mid<<" "<<mid2<< ",  ";
            if(mid > 0 && mid2 < n && nums1[mid - 1] > nums2[mid2] ) right = mid - 1;
            else if(mid < m && mid2 > 0 && nums1[mid] < nums2[mid2 - 1]) left = mid + 1;
            else {
                int left_max, right_min;
                if(mid == 0) left_max = nums2[mid2 - 1];
                else if (mid2 == 0) left_max = nums1[mid - 1];
                else left_max = max(nums1[mid - 1], nums2[mid2 - 1]);
                
                if(( m + n ) & 1) return left_max;
                
                if(mid == m) right_min = nums2[mid2];
                else if (mid2 == n) right_min = nums1[mid];
                else right_min = min(nums1[mid], nums2[mid2]);
                
                return (left_max + right_min) / 2.0;
            }
        }
        return 0;
    }
};


int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    Solution s;
    vector<int> n1 = {3,4,5,6};
    vector<int> n2 = {1,2};
    s.findMedianSortedArrays(n1, n2);
    return 0;
}
