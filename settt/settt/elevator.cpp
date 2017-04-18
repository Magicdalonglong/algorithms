#include <iostream>
#include <queue>
#include <iostream>
#include <random>
#include <set>

using namespace std;
class Elevator{
private:
	struct request {		
		int to;
		request(int t):to(t){}
	};
	
	int curfr = 0;
	set<request*> q;
	Elevator() {}
    Elevator(Elevator const&);              // Don't Implement.
    void operator=(Elevator const&);
public:
	
	static Elevator& getinstace(){
		static Elevator instance;
		return instance;
	}
	void movetotarget(int tar){
		cout<<"moving from" << curfr<<" to " <<tar<<endl;
		curfr = tar;
	}
	void addrequest(int to){
		q.insert(new request(to));
	}
	void process(){
		request* req = getrequest();

		if(req != NULL){
			int dest = req -> to;
			movetotarget(dest);
		}

	}
	void processall(){
		while(q.size()){
			process();
		}

	}
	request* getrequest(){
		request* res;
		int dict = INT_MAX;
		for(auto r : q)
		{
			if(abs(r->to - curfr) < dict)
			{
				dict = abs(r->to - curfr);
				res  = r;
			}
		}
		q.erase(res);
		return res;

	}
};

int main(){
	
	srand((unsigned)time(NULL));
	for(int i = 0; i< 10; i++){
		int d = rand()%100;
		cout<<"adding request: "<<d<<endl;
		Elevator::getinstace().addrequest(d);
	}
	cout<<"\nprocess all :\n";
	Elevator::getinstace().processall();
 

}

