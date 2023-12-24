#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>

#define ll long long

using namespace std;

class Solution {
public:
    int lengthOfLastWord(string s) {
        int i=s.size()-1,ans=0;

        while(i>=0&&s[i]==' ')
            --i;
        
        while(i>=0&&s[i--]!=' ')
            ++ans;
        
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
