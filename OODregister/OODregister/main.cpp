#include <iostream>
#include <unordered_map>
#include <vector>
#include <list>
#include <iostream>
using namespace std;



class RegisterCenter {
private:
    RegisterCenter(){}
    void operator= (RegisterCenter const&);
    RegisterCenter(RegisterCenter const&);
    
    // list data
    list<string> registe_list;
    unordered_map<string,list<string>::iterator> hash;
    // site
    const int indoorSiteCapacity = 4;
    const int outdoorSiteCapacity = 8;
    int Capacity;
public:
    // singleton
    static RegisterCenter& getinstace(){
        static RegisterCenter instace;
        return instace;
    }
    
    void Register(string name){
        registe_list.push_back(name);
        hash[name] = (--registe_list.end());
    }
    void Cancel(string name){
        registe_list.erase(hash[name]);
    }
    void Arrange(int weather){
        ChooseSite(weather);
        int count = 0;
        for(auto registered : registe_list){
            if(++ count <= Capacity)
                cout<<registered<<" Regiteration comfirmed\n";
            else
                cout<<registered<<" Capacity reached, Regiteration not comfirmed\n";
        }
        
    }
    
    void ChooseSite(int weather){
        Capacity = weather == 0 ? indoorSiteCapacity : outdoorSiteCapacity;
    }
    
};

class User{
private:
    string name;
public:
    User(string n ) : name(n){}
    void registe(){
        RegisterCenter::getinstace().Register(name);
    }
    void cancel(){
        RegisterCenter::getinstace().Cancel(name);
    }
};

int main() {
    cout<<"Hello\n";
    vector<User> urs;
    urs.emplace_back("Joe");
    urs.emplace_back("Jack");
    urs.emplace_back("Lisa");
    urs.emplace_back("harry");
    urs.emplace_back("emily");
    urs.emplace_back("Alison");
    urs.emplace_back("Chloe");
    for(auto ur : urs)
        ur.registe();
    urs[1].cancel();
    urs[1].registe();
    RegisterCenter::getinstace().Arrange(0);
    cout<<endl;
    return 0;
}
