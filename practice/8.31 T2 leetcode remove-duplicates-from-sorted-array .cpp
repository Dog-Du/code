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
    int removeDuplicates(vector<int>& nums) {
        int l=0,r=0,length=nums.size();

        while(r<length)
        {
            if(l>0&&nums[l-1]==nums[r])++r;//因为l指向最后一个元素的后方
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
