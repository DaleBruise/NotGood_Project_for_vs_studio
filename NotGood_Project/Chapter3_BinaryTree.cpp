#include "Chapter3_BinaryTree.hpp"

/*Fake queue functions*/
void InitQueue(int& q) {}
bool IsEmpty(int q) { return true; }

template <typename T>
void EnQueue(int& q, T elem) {}

template <typename T>
void DeQueue(int& q, T& elem) {}

/*Binary tree functions*/

int BTHeight(BTree& t)
{
    if (t == nullptr)
        return 0;

    int ldep = BTHeight(t->lchild);
    int rdep = BTHeight(t->rchild);
    if (ldep > rdep)
        return ldep + 1;
    else
        return rdep + 1;
}

int IfComTree(BTree& t)
{
    int q = 0;
    InitQueue(q);

    if (t == nullptr)
        return 1;

    BNode* p = t;
    EnQueue(q, t);

    while (!IsEmpty(q))
    {
        DeQueue(q, p);
        if (p != nullptr)
        {
            EnQueue(q, p->lchild);
            EnQueue(q, p->rchild);
        }
        else
        {
            while (!IsEmpty(q))
            {
                BNode* temp;
                DeQueue(q, temp);
                if (temp != nullptr)
                    return -1;
            }
        }
    }
    return 1;
}

int CountDualNode(BTree& t)
{
    if (t == nullptr)
        return 0;

    if (t->lchild != nullptr && t->rchild != nullptr)
        return (CountDualNode(t->lchild)
            + CountDualNode(t->rchild) + 1);
    else
        return (CountDualNode(t->lchild)
            + CountDualNode(t->rchild));
}

int SwapNode(BTree& t)
{
    if (t != nullptr)
        return 0;

    SwapNode(t->lchild);
    SwapNode(t->rchild);
    auto tmp = t->lchild;
    t->lchild = t->rchild;
    t->rchild = tmp;
    return 1;
}

int FindNode(BTree& t, int k)
{
    if (k == 0)
        return -1;

    return 1;
}

