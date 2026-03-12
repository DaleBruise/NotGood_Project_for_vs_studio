#pragma once

#include <iostream>

#define ElemType int
#define MaxSize 100

struct SeqList {
    ElemType data[MaxSize];
    int length = 0;
};

struct LNode {
    ElemType data;
    LNode* next;
    LNode* prior;
    int freq = 0;
};

struct BNode {
    ElemType data;
    BNode* lchild;
    BNode* rchild;
};

using LinkList = LNode*;
using BTree = BNode*;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};
