//
//  main.cpp
//  lc273
//
//  Created by Lei Duan on 2/24/17.
//  Copyright © 2017 Lei Duan. All rights reserved.
//

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    
    string convert(int n){
        switch( n){
            case 0: return "Zero ";break;
            case 1: return "One ";break;
            case 2: return "Two ";break;
            case 3: return "Three ";break;
            case 4: return "Four ";break;
            case 5: return "Five ";break;
            case 6: return "Six ";break;
            case 7: return "Seven ";break;
            case 8: return "Eight ";break;
            case 9: return "Nine ";break;
            case 10: return "Ten ";break;
            case 11: return "Eleven ";break;
            case 12: return "Twelve ";break;
            case 13: return "Thirteen ";break;
            case 14: return "Fourteen ";break;
            case 15: return "Fifteen ";break;
            case 16: return "Sixteen ";break;
            case 17: return "Seventeen ";break;
            case 18: return "Eighteen ";break;
            case 19: return "Nineteen ";break;
            case 20: return "Twenty ";break;
            case 30: return "Thirty ";break;
            case 40: return "Forty ";break;
            case 50: return "Fifty ";break;
            case 60: return "Sixty ";break;
            case 70: return "Seventy ";break;
            case 80: return "Eighty ";break;
            case 90: return "Ninety ";break;
            case 100: return "Hundred ";break;
            case 1000: return "Thousand ";break;
            case 1000000: return "Million ";break;
            case 1000000000: return "Billion ";break;
            default: return "Non";
        }
        
        
        
    }
    string numberToWords(int num) {
        string res;
        if(num/1000000000)
            res+=helper(num/1000000000)+ convert(1000000000);
        num%=1000000000;
        
        if(num/1000000)
            res+=helper(num/1000000)+ convert(1000000);
        num%=1000000;
        if(num/1000)
            res+=helper(num/1000)+ convert(1000);
        num%=1000;
        if(res.empty()||num)
            res+= helper(num);
        res.pop_back();
        return res;
        
    }
    
    string helper(int num){    //  less than 1000
        if(num<=20)
            return convert(num);
        string res;
        if(num/100) res = convert(num/100) +  convert(100);
        num%=100;
        if(num/10) res+=convert(num/10*10) + ((num%10)?convert(num%10):"");
        return res;
    }
};

int main(int argc, const char * argv[]) {
    // insert code here...

    Solution s ;
    
    int n = 30;
    cout<<s.numberToWords(30);
    std::cout << "Hello, World!\n";
    return 0;
}
