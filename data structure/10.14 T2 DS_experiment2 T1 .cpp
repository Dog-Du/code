#include <iostream>
#include <cstring>

using namespace std;

const int MAXSIZE=1e4+10;

void solve()
{
    char ch[MAXSIZE];
    char oper[MAXSIZE];
    char it[MAXSIZE];

    cin>>ch;

    int len=strlen(ch);
    int size=0,p=0;

    for(int i=0;i<len;++i)
    {
        bool flag=0;

        while((ch[i]>='0'&&ch[i]<='9')||
            (ch[i]>='a'&&ch[i]<='z')||
            (ch[i]>='A'&&ch[i]<='Z'))
        {
            it[p++]=ch[i++];
            flag=1;
        }

        if(flag)it[p++]='#';

        if(ch[i]=='(')
        {
            oper[size++]='(';
        }
        else if(ch[i]==')')
        {
            while(size>0&&oper[size-1]!='(')
            {
                it[p++]=oper[size-1];
                --size;
            }
            --size;
        }
        else if(ch[i]=='-'||ch[i]=='+')
        {
            while(size>0&&oper[size-1]!='(')
            {
                it[p++]=oper[--size];
            }

            oper[size++]=ch[i];
        }
        else if(ch[i]=='*'||ch[i]=='/'||ch[i]=='%')
        {
            while(size>0&&
            (oper[size-1]=='*'||oper[size-1]=='/'||oper[size-1]=='%'))
            {
                it[p++]=oper[--size];
            }

            oper[size++]=ch[i];
        }
    }

    while(size>=0)
        it[p++]=oper[size--];

    for(int i=0;i<p;++i)
        if(it[i]!='(')
            cout<< it[i];

    cout<<endl;
    size=0;
    int num[MAXSIZE];
    int t=0;

    for(int i=0;i<p;++i)
    {
        int temp=0,flag=0;

        while(it[i]>='0'&&it[i]<='9')
        {
            temp=temp*10+it[i++]-'0';
            flag=1;
        }

     //   6 9 + 19 9 5 * + + 100 -

        if(flag)num[t++]=temp;

        if(it[i]=='+')
        {
            int num2=num[t-1];
            --t;
            int num1=num[t-1];
            --t;
            num[t++]=num1+num2;
        }
        else if(it[i]=='-')
        {
            int num2=num[t-1];
            --t;
            int num1=num[t-1];
            --t;
            num[t++]=num1-num2;            
        }
        else if(it[i]=='/')
        {
            int num2=num[t-1];
            --t;
            int num1=num[t-1];
            --t;
            num[t++]=num1/num2;
        }
        else if(it[i]=='*')
        {
            int num2=num[t-1];
            --t;
            int num1=num[t-1];
            --t;
            num[t++]=num1*num2;            
        }
        else if(it[i]=='%')
        {
            int num2=num[t-1];
            --t;
            int num1=num[t-1];
            --t;
            num[t++]=num1%num2;
        }
    }

    cout<<num[t-1]<<endl;
}

int main()
{
    int t;
    cin>>t;

    while(t--)
    {
        solve();
    }

    cout<<endl;
    system("pause");
    return 0;
}
