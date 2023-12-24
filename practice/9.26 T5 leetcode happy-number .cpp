#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
#include <unordered_set>

#define ll long long

using namespace std;

class Solution {
public:
    
    int func(int x)
    {
        int sum=0;

        while(x)
        {
            sum+=(x%10)*(x%10);
            x/=10;
        }

        return sum;
    }

    bool isHappy(int n) {
        unordered_set<int> se;

        while(n!=1)
        {
            if(se.count(n))return false;
            else se.insert(n);

            n=func(n);
        }

        return true;
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);

    


    cout<<endl;
    system("pause");
    return 0;
}
