#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int read()
{
    int x;
    scanf("%d", &x);
    return x;
}

void strswap(char a[], char b[])
{
    char temp[100];
    strncpy(temp,a,90);
    strncpy(a,b,90);
    strncpy(b,temp,90);
}

void intswap(int *x,int *y)
{
    int temp=*x;
    *x=*y;
    *y=temp;
}

void fun(char *s,char c)
{
    int len=strlen(s);
    int l,r;

    for(l=0,r=0;r<len;++r)
    {
        if(s[r]!=c)
            s[l++]=s[r];
    }

    if(l==r)
        printf("%c not exist in\n",c);

    for(int i=0;i<l;++i)
        putchar(s[i]);
}

int countfreq(char *t,char p)
{
    int len=strlen(t);

    int ans=0;
    for(int i=0;i<len;++i)
        if(*(t+i)==p)
            ++ans;
    
    return ans;
}

int main()
{

    system("pause");
    return 0;
}