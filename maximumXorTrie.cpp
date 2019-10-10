#include<iostream>
#include<vector>
#include<math.h>

// Very interesting problem and solution

class BTNode
{
    public:
    BTNode* child[2]{nullptr, nullptr};
    bool isEnd{true};
};
BTNode* newNode()
{
    BTNode* t = new BTNode;
    t->child[0] = nullptr;
    t->child[1] = nullptr;
    t->isEnd = false;
    return t;
}
void insert(BTNode* root, int value)
{
    BTNode* temp = root;
    int index = 0;
    int counter = 0;
    for(int i = 31; i >= 0; --i)
    {
        BTNode* t = newNode();
        ++counter;
        if(value & (1 << i))
        {
            index = 1;
        }
        else
        {
            index = 0;
        }
        if(temp->child[index] == nullptr)
        {
            temp->child[index] = t;
        }
        temp = temp->child[index];
    }
    temp->isEnd = true;
}
int searchBinaryTrie(BTNode* root, int q)
{
    int index = 0;
    int index_ = 0;
    int value = 0;
    BTNode* temp = root;
    for(int i = 31; i >= 0; --i)
    {
        if(q & (1 << i))
        {
            index = 1;
        }
        else
        {
            index = 0;
        }
        index_ = (index + 1) % 2;
        // Go to opposite child to find max xor
        if(temp->child[index_] != nullptr && temp->isEnd == false)
        {
            value += pow(2, i);    
            temp = temp->child[index_];
        }
        else
        {
            temp = temp->child[index];
        }
    }
    return value;
}
int findMaxXor(const std::vector<int>& vec, int q)
{
    BTNode* root = newNode(); 
    for(const auto v:vec)
    {
        insert(root, v);
    }
    int max = 0; 
    max = searchBinaryTrie(root, q);
    return max;
}
int main()
{
    std::vector<int> vec{0, 1, 2};
    int q = 2;
    return 0;
}
