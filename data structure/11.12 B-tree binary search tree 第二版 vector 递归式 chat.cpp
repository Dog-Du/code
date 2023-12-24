#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX_KEYS = 4; // B 树的阶数

// B 树节点
struct BTreeNode {
    std::vector<int> keys; // 关键字
    std::vector<BTreeNode*> children; // 子节点
    bool isLeaf; // 是否为叶子节点

    BTreeNode(bool leaf = true) : isLeaf(leaf) {}
};

class BTree {
private:
    BTreeNode* root;

    // 辅助函数
    void insertNonFull(BTreeNode* node, int key);
    void splitChild(BTreeNode* parent, int index);
    void remove(BTreeNode* node, int key);
    void removeFromLeaf(BTreeNode* node, int key);
    void removeFromNonLeaf(BTreeNode* node, int key);
    int getPred(BTreeNode* node, int index);
    int getSucc(BTreeNode* node, int index);
    void fillChild(BTreeNode* node, int index);
    void borrowFromPrev(BTreeNode* node, int index);
    void borrowFromNext(BTreeNode* node, int index);
    void merge(BTreeNode* node, int index);

public:
    BTree() : root(nullptr) {}
    ~BTree();

    void insert(int key);
    void remove(int key);
    bool search(int key);
    void traverse();
};

// 构造函数
BTree::~BTree() {
    // 释放内存
}

// 插入关键字
void BTree::insert(int key) {
    if (root == nullptr) {
        root = new BTreeNode(true);
        root->keys.push_back(key);
    } else {
        if (root->keys.size() == MAX_KEYS) {
            BTreeNode* newRoot = new BTreeNode(false);
            newRoot->children.push_back(root);
            splitChild(newRoot, 0);
            root = newRoot;
        }
        insertNonFull(root, key);
    }
}

// 在非满节点插入关键字
void BTree::insertNonFull(BTreeNode* node, int key) {
    int i = node->keys.size() - 1;
    if (node->isLeaf) {
        node->keys.push_back(0); // 扩展数组
        while (i >= 0 && key < node->keys[i]) {
            node->keys[i + 1] = node->keys[i];
            i--;
        }
        node->keys[i + 1] = key;
    } else {
        while (i >= 0 && key < node->keys[i]) {
            i--;
        }
        i++;
        if (node->children[i]->keys.size() == MAX_KEYS) {
            splitChild(node, i);
            if (key > node->keys[i])
                i++;
        }
        insertNonFull(node->children[i], key);
    }
}

// 分裂子节点
void BTree::splitChild(BTreeNode* parent, int index) {
    BTreeNode* child = parent->children[index];
    BTreeNode* newChild = new BTreeNode(child->isLeaf);
    parent->keys.insert(parent->keys.begin() + index, child->keys[MAX_KEYS / 2]);
    parent->children.insert(parent->children.begin() + index + 1, newChild);

    newChild->keys.assign(child->keys.begin() + MAX_KEYS / 2 + 1, child->keys.end());
    child->keys.resize(MAX_KEYS / 2);

    if (!child->isLeaf) {
        newChild->children.assign(child->children.begin() + MAX_KEYS / 2 + 1, child->children.end());
        child->children.resize(MAX_KEYS / 2 + 1);
    }
}

// 删除关键字
void BTree::remove(int key) {
    if (root == nullptr) {
        std::cout << "BTree is empty\n";
        return;
    }

    remove(root, key);

    // 如果根节点只有一个子节点，则使根节点的子节点成为新的根节点
    if (root->keys.empty() && !root->isLeaf) {
        BTreeNode* newRoot = root->children[0];
        delete root;
        root = newRoot;
    }
}

// 从节点中删除关键字
void BTree::remove(BTreeNode* node, int key) {
    int index = 0;
    while (index < node->keys.size() && key > node->keys[index]) {
        index++;
    }

    if (index < node->keys.size() && key == node->keys[index]) {
        if (node->isLeaf) {
            removeFromLeaf(node, index);
        } else {
            removeFromNonLeaf(node, index);
        }
    } else {
        if (node->isLeaf) {
            std::cout << "Key " << key << " not found in the tree\n";
            return;
        }
        bool flag = (index == node->keys.size());
        if (node->children[index]->keys.size() < MAX_KEYS) {
            fillChild(node, index);
        }
        if (flag && index > node->keys.size()) {
            remove(node->children[index - 1], key);
        } else {
            remove(node->children[index], key);
        }
    }
}

// 从叶子节点中删除关键字
void BTree::removeFromLeaf(BTreeNode* node, int index) {
    node->keys.erase(node->keys.begin() + index);
}

// 从非叶子节点中删除关键字
void BTree::removeFromNonLeaf(BTreeNode* node, int index) {
    int key = node->keys[index];
    if (node->children[index]->keys.size() >= MAX_KEYS) {
        int pred = getPred(node, index);
        node->keys[index] = pred;
        remove(node->children[index], pred);
    } else if (node->children[index + 1]->keys.size() >= MAX_KEYS) {
        int succ = getSucc(node, index);
        node->keys[index] = succ;
        remove(node->children[index + 1], succ);
    } else {
        merge(node, index);
        remove(node->children[index], key);
    }
}

