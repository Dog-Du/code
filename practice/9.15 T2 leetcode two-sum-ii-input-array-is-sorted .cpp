#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>

#define ll long long

using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
            vector<int> ans;

            for(int i=0,l,r,mid,t,n=numbers.size()
                        ;i<n;++i)
            {
                l=i+1,r=n-1,t=0;

                while(l<=r)
                {
                    mid=l+r>>1;

                    if(numbers[mid]+numbers[i]>=target)
                        r=mid-1,t=mid;
                    else
                        l=mid+1;
                }

                if(numbers[t]+numbers[i]==target)
                {
                    ans.push_back(i+1);
                    ans.push_back(t+1);
                    return ans;
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
