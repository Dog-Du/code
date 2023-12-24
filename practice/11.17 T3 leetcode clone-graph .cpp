#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <queue>
#include <vector>
#include <algorithm>

#define ll long long

using namespace std;

class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};


class Solution {
public:
    vector<Node*> vec;//有一个哈希

    void dfs(Node*&now,Node*&node)
    {
        if(vec[node->val]!=nullptr)
        {
            now=vec[node->val];
            return;
        }
        now=new Node(node->val);
        vec[node->val]=now;//标记
        for(auto&iter:node->neighbors)
        {
            now->neighbors.push_back(nullptr);
            dfs(now->neighbors.back(),iter);
        }
    }

    Node* cloneGraph(Node* node) {
        if(node==nullptr)return nullptr;
        vec.resize(110,nullptr);
        Node*ans=nullptr;
        dfs(ans,node);
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
