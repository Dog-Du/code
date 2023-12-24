#include <iostream>
#include<queue>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
#include <set>

#define ll long long

using namespace std;


// 多路归并算法的基本思想如下：

// 1) 首先建立一个小顶堆；

// 2) 将每一路的最小元素（即第1列元素）都加入小顶堆中，此时堆顶就是k路中全局的最小值；

// 3) 将堆顶元素弹出，并将堆顶元素所在数组的下一个元素加入堆中。

// 4) 重复第2)和第3)步，直至每一路数据都读取结束。


class Solution {
public:
    //相当于n路归并？
    
    vector<vector<int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
        vector<vector<int>> ans;
        int n=nums1.size(),m=nums2.size();

        auto cmp=[&nums1,&nums2](vector<int>&a,vector<int>&b){
                return nums1[a.front()]+nums2[a.back()]>nums1[b.front()]+nums2[b.back()];
            };

        //没用过这种语法
        priority_queue<vector<int>,vector<vector<int>>,decltype(cmp)> que(cmp);//建堆
        
        for(int i=0;i<min(n,k);++i)//每一路最小值放进去，i为第i路
            que.push({i,0});
        
        while(ans.size()<k&&!que.empty())
        {
            auto it=move(que.top());
            que.pop();
            ans.push_back({nums1[it.front()],nums2[it.back()]});//把最小值放入答案集合
            if(it.back()<m)que.push({it.front(),it.back()+1});//第i路进行下一步。
        }

        return ans;
    }
};

//错解
// class Solution {
// public:
//     vector<vector<int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
//         int p1=0,p2=0,n=nums1.size(),m=nums2.size(),sum1,sum2;

//         vector<vector<int>> ans;
//         ans.push_back({nums1.front(),nums2.front()});

//         while(k--&&(p1!=n||p2!=m))      
//         {
//             if((p1<n-1&&p2<m-1&&nums1[p1+1]+nums2[p2]>nums1[p1]+nums2[p2+1])||p1==n)
//                 ans.push_back({nums1[p1],nums2[++p2]});
//             else if((p1<n-1&&p2<m-1&&nums1[p1+1]+nums2[p2]<nums1[p1]+nums2[p2+1])||p2==m)
//                 ans.push_back({nums1[++p1],nums2[p2]});
//             else if(nums1[p1]<nums2[p2])    
//                 ans.push_back
//         }

//         return ans;
//     }
// };

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);

    vector<int> n1={1,1,2},n2={1,2,3};
    Solution one;

    auto ans=one.kSmallestPairs(n1,n2,2);

    for(auto&it:ans)
    {
        cout<<it.front()<<' '<<it.back()<<endl;
    }

    cout<<endl;
    system("pause");
    return 0;
}
