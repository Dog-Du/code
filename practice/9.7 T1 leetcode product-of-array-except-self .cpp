#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>

#define ll long long

using namespace std;

//前缀和和后缀和的结合实现没有使用除法
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
         int length=nums.size();
        vector<int> ans(length);
        int cnt=0;

        for(auto&it:nums)
            if(!it)++cnt;
        
        if(cnt>1)
            return ans;
        else if(cnt==1)
        {
            int sum=1,t;

            for(int i=0;i<length;++i)
                if(!nums[i])
                    t=i;
                else
                    sum*=nums[i];
            
            ans[t]=sum;

            return ans;
        }
        else
        {
            ans.back()=nums.back();

            for(int i=length-1-1;i>=0;--i)
                ans[i]=ans[i+1]*nums[i];
            
            for(int i=1;i<length;++i)
                nums[i]=nums[i]*nums[i-1];
            
            ans[0]=ans[1];

            for(int i=1;i<length-1;++i)
                ans[i]=ans[i+1]*nums[i-1];

            ans.back()=nums[length-2];

            return ans;
        }

        return ans;
    }
};


//分类讨论和前缀和
class Solution {
public: 
    vector<int> productExceptSelf(vector<int>& nums) {
       int length=nums.size();
        vector<int> ans(length);
        int cnt=0;

        for(auto&it:nums)
            if(!it)++cnt;
        
        if(cnt>1)
            return ans;
        else if(cnt==1)
        {
            int sum=1,t;

            for(int i=0;i<length;++i)
                if(!nums[i])
                    t=i;
                else
                    sum*=nums[i];
            
            ans[t]=sum;

            return ans;
        }
        else
        {
            for(int i=1;i<length;++i)
                nums[i]*=nums[i-1];
            
            ans[0]=nums.back()/nums.front();

            for(int i=1;i<length;++i)
                ans[i]=nums.back()/(nums[i]/nums[i-1]);
            
            return ans;
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
