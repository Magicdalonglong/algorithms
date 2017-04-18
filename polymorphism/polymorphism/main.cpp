//
//  main.cpp
//  polymorphism
//
//  Created by Lei Duan on 3/31/17.
//  Copyright © 2017 Lei Duan. All rights reserved.
//

#include <iostream>

using namespace std;


class vehicle {
public:
    int weight;
    virtual int GPM()
    {
        return 9901;
    }
    void setweight(int w){
            weight = w;
    }
};


class car : public vehicle {
public:

     int GPM(){
        return weight * 16;
    }
  
};


class truck : public vehicle {
public:

    int GPM(){
        return weight * 32;
    }
   
};

class nissan : public car {
    int GPM(){
        return weight * 10;
    }
    
};
class A{
public:
    A(){
        cout<<"1A ";
    }
     virtual ~A(){
        cout<<"3A ";
    }
};

class B : public A{
public:
    B(){cout<<"1B ";}
    ~B(){
        cout<<"3B ";
    }
    
};
int main(int argc, const char * argv[]) {
    // insert code here...
//    std::cout << "Hello, World!\n";
//    car c1;
//    vehicle v1;
//    truck t1;
//    nissan n1;
//    vehicle* p1 = &c1;
//    vehicle* p2 = &t1;
//    vehicle* p3 = &v1;
//    vehicle* p4 = &n1;
//    p1->setweight(100);
//    p2->setweight(100);
//    p3->setweight(100);
//    p4->setweight(100);
//    cout<<"p1->GPM() " <<p1->GPM()<<endl;
//    cout<<"p2->GPM() " <<p2->GPM()<<endl;
//    cout<<"p3->GPM() " <<p3->GPM()<<endl;
//    cout<<"p4->GPM() " <<p4->GPM()<<endl;
    
    A *p = new B();
    delete p;
    cout<<endl;
    return 0;
}
