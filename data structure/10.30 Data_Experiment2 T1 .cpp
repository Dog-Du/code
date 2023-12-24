#include <iostream>
#include <cstring>

using namespace std;

const int MAXSIZE = 1e4 + 10;

void solve()
{
    char ch[MAXSIZE] = {0};   // 存储原字符串
    char oper[MAXSIZE] = {0}; // 存储运算符的栈
    char it[MAXSIZE] = {0};   // 存储后缀表达式

    cout << "please input your biaodashi:" << endl;
    cin >> ch;

    int len = strlen(ch); // 算术表达式的长度
    int size = 0, p = 0;  // size是运算符的栈的大小，p是后缀表达式的长度

    // 转化成后缀表达式
    for (int i = 0; i < len; ++i)
    {
        bool flag = 0; // 标记是否是数字

        while ((ch[i] >= '0' && ch[i] <= '9') ||
               (ch[i] >= 'a' && ch[i] <= 'z') ||
               (ch[i] >= 'A' && ch[i] <= 'Z'))
        {
            it[p++] = ch[i++];
            flag = 1;
        }

        if (flag)
            it[p++] = '#'; // 是数字则分割

        if (ch[i] == '(')
        {
            oper[size++] = '(';
        }
        else if (ch[i] == ')')
        {
            while (size > 0 && oper[size - 1] != '(')
            {
                it[p++] = oper[size - 1];
                --size;
            }
            --size;
        }
        else if (ch[i] == '-' || ch[i] == '+')
        {
            while (size > 0 && oper[size - 1] != '(')
            {
                it[p++] = oper[--size];
            }

            oper[size++] = ch[i];
        }
        else if (ch[i] == '*' || ch[i] == '/' || ch[i] == '%')
        {
            while (size > 0 &&
                   (oper[size - 1] == '*' || oper[size - 1] == '/' || oper[size - 1] == '%'))
            {
                it[p++] = oper[--size];
            }

            oper[size++] = ch[i];
        }
    }

    while (size > 0) // 把运算符栈剩余运算符全部倒入后缀表达式中
        it[p++] = oper[--size];

    // 输出后缀表达式
    for (int i = 0; i < p; ++i)
        if (it[i] != '(')
            cout << it[i];

    cout << endl;

    size = 0;               // 运算符栈清空
    int num[MAXSIZE] = {0}; // 数字栈
    int t = 0;              // 数字栈的大小
    int num1, num2;         // 用来存储弹出时的两个数字

    for (int i = 0; i < p; ++i)
    {
        int temp = 0, flag = 0; // 判断是否是数字

        while (it[i] >= '0' && it[i] <= '9')
        {
            temp = temp * 10 + it[i++] - '0';
            flag = 1;
        }

        //   6 9 + 19 9 5 * + + 100 -

        if (flag)
            num[t++] = temp; // 如果是数字压入数字栈中

        // 如果是运算符，取出数字
        if (it[i] == '+' || it[i] == '-' || it[i] == '*' || it[i] == '/' || it[i] == '%')
        {
            num2 = num[t - 1];
            --t;
            num1 = num[t - 1];
            --t;
        }

        // 运算并压入
        if (it[i] == '+')
        {
            num[t++] = num1 + num2;
        }
        else if (it[i] == '-')
        {
            num[t++] = num1 - num2;
        }
        else if (it[i] == '/')
        {
            num[t++] = num1 / num2;
        }
        else if (it[i] == '*')
        {
            num[t++] = num1 * num2;
        }
        else if (it[i] == '%')
        {
            num[t++] = num1 % num2;
        }
    }

    cout << num[t - 1] << endl; // 输出结果
}

int main()
{
    cout << "please how many do you want to test :" << endl;

    int t;
    cin >> t;

    while (t--)
    {
        solve();
    }

    cout << endl;
    system("pause");
    return 0;
}

//     for(int i=0;i<len;)
// {
//     switch (ch[i])
//     {
//     case '(':
//         oper[size++]=ch[i++];
//         break;
//     case ')':
//         while(size>0&&oper[size-1]!='(')
//         {
//             it[p++]=oper[size-1];
//             --size;
//         }
//         ++i;
//         break;
//     case '+':
//     case '-':
//         while(size>0&&oper[size-1]!='(')
//         {
//             it[p++]=oper[--size];
//         }
//         oper[size++]=ch[i++];
//         break;
//     case '*':
//     case '/':
//     case '%':
//         while(size>0&&(oper[size-1]=='*'||oper[size-1]=='/'||oper[size-1]=='%'))
//         {
//             it[p++]=ch[size-1];
//             --size;
//         }
//         oper[size++]=ch[i++];

//     default:
//         while(ch[i]>='0'&&ch[i]<='9')
//         {
//             it[p++]=ch[i++];
//         }
//         it[p++]='#';
//     }
// }
