#include <iostream>
#include <random>
#include <iomanip>  // setw function

using namespace std;
int globalcount=0;


class solution{
private:
    long mem[53][53] = {0};
public:
    
    solution(){}
    
    long choose(int n,int r){
        if(n==r||r==0)return mem[n][r]=1;
        if(mem[n][r]!=0)return mem[n][r];
        
        if(r>n/2)
            r = n - r;
        
        mem[n][r] = choose(n-1,r-1)+choose(n-1, r);
        
        return mem[n][r];
    }
    
};

int main() {
    solution s;
    long long count = 0;
    srand((unsigned)time(NULL));
    cout<<"---Use random n and r to test the choose r from n function---\n\n";
    cout<<"Enter a number n to set the time of test--pow(10,n):"<<endl;
    cout<<"(Give a number under five if you dont wanna wait too long) ";
    int n;
    cin>>n;
    while(count++<pow(10,n)){
        int n = rand()%52+1;
        int r = rand()%n;
        cout<<"Choose "<<r<<" from "<<n<< setw(2)<<" is: "<<s.choose(n, r)<<endl;
    }
    
}
