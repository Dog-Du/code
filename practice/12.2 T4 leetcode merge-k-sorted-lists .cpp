#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>

#define ll long long

using namespace std;

 struct ListNode {
      int val;
      ListNode *next;
      ListNode() : val(0), next(nullptr) {}
      ListNode(int x) : val(x), next(nullptr) {}
      ListNode(int x, ListNode *next) : val(x), next(next) {}
  };
 

class Solution {
private:
    void merge(ListNode*&list,ListNode*&p)
    {
        ListNode*p1=list,*p2=p,*it=nullptr,*ans=nullptr;

        while(p1!=nullptr&&p2!=nullptr)
        {
            if(p1->val<p2->val)
            {
                if(it==nullptr)it=ans=p1;
                else
                {
                    it->next=p1;
                    it=it->next;
                }
                p1=p1->next;
            }
            else
            {
                if(it==nullptr)it=ans=p2;
                else
                {
                    it->next=p2;
                    it=it->next;
                }
                p2=p2->next;
            }
        }

        if(p1==nullptr)
            (it==nullptr)?ans=p2:it->next=p2;
        else
            (it==nullptr)?ans=p1:it->next=p1;
        
        list=ans;
        p=nullptr;
    }

    ListNode* dfs(int l,int r,vector<ListNode*>&lists)
    {
        if(l>r)return nullptr;
        if(l==r)return lists[l];

        int mid=l+r>>1;
        ListNode*left=dfs(l,mid,lists);
        ListNode*right=dfs(mid+1,r,lists);
        merge(left,right);
        return left;
    }
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        return dfs(0,lists.size()-1,lists);
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
