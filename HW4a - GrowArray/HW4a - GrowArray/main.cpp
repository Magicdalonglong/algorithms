
#include <iostream>
#include <set>
#include <fstream>
#include <stdlib.h>
using namespace std;

class GrowArray { // C++: Vector<int>    Java: ArrayList
private:
    int *data;
    int used;
    int capacity;
public:
    GrowArray() {
        used=0;
        capacity = 0;
    }
    
    //preallocate storage for more speed (how much? 100%)
    GrowArray(int initialCapacity) {
        data = new int[initialCapacity];
        capacity = initialCapacity;
        used = 0;
    }
    
    ~GrowArray() {
        delete []data;
    }
    
    void addback(int start, int step, int end) {
        int len =(end-start)/step+1;
        if(used+len>capacity){
            while(capacity<used+len)capacity*=2;
            int *temp;
            temp = (int*)realloc(data, sizeof(int)*(capacity));
            if(temp == nullptr){
                cout<<"no more memory!\n";
                exit(1);
            }
            data = temp;
        }
        while(start<=end){
            data[used++]=start;
            start+=step;
        }
        
    }
    
    void addfront(int start, int step, int end ) {
        int len =(end-start)/step+1;
        if(used+len>capacity){
            while(capacity<used+len)capacity*=2;
            int *temp;
            temp = (int*)realloc(data, sizeof(int)*(capacity));
            if(temp == nullptr){
                cout<<"no more memory!\n";
                exit(1);
            }
            data = temp;
        }
        int index = used-1;
        for(int i=used+len-1;i>=0;i--){
            if(index<0){
                data[i]=start;
                start+=step;
            }
            else{
                data[i]=data[index--];
            }
            used++;
            
        }
        
        
    }
    void removeBack(int len) {
        if(len>used){
            cout<<"Remove length greater than current length\n";
            exit(1);
        }
        used-=len;
        
        
    }
    
    void removeFront(int len) {
        for(int i=0;i<used-len;i++){
            data[i]=data[i+len];
        }
        used-=len;
    }
    void print(){
    
        for(int i=0;i<used;i++)
            if(i<used-1)
                cout<<data[i]<<",";
            else
                cout<<data[i];
        cout<<endl;
    }
    
};


void commandline(string s, GrowArray* g, int *param){
    if(s=="ADD_FRONT")
        g->addfront(param[0],param[1],param[2]);
    
    else if(s=="ADD_BACK")
        g->addback(param[0],param[1],param[2]);
    
    else if(s=="REMOVE_FRONT")
        g->removeFront(param[0]);
    
    else if(s=="REMOVE_BACK")
        g->removeBack(param[0]);
    
    else if(s=="OUTPUT")
        g->print();
    else {
        cout<<"Invalid instructions\n";
        exit(1);
    }
    
}


int main(int argc, const char * argv[]) {
    
    
    set<int> s;
    auto res = s.insert(3);
   
    return 0;
    
}
