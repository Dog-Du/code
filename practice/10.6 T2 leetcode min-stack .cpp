#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
#include <stack>

#define ll long long

using namespace std;

class MinStack {
public:

    stack<int> st,minstack;

    MinStack() {
        
    }
    
    void push(int val) {
        st.push(val);

        if(minstack.empty()||val<=minstack.top())
            minstack.push(val);
    }
    
    void pop() {

        if(minstack.top()==st.top())
            minstack.pop();
        
        st.pop();
    }
    
    int top() {
        return st.top();
    }
    
    int getMin() {
        return minstack.top();
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
