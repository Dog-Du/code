#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>

#define ll long long

using namespace std;

class Solution
{
public:
    bool memory[205][205] = {0}; // s1前i个，s2前j个能否表示s3前i+j个

    void dfs(int i, int p1, int p2, string &s1, string &s2, string &s3)
    {
        if (p1 == s1.size() && p2 == s2.size())
        {
            memory[p1][p2] = true;
            return;
        }

        if (memory[p1][p2])
            return;

        if (s1[p1] != s3[i] && s2[p2] != s3[i])
            return;

        memory[p1][p2] = true;

        if (s1[p1] == s3[i])
            dfs(i + 1, p1 + 1, p2, s1, s2, s3);
        if (s2[p2] == s3[i])
            dfs(i + 1, p1, p2 + 1, s1, s2, s3);
    }

    bool isInterleave(string s1, string s2, string s3)
    {
        if (s3.size() == 0)
            return true;
        if (s3.size() != s1.size() + s2.size())
            return false;

        dfs(0, 0, 0, s1, s2, s3);
        return memory[s1.size()][s2.size()];
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cout << endl;
    system("pause");
    return 0;
}
