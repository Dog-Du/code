#include <iostream>
#include <cmath>
#include <string>
#include <set>
#include <cstring>
#include <vector>
#include <algorithm>
#include <queue>

#define ll long long

using namespace std;

//贪心
//策略：按照cap排序，
//把当前小于等于w的全部放进heap（以pro为比较项的大根堆），
//然后取出最大值相加。

class Solution {
private:
    struct node {
        int pro,cap;
        node(int &p,int& c):pro(p),cap(c){}
        bool operator<(const node&other)const{
            return cap<other.cap;
        }
        bool operator>(const node&other)const{
            return pro<other.pro;
        }
    };
public:
    int findMaximizedCapital(int k, int w, vector<int>& profits, vector<int>& capital) {
        vector<node> vec;
        int n=profits.size();

        for(int i=0;i<n;++i)
            vec.push_back({profits[i],capital[i]});

        priority_queue<node,vector<node>,greater<node>> que;

        sort(vec.begin(),vec.end());
        int i=0;

        while(k--)
        {
            while(i<n&&vec[i].cap<=w)
                que.emplace(vec[i++]);
            
            if(que.empty())break;

            w+=que.top().pro;
            que.pop();
        }

        return w;
    }
};

//暴力解法
class Solution {
private:
    struct node{
        int pro,cap;
        node(int &p,int& c):pro(p),cap(c){}

        bool operator<(const node&other)const{
            return pro<other.pro;
        }
    };

public:
    int findMaximizedCapital(int k, int w, vector<int>& profits, vector<int>& capital) {
        int n=profits.size();
        vector<node> vec;

        for(int i=0;i<n;++i)
            vec.push_back({profits[i],capital[i]});
        
        //实现pro从大到小。
        priority_queue<node,vector<node>> que(vec.begin(),vec.end());
        vec.clear();

        while(k>0)
        {
            while(!que.empty()&&w<que.top().cap)
            {
                vec.push_back(que.top());
                que.pop();
            }

            if(que.empty())break;

            w+=que.top().pro;
            que.pop();
            --k;

            while(!vec.empty())
            {
                que.push(vec.back());
                vec.pop_back();
            }
        }

        return w;
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
