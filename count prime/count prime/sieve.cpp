
#include <iostream>
#include <stdint.h>
#include <cmath>
#include <vector>
using namespace std;

class solution{
private:
    int len;
    long left;
    long right;
    vector<bool> primes;
    
public:
    // constructor
    solution(long n1, long n2):left(n1),right(n2),len(n2-n1+1){
        primes.assign(len, true);
    }
    
    bool isPrime(long num){
        if(num==2)return 1;
        for(int i=2; i<=sqrt(num); i++)
            if(!(num%i)) return false;
        return true;
    }
    
    //get the primes from 2 to sqrt(right)
    vector<int> init(){
        int range = floor(sqrt((double)right));
        vector<bool> flag(range+1,true);
        vector<int> init_primes;
        for(int i=4; i<=range; i+=2){
            flag[i]=false;
        }
        for(int i=3; i<=sqrt(range); i+=2){
            if(isPrime(i)){
                for(int j=i*i; j<=range; j+=2*i){
                    flag[j]=false;
                }
            }
        }
        
        for(int i=2; i<=range; i++){
            if(flag[i]){
                init_primes.push_back(i);
            }
        }
        return init_primes;
    }
    //Sieve to count prime btw left and right
    int Sieve(){
        vector<int> init_primes = init();
        
        for(int i=0; i<init_primes.size(); i++){
            int step = init_primes[i];
            long s = left/step;
            s *= step;// find the start point
            for(long j=s; j<=right; j+=step){
                if(j<left)continue;
                primes[j-left] = false;
            }
        }
        int count=0;
        for(int i=0; i<len; i++){
            if(primes[i]&&(i+left)!=1 ){
                count++;
            }
        }
        
        
        // add back the initial primes in the range
        for(int i=0;i<init_primes.size();i++)
            if(init_primes[i]>=left && init_primes[i]<=right)
                count++;
        
        return count;
    }
};


int main(){
    long left,right;//left = 2000000000000, right = 2000000100000;
    cout<<"Enter two numbers (left, right) to test: "<<endl;
    cin>>left>>right;
    solution s(left,right);
    cout<<"There are "<<s.Sieve()<<" primes between "<<left<<" and "<<right<<endl;
    
    return 0;
}

