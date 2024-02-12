#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include <map>
#include <ctime>
#include <new>
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

class A{
public:
	int x;
	virtual void func() const{cout<<"A!!!!!!"<<this<<x<<endl;}
protected:
	int z;
};

class B:private A{
public:
	int y;
	virtual void func() const{cout<<"B!!!!!!"<<this<<A::x<<y<<endl;}
	void gunc()
	{
		A::z=10;
	}
};

void display(const A& a)
{
	a.func();
}

class Rational{
public:
	Rational(int numerator=0,int denominator=1):n(numerator),d(denominator){}
	int numerator()const{return n;}
	int denominator()const{return d;}
private:
	int n,d;
};

template<typename T>
class C{
public:
	void swap(C<T>&rhs){}
};

template<typename T>
void std::swap(C<T>& lhs,C<T>& rhs)
{
	cout<<"std::swap!!!!!!"<<endl;
	lhs.swap(rhs);
}

template<typename T>
void swap(C<T>& lsh,C<T>& rsh)
{
	cout<<"111111"<<endl;
}

struct D{
	int x;
	explicit D(int X):x(X){}
};

void gunc(double ,int )
{
	cout<<"double int"<<endl;
}

void gunc(int ,double )
{
	cout<<"int double"<<endl;
}

struct E{
	int x;
	virtual void func()
	{
		cout<<"E::func()"<<endl;
	}
};

struct F:public E{
	void func()
	{
		cout<<"F::func()"<<endl;
	}
};

class G final{
public:
	static void func(int ){cout<<"G::func()";}
private:
	static int x;
	G();
	~G();
};

void func(){cout<<"func!"<<endl;}

auto gunc()
{
	return []()->void
	{
		func();
		cout<<"lamaba function calling"<<endl;
	};
}

template<typename T>
auto punc(T t)
{
	t();
}

template<unsigned n>
struct Factorial{
	enum{ value = n* Factorial<n-1>::value };
};

template<>
struct Factorial<0>{
	enum{ value = 1 };
};

class H{
public:
	int x[100000];
	H(){throw 1;}
};


int main()
{	
	cout<<sizeof(H)<<endl;
	while(1)
	{
		try{
			H*p=new H;
		}
		catch(...)
		{

		}
	}
	system("pause");
	return 0;
}