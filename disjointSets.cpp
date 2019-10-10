#include<iostream>
#include<map>
#include<vector>

typedef std::vector<std::vector<int>> Graph;
class DisjointSet
{
    std::size_t max{0};
    struct Node
    {
        Node* parent{nullptr};
        int rank{0};
        int members{0};
        int id{0};
    };
    std::map<int, Node*> idMap;
    void makeSet(int id)
    {
        Node* p = new Node;
        p->parent = p;
        p->rank = 0;
        p->members = 1;
        p->id = id;
        idMap[id] = p;
    }
    Node* findParent(Node* n)
    {
        if(n->parent == n) return n;
        n->parent = findParent(n->parent);
        return n->parent;
    }
    public:
    int getMax() const
    {
        return max;
    }
    void doUnion(int id1, int id2)
    {
        if(idMap.count(id1) == 0) makeSet(id1);
        if(idMap.count(id2) == 0) makeSet(id2);
        Node* parent1 = findParent(idMap[id1]);
        Node* parent2 = findParent(idMap[id2]);
        if(parent1 == parent2) return; 
        if(parent1->rank >= parent2->rank)
        {
            if(parent1->rank == parent2->rank) parent1->rank++;
            parent2->parent = parent1;
            parent1->members += parent2->members;
            if(parent1->members > max) max = parent1->members;
        }
        else
        {
            parent1->parent = parent2;
            parent2->members += parent1->members;
            if(parent2->members > max) max = parent2->members;
        }
    }
};
int main()
{
    Graph queries{{1, 2}, {3, 4}, {5, 6}, {2, 3}};
    DisjointSet ds;
    for(const auto& i:queries)
    {
        ds.doUnion(i[0], i[1]);
        std::cout << ds.getMax() << '\n';
    }
    return 0;
}
