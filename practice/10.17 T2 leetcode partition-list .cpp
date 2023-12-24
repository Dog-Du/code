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
public:
    ListNode* partition(ListNode* head, int x) {
        if(head==NULL||head->next==NULL)return head;

        ListNode*p1=NULL,*p2=NULL,*ans=NULL,*p=head,*t=NULL;

        while(p)
        {
            if(p->val>=x)
            {
                if(!p2)
                {
                    p2=p;
                    t=p2;
                }
                else
                {
                    p2->next=p;
                    p2=p2->next;
                }
            }
            else
            {
                if(!p1)
                {
                    p1=p;
                    ans=p1;
                }
                else
                {
                    p1->next=p;
                    p1=p1->next;
                }
            }

            p=p->next;
        }

        if(p2)
            p2->next=NULL;//防止无限循环
        
        if(p1)
            p1->next=t;
        
        //如果ans不为空，返回它，不然返回t
        return (ans==NULL)?t:ans;
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
