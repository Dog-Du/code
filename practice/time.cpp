#include <iostream>
#include <cmath>
#include <string>
#include <functional>

using namespace std;

struct myclass{
	int a,b;
	myclass(){cout<<"1111"<<endl;}
	myclass(int A):a(A){cout<<"222"<<endl;}
	myclass(int A,int B):a(A),b(B){cout<<"333"<<endl;}
	myclass(myclass&x):a(x.a),b(x.b){cout<<"444"<<endl;}
	
	myclass& operator=(const myclass&x)
	{
		a=x.a;
		b=x.b;
		cout<<"555"<<endl;
		return *this;
	}
};

void fun(myclass){}

int main()
{	
	
	system("pause");
	return 0;
}
