#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>

#define ll long long

using namespace std;

class Solution {
private:
    bool check(string &a,string &b)
    {
        return a.size()==b.size()&&a.size()>0&&
            equal(a.begin(),a.end(),b.rbegin());
    }
public:
    int maximumNumberOfStringPairs(vector<string>& words) {
        int ans=0;
        for(int i=0,j,n=words.size();i<n;++i)
        {
            for(j=i+1;j<n;++j)
            {
                if(check(words[i],words[j]))
                {
                    ++ans;
                    words[j]="";
                    break;
                }
            }
        }
        return ans;
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
