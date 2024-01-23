#include<iostream>
#include <list>
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include <map>
#include <ctime>

using namespace std;

int func(int x,int y)
{
	return x+y;
}


int main()
{
	int (*a)(int,int)=func;
	cout<<a(1,2)<<endl;
	

	system("pause");
	return 0;
}