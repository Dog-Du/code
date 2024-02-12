#include <iostream>
#include <cmath>
#include <ctime>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>

#define ll long long

using namespace std;

struct a2{
	a2(){cout<<"a2!!!!!!"<<this<<endl;}
	a2(const a2& rhs){cout<<"a2 copy!!!!!!"<<this<<endl;}
	~a2(){cout<<"a2 destory!!!!!!"<<this<<endl;}
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);

#ifdef LOCAL
    clock_t c1 = clock();
#endif

//-------------------------------------------------
{
    a2& a=*(new a2());//不会调用析构函数。

}
//-------------------------------------------------

#ifdef LOCAL
    cout << "\nTime Used: \n" << clock() - c1 << " ms" << endl;
#endif

    system("pause");
    return 0;
}
