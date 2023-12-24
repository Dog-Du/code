#include <iostream>
#include <queue>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <set>
#include <map>
#include <algorithm>

#define ll long long

using namespace std;

//
//法二：建立一个map，值域二分，但是这需要map支持getrank操作


//这个是左右两边是map。可以实现增删改 logn 查 1
class MedianFinder {
private:
    map<int,int> le,ge;//左子树，top为小于等于mid的最大值
    int mid=RAND_MAX;//指向最中间
    int sizel=0,sizer=0;
public:
    MedianFinder() {
        
    }
    
    void addNum(int num) {
        if(mid==RAND_MAX)
        {
            mid=num;
            return;
        }

        if(num>=mid)++ge[num],++sizer;
        else ++le[num],++sizel;
        
        int bf=sizer-sizel;

        if(bf>1)
        {
            ++le[mid];
            mid=ge.begin()->first;
            ++sizel,--sizer;
            if(--ge[mid]==0)
                ge.erase(ge.find(mid));
        }
        else if(bf<-1)
        {
            ++ge[mid];
            mid=(--le.end())->first;
            ++sizer,--sizel;
            if(--le[mid]==0)
                le.erase(le.find(mid));
        }
    }
    
    double findMedian() {
        if(sizel>sizer)
            return 1.0*((--le.end())->first+mid)/2;
        else if(sizel<sizer)
            return 1.0*(ge.begin()->first+mid)/2;
        else    
            return 1.0*mid;
    }
};


//建立一个AVL树，le表示左子树，ge表示右子树
//平衡条件是左右子树size差不大于1.
// class MedianFinder {
// private:
//     priority_queue<int,vector<int>,greater<int>> ge;//左子树，top为小于等于mid的最大值
//     priority_queue<int,vector<int>,less<int>> le;//右子树，top为大于等于mid的最小值
//     int mid=RAND_MAX;//指向最中间
// public:
//     MedianFinder() {
        
//     }
    
//     void addNum(int num) {
//         if(mid==RAND_MAX)
//         {
//             mid=num;
//             return;
//         }

//         if(num>=mid)ge.push(num);
//         else le.push(num);
        
//         int bf=ge.size()-le.size();

//         if(bf>1)//一个类似于左旋的操作
//         {
//             le.push(mid);
//             mid=ge.top();
//             ge.pop();
//         }
//         else if(bf<-1)
//         {
//             ge.push(mid);
//             mid=le.top();
//             le.pop();
//         }
//     }
    
//     double findMedian() {
//         if(le.size()>ge.size())
//             return 1.0*(le.top()+mid)/2;
//         else if(le.size()<ge.size())
//             return 1.0*(ge.top()+mid)/2;
//         else    //左右子树size相等，说明奇数，直接返回根即可。
//             return 1.0*mid;
//     }
// };

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);

    int n;
    cin>>n;
    MedianFinder one;
    //一种基于AVL树和Treap思想结合的有趣写法
    while(n--)
    {
        int op;
        cin>>op;

        if(op==1)
        {
            int x;
            cin>>x;
            one.addNum(x);
        }
        else
        {
            cout<<one.findMedian()<<endl;
        }
    }


    cout<<endl;
    system("pause");
    return 0;
}
