// #include <iostream>
// #include <cmath>
// #include <string>
// #include <cstring>
// #include <vector>
// #include <algorithm>

// #define ll long long

// using namespace std;

// const int maxn=1e6+10;

// string s1,s2;
// int Next[maxn];

// void getnext(string & s,int next[])
// {
//     int i=0,j=-1,n=s.size();
//     next[0]=-1;

//     while(i<=n)
//     {
//         if(j==-1||s[i]==s[j])
//             next[++i]=++j;
//         else
//             j=next[j];
//     }
// }

// int search(string &s,string & t,int pos,int next[])
// {
//     int i=pos,j=0,n=s.size(),m=t.size();

//     while(i<n&&j<m)
//     {
//         if(j==-1||s[i]==t[j])
//             ++i,++j;
//         else
//             j=next[j];
//     }

//     if(j>=m)return i-j;
//     return -1;
// }

// int main()
// {
//     ios::sync_with_stdio(false);
//     cin.tie(0),cout.tie(0);

//     cin>>s1>>s2;

//     int pos=-1; 

//     getnext(s2,Next);

//     while((pos=search(s1,s2,pos+1,Next))!=-1)
//         cout<<pos+1<<'\n';

//     for(int i=1,n=s2.size();i<=n;++i)
//         cout<<Next[i]<<' ';

//     cout<<endl;
//     system("pause");
//     return 0;
// }
