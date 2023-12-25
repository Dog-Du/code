#include <iostream>


class myint{
public:
    int a;
    myint():a(1){}

    void print()const
    {
        std::cout<<a<<std::endl;
    }

    const int& get()const
    {
        return a;
    }

    void set(int x)
    {
        a=x;
    }
};
int main()
{
	std::ios::sync_with_stdio(false);
	std::cout.tie(0),std::cin.tie(0);


	std::cout<<std::endl;
	system("pause");
	return 0;
}