#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>

#define ll long long

using namespace std;

class myclass{
public:
    int a,b;
    myclass():a(1),b(1){cout<<"111"<<endl;}
    myclass(int A):a(A){cout<<"222"<<endl;}
    myclass(int A,int B):a(A),b(B){cout<<"333"<<endl;}
    myclass(const myclass &it):a(it.a),b(it.b){cout<<"444"<<endl;}
    myclass& operator=(myclass it)
    {
        a=it.a;
        b=it.b;
        cout<<"555"<<endl;
        return *this;
    }
};

//调用的全是构造函数
void func(myclass){}

void gunc(const int & x){cout<<x<<endl;}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);

    
    myclass a;
    func({});
    func({1});
    func({1,2});
    func(a);
    
    gunc(1);

    const int &x=1;
    cout<<x<<endl;

    cout<<endl;
    system("pause");
    return 0;
}
