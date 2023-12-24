// #include <iostream>
// #include <cmath>
// #include <string>
// #include <cstring>
// #include <vector>
// #include <algorithm>

// #define ll long long

// using namespace std;

// void get_next(string & s,int next[])
// {
//     int i=0,j=-1,n=s.size();
//     next[0]=-1;

//     while(i<n)
//     {
//         if(j==-1||s[i]==s[j])
//             next[++i]=++j;
//         else
//             j=next[j];
//     }

//     for(int i=0;i<n;++i)
//         cout<<next[i]<<' ';
//     cout<<endl;
// }

// int search(string & s,string & t)
// {
//     int i=0,j=0,n=s.size(),m=t.size();

//     int *next=new int[n];

//     get_next(t,next);

//     while(i<n&&j<m)
//     {
//         if(j==-1||s[i]==t[j])
//             ++i,++j;
//         else
//             j=next[j];
//     }

//     delete [] next;

//     if(j>=m)return i-j;
//     return -1;
// }

// int main()
// {
//     ios::sync_with_stdio(false);
//     cin.tie(0),cout.tie(0);

//     int n;

//     string s;

//     cin>>n>>s;

//     while(n--)
//     {
//         string t;
//         cin>>t;

//         cout<<search(s,t)<<endl;
//     }


//     cout<<endl;
//     system("pause");
//     return 0;
// }
