#pragma once

#include <iostream>
#include <unordered_map>

#define ElemType int
#define MaxSize 100

typedef struct SeqList {
    ElemType data[MaxSize];
    int length = 0;
}SeqList;

typedef struct LNode {
    ElemType data;
    LNode* next;
    LNode* prior;
    int freq = 0;
}LNode, * LinkList;

typedef struct BNode {
    ElemType data;
    BNode* lchild;
    BNode* rchild;
}BNode, * BTree;

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
