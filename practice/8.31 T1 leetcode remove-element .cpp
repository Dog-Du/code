#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#define ll long long

using namespace std;

class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int l=0,r=0,length=nums.size();

        while(l<length&&r<length)
        {
            if(nums[r]==val)++r;
            else
                nums[l++]=nums[r++];
        }

        return l;
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
