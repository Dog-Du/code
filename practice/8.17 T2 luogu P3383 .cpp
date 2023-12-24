#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>

#define ll long long

using namespace std;

const int maxn=1e8+2;

vector<int> prime;
bool is_prime[maxn];

void prime_fliter(int n)
{
    for(int i=2;i<=n;++i)
    {
        if(!is_prime[i])
        {
            prime.push_back(i);
        }

        for(const auto&it:prime)
        {
            if(it>n/i)break;

            is_prime[i*it]=1;

            if(i%it==0)break;
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);

    int n,q;

    cin>>n>>q;

    prime_fliter(n);

    while(q--)    
    {
        int x;
        cin>>x;

        cout<<prime[x-1]<<'\n';
    }


    cout<<endl;
    system("pause");
    return 0;
}
