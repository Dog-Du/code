#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>

#define ll long long

using namespace std;

//也是单调栈，但是在弹出的时候进行了分析，测，有点妙
class Solution {
public:
    vector<int> canSeePersonsCount(vector<int>& heights) {
        int n=heights.size();
        vector<int> st,ans(n,0);

        for(int i=n-1;i>=0;--i)
        {
            while(!st.empty()&&heights[st.back()]<heights[i])
            {
                st.pop_back();
                ++ans[i];
            }

            if(!st.empty())
                ans[i]++;
            
            st.push_back(i);
        }

        return ans;
    }
};


//下面这个有问题、
class Solution {
public:
    vector<int> canSeePersonsCount(vector<int>& heights) {
        vector<int> st,st_back,st_front;
        //st_front表示i可以影响那些，st_back表示i受那些影响
        //i受j影响而+1等价于 st_front[j]<=i 并且 st_back[i] >= j

        int n=heights.size();
        st_back.resize(n,n-1);
        st_front.resize(n,0);

        for(int i=n-1;i>=0;--i)
        {
            while(!st.empty()&&heights[st.back()]<=heights[i])
            {
                st_front[st.back()]=i;
                st.pop_back();
            }
            st.push_back(i);
        }   

        st.clear();

        for(int i=0;i<n;++i)
        {
            while(!st.empty()&&heights[st.back()]<=heights[i])
            {
                st_back[st.back()]=i;
                st.pop_back();
            }
            st.push_back(i);
        }
        
        st.clear();
        st.resize(n,0);

        for(int i=0;i<n;++i)
        {
            for(int j=i+1;j<=st_back[i];++j)
                if(st_front[j]<=i)++st[i];
        }

        return st;
    }  
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);

    vector<int> vec={10,6,8,5,11,9};
    Solution one;
    one.canSeePersonsCount(vec);


    cout<<endl;
    system("pause");
    return 0;
}
