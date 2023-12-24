#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
#include <queue>

#define ll long long

using namespace std;

class Solution {
private:
    int quicksort(vector<int>&nums,int k)//k==0
    {
        int n=nums.size();
        int start=0,end=n-1,l,r;

        while(1)
        {
            //这种quicksort写法保证了，每次选择的pivot都在正确位置上，
            //可以说是原教义quicksort了
            l=start,r=end;
            swap(nums[l++],nums[rand()%(end-start+1)+start]);

            while(l<=r)
            {
                while(l<=r&&nums[l]<nums[start])++l;
                while(l<=r&&nums[r]>nums[start])--r;

                if(l>=r)break;
                swap(nums[l++],nums[r--]);
            }
            swap(nums[start],nums[r]);

            if(r<k)start=r+1;
            else if(r>k)end=r-1;
            else return nums[r];
        }
        return -1;
    }
public:
    int findKthLargest(vector<int>& nums, int k) {
        srand(114514);
        return quicksort(nums,nums.size()-k);
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);

    vector<int> vec={-1,-1};
    Solution one;
    one.findKthLargest(vec,2);



    cout<<endl;
    system("pause");
    return 0;
}
