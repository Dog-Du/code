#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
#include <stack>

#define ll long long

using namespace std;

 struct ListNode {
      int val;
      ListNode *next;
      ListNode() : val(0), next(nullptr) {}
      ListNode(int x) : val(x), next(nullptr) {}
      ListNode(int x, ListNode *next) : val(x), next(next) {}
  };
 
void init(ListNode*&head)
{
    int n;
    cin>>n;
    
    head=new ListNode(0,nullptr);
    ListNode* p=head;

    while(n--)
    {
        int x;
        cin>>x;
        head->next=new ListNode(x,nullptr);
        head=head->next;
    }

    head=p->next;
    delete p;
}

class Solution {
public:
    ListNode* removeNodes(ListNode* head) {
        if(head==nullptr||head->next==nullptr)return head;
        stack<ListNode*> st;
        st.push(head);
        ListNode*p=head->next;

        while(p!=nullptr)
        {
            while(!st.empty()&&st.top()->val<p->val)
            {
                ListNode*tmp=st.top();
                st.pop();

                if(!st.empty())
                    st.top()->next=p;
                    
                //delete tmp;
            }

            st.push(p);
            p=p->next;
        }

        while(st.size()>1)
            st.pop();
        
        return st.top();
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);

    ListNode*head;
    init(head);

    Solution one;
    one.removeNodes(head);


    cout<<endl;
    system("pause");
    return 0;
}
