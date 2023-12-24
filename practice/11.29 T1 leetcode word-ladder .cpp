#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
#include <queue>
#include <unordered_map>
#include <unordered_set>

#define ll long long

using namespace std;

//暴力方法二
class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> words(wordList.begin(),wordList.end());
        queue<pair<string,int>> que;
        que.push({beginWord,1});
        pair<string,int> j;
        int len=beginWord.size();

        while(!que.empty())
        {
            j=que.front();
            que.pop();

            if((j.first)==endWord)return j.second;

            for(int i=0;i<len;++i)
            {
                for(char k='a',t=j.first[i];k<='z';++k)
                {
                    j.first[i]=k;

                    if(!words.count(j.first))
                    {
                        j.first[i]=t;
                        continue;
                    }

                    que.push({j.first,j.second+1});
                    words.erase(words.find(j.first));

                    j.first[i]=t;
                }
            }
        }

        return 0;
    }
};

// //暴力方法一
// class Solution {
// private:
//     int n,len;

//     void getnext(string&s,vector<string> &bank,vector<int>&vec,vector<bool>&used)
//     {
//         for(int i=0,cnt;i<n;++i)
//         {
//             if(used[i])continue;
//             cnt=0;
//             for(int j=0;j<len;++j)
//                 if(s[j]!=bank[i][j])++cnt;
            
//             if(cnt==1)vec.push_back(i);
//         }
//     }

// public:

//     int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
//         queue<pair<string*,int>> que;
//         que.push({&beginWord,1});
//         n=wordList.size();
//         len=beginWord.size();
//         vector<int> vec;
//         vector<bool> used(n,0);

//         pair<string*,int> j;

//         while(!que.empty())
//         {
//             j=que.front();
//             que.pop();

//             if((*j.first)==endWord)return j.second;

//             vec.clear();
//             getnext(*j.first,wordList,vec,used);

//             for(auto&it:vec)
//             {
//                 if(wordList[it]=="Q")continue;
//                 que.push({&wordList[it],j.second+1});
//                 used[it]=1;
//             }
//         }

//         return 0;
//     }
// };

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);

    string beginWord="hit",endWord="cog";
    vector<string> wordList = {"hot","dot","dog","lot","log","cog"};
    
    Solution one;
    one.ladderLength(beginWord,endWord,wordList);

    cout<<endl;
    system("pause");
    return 0;
}
