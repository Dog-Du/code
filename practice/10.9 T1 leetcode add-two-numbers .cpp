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
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {

        ListNode * ans=new ListNode,* p=ans,* p1=l1,*p2 = l2;
        ans->next=NULL;

        int temp=0;

        while(p1&&p2)
        {
            p->val=(p1->val+p2->val+temp)%10;

            if(p1->val+p2->val+temp>=10)temp=1;
            else temp=0;

            if(p1->next&&p2->next)
            {  
                p->next=new ListNode;
                p=p->next;
            }

            p1=p1->next;
            p2=p2->next;
        }

        p->next=NULL;

        if(p2&&!p1)
        {
            p1=p2;
            p->next=new ListNode;
            p=p->next;
        }
        else if(p1)
        {
            p->next=new ListNode;
            p=p->next;
        }

        while(p1)
        {
            p->val=(p1->val+temp)%10;

            if(p1->val+temp>=10)temp=1;
            else temp=0;

            if(p1->next)
            {
                p->next=new ListNode;
                p=p->next;
            }

            p1=p1->next;
        }

        if(temp)
        {
            p->next=new ListNode;
            p=p->next;
            p->next=NULL;
            p->val=1;
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
