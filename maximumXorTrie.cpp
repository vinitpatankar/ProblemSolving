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
    std::cout << "Inserting " << value << '\n';
    int index = 0;
    int counter = 0;
    for(int i = 31; i >= 0; --i)
    {
        BTNode* t = newNode();
        std::cout << "Inside loop: temp = " << temp << ", t = " << t << '\n';
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
    std::cout << "Inserted " << counter << " nodes" << '\n';
    std::cout << "Root before end of insertion = " << root << ", root->child[0] = " << root->child[0] << ", root->child[1] = " << root->child[1] << ", root->isEnd = " << root->isEnd << '\n' << std::flush;
    temp->isEnd = true;
}
int searchBinaryTrie(BTNode* root, int q)
{
    int index = 0;
    int index_ = 0;
    int value = 0;
    //std::cout << "Root here = " << root << ", root->child[0] = " << root->child[0] << ", root->child[1] = " << root->child[1] << ", root->isEnd = " << root->isEnd << '\n' << std::flush;
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
        std::cout << "i = " << i << ", index = " << index << ", index_ = " << index_ << ", value = " << value << '\n';
        std::cout << "temp->child[" << index_ << "]=" << temp->child[index_] << ", temp->isEnd = " << temp->isEnd << '\n';
        if(temp->child[index_] != nullptr && temp->isEnd == false)
        {
            std::cout << "Found " << index_ << " hence going opposite direction" << '\n';
            value += pow(2, i);    
            temp = temp->child[index_];
        }
        else
        {
            std::cout << "temp = " << temp << '\n';
            temp = temp->child[index];
        }
    }
    return value;
}
int findMaxXor(const std::vector<int>& vec, int q)
{
    BTNode* root = newNode(); 
    std::cout << "Root = " << root << " created: root->child[0] = " << root->child[0] << ", root->child[1] = " << root->child[1] << ", root->isEnd = " << root->isEnd << '\n' << std::flush;
    for(const auto v:vec)
    {
        insert(root, v);
    }
    std::cout << "Insertion complete" << '\n' << std::flush;
    std::cout << "Root = " << root << ", root->child[0] = " << root->child[0] << ", root->child[1] = " << root->child[1] << ", root->isEnd = " << root->isEnd << '\n' << std::flush;
    int max = 0; 
    max = searchBinaryTrie(root, q);
    return max;
}
int main()
{
    std::vector<int> vec{0, 1, 2};
    int q = 2;
    std::cout << findMaxXor(vec, q) << '\n';
    return 0;
}
