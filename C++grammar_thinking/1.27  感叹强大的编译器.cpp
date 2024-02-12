#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include <map>
#include <ctime>
#include <shared_mutex>

using namespace std;

struct aaa{
	int x;
	aaa():x(int()){}
	aaa(int X):x(X){}
	aaa& operator=(const aaa& rhs){
		cout<<x<<' '<<"operator= ing ";
		x=rhs.x;
		return *this;
	}

	bool operator==(const aaa& rhs)
	{
		cout<<"operator==!!!! ";
		return x==rhs.x;
	}
};

struct node{
	aaa x;
	aaa *y;
	node():x(10),y(new aaa(10)){}
	node(int Y):x(11),y(new aaa(Y)){}
	node(const node& rhs):x(rhs.x),y(rhs.y){cout<<"structting !!!";}
	node(node&& rhs):x(rhs.x),y(rhs.y){cout<<"move structting !!!";}
	node& operator=(const node& rhs)
	{
		return *this;
	}
	node& operator=(node&& rhs)
	{
		x=rhs.x;
		y=rhs.y;
		cout<<"move operator!!!!";
		return *this;
	}
	~node(){cout<<x.x<<' '<<y->x<<"~node ing \n";}
};

struct a1{
	a1(){cout<<"a1!!!!!!"<<this<<endl;}
	a1(const a1& rhs){cout<<"a1 copy!!!!!!"<<this<<endl;}
};

struct a2{
	a2(){cout<<"a2!!!!!!"<<this<<endl;}
	a2(const a2& rhs){cout<<"a2 copy!!!!!!"<<this<<endl;}
	~a2(){cout<<"a2 destory!!!!!!"<<this<<endl;}
};

void func(a1 x,a2 y,a2 z,a1 w,a2 v)
{

}

class A{
public:
	int x;
	virtual void func() const{cout<<"A!!!!!!"<<this<<x<<endl;}
};

class B:public A{
public:
	int y;
	virtual void func() const{cout<<"B!!!!!!"<<this<<A::x<<y<<endl;}
};

void display(const A& a)
{
	a.func();
}

class Rational{
public:
	Rational(int numerator=0,int denominator=1):n(numerator),d(denominator){cout<<"Rational!!!!!!"<<this<<endl;}
	Rational(const Rational &rhs):n(rhs.n),d(rhs.d){cout<<"const Rational!!"<<endl;}
	Rational(Rational&& rhs):n(rhs.n),d(rhs.d){cout<<"&& Rational!!!"<<endl;}
	~Rational(){cout<<"~Rational!!!!!!"<<this<<endl;}

	int n,d;
	Rational& operator=(const Rational& rhs);
	Rational& operator=(Rational&& rhs);

    //按道理讲res是一个local变量，之后应该会被销毁，但是下面有一个构造语句。
    //因此虽然返回值是一个Rational，但是c的地址和res的地址一样，然后构造函数也没有调用
    //合理的解释是：c接管了res，减少了一次构造，一次析构，强大的编译器。
	const Rational operator*(const Rational& rhs)
	{
		Rational res(n*rhs.n,d*rhs.d);
		cout<<"operator*!!!!!"<<endl;
		return res;
	}
};


int main()
{	
	{
	Rational a,b;
	Rational c(a*b);
    a*b;
	cout<<c.n<<c.d<<' '<<&c<<endl;
	}

	system("pause");
	return 0;
}