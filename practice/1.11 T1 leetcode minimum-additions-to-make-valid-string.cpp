#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>

#define ll long long

using namespace std;

class Solution {
private:
    int check(int &i,string&word)
    {
        if(word[i]=='a'&&word[i+1]=='b'&&word[i+2]=='c')
        {
            i+=3;
            return 0;
        }
        else if(word[i]=='a'&&word[i+1]=='c')
        {
            i+=2;
            return 1;
        }
        else if(word[i]=='a'&&word[i+1]=='b')
        {
            i+=2;
            return 1;
        }
        else if(word[i]=='a')
        {
            i+=1;
            return 2;
        }
        else if(word[i]=='b'&&word[i+1]=='c')
        {
            i+=2;
            return 1;
        }
        else if(word[i]=='b')
        {
            i+=1;
            return 2;
        }
        else if(word[i]=='c')
        {
            i+=1;
            return 2;
        }
        return 0;
    }
public:
    int addMinimum(string word) {
        int ans=0;
        for(int i=0,n=word.size();i<n;)
        {
            ans+=check(i,word);
        }
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
