//
//  main.cpp
//  Lc_candy
//
//  Created by Lei Duan on 4/28/17.
//  Copyright © 2017 Lei Duan. All rights reserved.
//

#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

int candy(vector<int>& ratings) {
    cout<<"\ncur is 1 ";
    int res = 1, cur = 1, left = 0, len = ratings.size(), leftval = 1;
    for(int i = 1; i <= ratings.size(); i++){
        if(i == ratings.size() || ratings[i] >= ratings[i - 1]){
            if(cur < 1){
                res += (i - left - 1) * (1 - cur);
                if(i - left > leftval) res += i - left - leftval;
                if(i < ratings.size()){
                    res += cur = ratings[i] > ratings[i - 1] ? 2 : 1;
                }
            }else if(i < ratings.size()){
                res += cur = ratings[i] > ratings[i - 1] ? cur + 1 : 1;
                
            }
            left = -1;
        }else{
            if(left == -1){
                left = i - 1;
                leftval = cur;
            }
            cur = cur > 1 ? 1 : cur - 1;
            res += cur;
        }
        cout<<cur<<" ";
    }
    cout<<endl;
    return res;
}


//{58,21,72,77,48,9,38,71,68,77,82,47,25,94,89,54,26,54,54,99,64,71,76,63,81};
 // 2 1   2 3  2  1 2   3  1 2  3  2   1  4  3 2  1  2   1  2  1  2  3  1  2

int main(int argc, const char * argv[]) {
    // insert code here...
    vector<int> nums=  {58,21,72,77,48,9,38,71,68,77,82,47,25,94,89,54,26,54,54,99,64,71,76,63,81};
    string num = " 2 1   2 3  2  1 2   3  1 2  3  2   1  4  3 2  1  2   1  2  1  2  3  1  2 #";
    stringstream ss(num);
    int sum = 0;
    cout<<"stand: ";
    while(1){
        string n;
        ss >> n;
        if(n == "#") break;
        cout<<n<<" ";
    }
    auto res = candy(nums);
    cout<<"\nres is "<< res;
    std::cout << "\nHello, World!\n";
    return 0;
}
