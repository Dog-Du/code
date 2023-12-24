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
    int search(vector<int>&nums1,int start1,int end1,vector<int>&nums2,int start2,int end2,int k)
    {
        int len1;
        int len2;

        while(true)
        {
            len1=end1-start1+1;
            len2=end2-start2+1;
            if(len1>len2)//让nums1一直是较短的那个数组
            {
                swap(nums1,nums2);
                swap(start1,start2);
                swap(end1,end2);
                continue;
            }
            //如果短的等于0，那么直接返回长的的第k个
            if(len1==0)return nums2[start2+k-1];
            if(k==1)return min(nums1[start1],nums2[start2]);

            //为了防止越界，选择两者之间的较小值
            int i=start1+min(len1,k/2)-1;
            int j=start2+min(len2,k/2)-1;

            //排除
            if(nums1[i]>nums2[j])k-=j-start2+1,start2=j+1;
            else 
               k-=i-start1+1,start1=i+1;
        }
    }

public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
       return (search(nums1,0,nums1.size()-1,nums2,0,nums2.size()-1,nums1.size()+nums2.size()+1>>1)+
        search(nums1,0,nums1.size()-1,nums2,0,nums2.size()-1,nums1.size()+nums2.size()+2>>1))*0.5;
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);

    
    vector<int>nums1={2};
    vector<int>nums2;
    Solution one;
    one.findMedianSortedArrays(nums1,nums2);

    cout<<endl;
    system("pause");
    return 0;
}
