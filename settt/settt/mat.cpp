#include <iostream>
#include <vector>
using namespace std;

class mat {
private:
    double* data;
    int m;
    int n;
public:   
    mat(int m_, int n_){
        m = m_; n = n_;
        data = new double[m * n];
        for(int i = 0; i < m * n; i++) data[i] = 0;
    }
    ~mat(){
        m = n = 0;
        delete []data;
    }
    void set(int i, int j, double val){
        data[i * n + j] = val;
    }
    double get(int i, int j){
        return data[i * n + j];
    }

};
// 2,1
// 12
// 1 2 3
// 4 5 6
// 7 8 9
// 1 2 3

int main() {
    cout<<"Hello\n";
    

    mat m(3,4);
    double cur =1.5;
    for(int i = 0 ;i < 3; i++)
        for(int j = 0 ;j < 4; j++)
            m.set(i,j,cur++);

    for(int i = 0 ;i < 3; i++){
        for(int j = 0 ;j < 4; j++)
            cout<<m.get(i,j)<<" ";
        cout<<endl;
    }
   

    return 0;
}