// 获取前驱关键字
int BTree::getPred(BTreeNode* node, int index) {
    BTreeNode* curr = node->children[index];
    while (!curr->isLeaf) {
        curr = curr->children.back();
    }
    return curr->keys.back();
}

// 获取后继关键字
int BTree::getSucc(BTreeNode* node, int index) {
    BTreeNode* curr = node->children[index + 1];
    while (!curr->isLeaf) {
        curr = curr->children[0];
    }
    return curr->keys[0];
}

// 填充子节点
void BTree::fillChild(BTreeNode* node, int index) {
    if (index != 0 && node->children[index - 1]->keys.size() >= MAX_KEYS) {
        borrowFromPrev(node, index);
    } else if (index != node->keys.size() && node->children[index + 1]->keys.size() >= MAX_KEYS) {
        borrowFromNext(node, index);
    } else {
        if (index != node->keys.size()) {
            merge(node, index);
        } else {
            merge(node, index - 1);
        }
    }
}

// 从前一个子节点借关键字
void BTree::borrowFromPrev(BTreeNode* node, int index) {
    BTreeNode* child = node->children[index];
    BTreeNode* sibling = node->children[index - 1];

    // 将父节点的关键字移动到 child 的开头
    child->keys.insert(child->keys.begin(), node->keys[index - 1]);
    // 如果 sibling 不是叶子节点，则将其最右边的子节点移到 child 的最左边
    if (!sibling->isLeaf) {
        child->children.insert(child->children.begin(), sibling->children.back());
        sibling->children.pop_back();
    }
    // 更新父节点的关键字
    node->keys[index - 1] = sibling->keys.back();
    // 移除 sibling 的最右边的关键字
    sibling->keys.pop_back();
}

// 从后一个子节点借关键字
void BTree::borrowFromNext(BTreeNode* node, int index) {
    BTreeNode* child = node->children[index];
    BTreeNode* sibling = node->children[index + 1];

    // 将父节点的关键字移动到 child 的末尾
    child->keys.push_back(node->keys[index]);
    // 如果 sibling 不是叶子节点，则将其最左边的子节点移到 child 的最右边
    if (!sibling->isLeaf) {
        child->children.push_back(sibling->children.front());
        sibling->children.erase(sibling->children.begin());
    }
    // 更新父节点的关键字
    node->keys[index] = sibling->keys.front();
    // 移除 sibling 的最左边的关键字
    sibling->keys.erase(sibling->keys.begin());
}

// 合并子节点
void BTree::merge(BTreeNode* node, int index) {
    BTreeNode* child = node->children[index];
    BTreeNode* sibling = node->children[index + 1];

    // 将父节点的关键字移到 child 的末尾
    child->keys.push_back(node->keys[index]);
    // 将 sibling 的关键字复制到 child 的末尾
    child->keys.insert(child->keys.end(), sibling->keys.begin(), sibling->keys.end());
    // 如果 sibling 不是叶子节点，则将其子节点复制到 child 的末尾
    if (!sibling->isLeaf) {
        child->children.insert(child->children.end(), sibling->children.begin(), sibling->children.end());
    }
    // 从父节点移除关键字和指向 sibling 的指针
    node->keys.erase(node->keys.begin() + index);
    node->children.erase(node->children.begin() + index + 1);
    // 释放 sibling 的内存
    delete sibling;
}

// 查找关键字
bool BTree::search(int key) {
    if (root == nullptr) {
        return false;
    }
    BTreeNode* current = root;
    while (current != nullptr) {
        int i = 0;
        while (i < current->keys.size() && key > current->keys[i]) {
            i++;
        }
        if (i < current->keys.size() && key == current->keys[i]) {
            return true;
        } else if (current->isLeaf) {
            return false;
        } else {
            current = current->children[i];
        }
    }
    return false;
}

// 中序遍历
void inOrderTraversal(BTreeNode* node) {
    if (node != nullptr) {
        int i;
        for (i = 0; i < node->keys.size(); i++) {
            if (!node->isLeaf) {
                inOrderTraversal(node->children[i]);
            }
            std::cout << node->keys[i] << " ";
        }
        if (!node->isLeaf) {
            inOrderTraversal(node->children[i]);
        }
    }
}

// 遍历 B 树
void BTree::traverse() {
    if (root != nullptr) {
        inOrderTraversal(root);
    }
    std::cout << std::endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    
    BTree btree;
    int n;
    cin>>n;
    int a[n+1];

    for(int i=1;i<=n;++i)
    {
        cin>>a[i];
        btree.insert(a[i]);
    }

    sort(a+1,a+1+n);

    for(int i=1;i<=n;++i)
    {
        if(btree.search(a[i]))
            cout<<a[i]<<' ';
        btree.remove(a[i]);
    }

    cout<<endl;
    system("pause");
    return 0;
}
