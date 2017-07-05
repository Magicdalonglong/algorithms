//
//  main.cpp
//  class_friend
//
//  Created by Lei Duan on 5/6/17.
//  Copyright © 2017 Lei Duan. All rights reserved.
//

#include <iostream>
using namespace std;

class Imaginary {
private:
    int real;
    int im;
public:
    Imaginary(){
        real = 0;
        im = 0;
    }
    Imaginary (int a, int b): real(a), im(b){}
    Imaginary operator+(Imaginary& other){
        Imaginary res;
        res.im = im + other.im;
        res.real = real + other.real;
        return res;
    }
    friend ostream& operator<<(ostream& o, const Imaginary& i){
        o<<i.real <<"+ i"<<i.im;
        return o;
    }
    
};

int main(int argc, const char * argv[]) {
    // insert code here...

    Imaginary i(12,3);
    Imaginary i2(123,12);
    auto res = i + i2;
    cout<<res;
    std::cout << "\nHello, World!\n";
    return 0;
}
