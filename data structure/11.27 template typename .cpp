#include <iostream>
using namespace std;

template<typename Type> //使用模板类型，跟契合stl
class stack{
private:
    size_t Size;

    struct StackNode{
        Type key;
        StackNode*next;
    }*head;


public:
    stack(){
        head=nullptr;
        Size=0;
    }
    
    ~stack<Type>(){//检验析构函数被调用
        clear();
        cout<<"~stack is working"<<endl;
        head=nullptr;
        Size=0;
    }


    void swap(stack<Type>& it)//只需要交换 Size和头指针
    {
        swap(it.Size,this.Size);
        swap(it.head,this.head);
    }

    void clear(){//清空，
        StackNode*temp=head,*now=head;
        
        while(now!=nullptr)
        {
            temp=now->next;
            delete now;
            now=temp;
        }

        head=nullptr;//注意置空
        Size=0;
    }

    void push(Type key)//头插法
    {
        StackNode*newnode=new StackNode;
        newnode->key=move(key);
        newnode->next=head;
        head=newnode;//头指针改成新节点
        ++Size;
        return;
    }

    void pop()//删除
    {
        StackNode*temp=head;
        head=head->next;
        delete temp;//删除
        --Size;
        return;
    }

    int size(){
        return Size;
    }
    bool empty(){
        return Size==0;
    }

    //对照stl库发现，栈的top函数实际上是可以被修改的，也就是说返回的是一个左值，因此返回引用
    Type &top(){//如果空，不应该返回随机值，应该报错才对。返回值用引用型左值
        if(head==nullptr)raise;//如果head为空，应该报错，不应该返回值
        return head->key;
    }
};

//在函数中使用，随便检验析构函数
void solve()
{
    stack<int> st;//模板类
    int c=11;
    
    // int t;
    // cin>>t;
    cout<<c<<endl;
    delete &st;

    // while(t--)
    // {
    //     int op,x;
    //     cin>>op;

    //     if(op==1)//插入
    //     {
    //         cin>>x;
    //         st.push(x);
    //     }
    //     else if(op==2)//删除
    //     {
    //         if(st.empty())cout<<"now is empty"<<endl;
    //         else
    //             st.pop();
    //     }
    //     else if(op==3)//输出栈顶
    //     {
    //         if(st.empty())cout<<"now is empty"<<endl;
    //         else
    //             cout<<"top=="<<st.top()<<endl;
    //     }
    //     else if(op==4)//输出大小
    //     {
    //         cout<<"size=="<<st.size()<<endl;
    //     }
    //     else if(op==5)//判断空否
    //     {
    //         cout<<st.empty()<<endl;
    //     }
    //     else if(op==6)//调用情况函数
    //     {
    //         st.clear();
    //         cout<<"stack have been cleared"<<endl;
    //     }
    //     else if(op==7)//修改栈顶
    //     {
    //         cin>>x;

    //         if(st.empty())cout<<"now is empty"<<endl;
    //         else
    //             st.top()=x;
    //     }
    // }

    
}

int main()
{

    solve();

    cout<<endl;
    system("pause");
    return 0;
}
