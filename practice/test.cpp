#include<iostream>
#include <list>
#include<string>
#include <vector>
#include <random>
#include <algorithm>
#include <ctime>

template<typename X>
void print(const X&x,const std::string&end="\n")
{
	std::cout<<x<<end;
}

int main()
{
	std::ios::sync_with_stdio(false);
	std::cout.tie(0),std::cin.tie(0);

	std::random_device seed;
	std::minstd_rand rng(seed());
	
	system("pause");
	return 0;
}