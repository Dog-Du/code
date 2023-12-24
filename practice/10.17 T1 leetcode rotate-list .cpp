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
    ListNode* rotateRight(ListNode* head, int k) {

        if(head==NULL||head->next==NULL
        ||k==0)return head;

        int len=0;
        ListNode*p=head;

        while(p)
        {
            p=p->next;
            ++len;
        }

        k%=len;

        if(k==0)return head;

        ListNode*slow=head,*fast=head,*slow_pre=NULL,*fast_pre=NULL,*ans;

        while(k--)
        {
            fast_pre=fast;
            fast=fast->next;
        }

        while(fast)
        {
            slow_pre=slow;
            fast_pre=fast;
            slow=slow->next;
            fast=fast->next;
        }

        ans=slow;
        slow_pre->next=NULL;
        
        fast_pre->next=head;

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
