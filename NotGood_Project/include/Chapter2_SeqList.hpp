#pragma once

/* Sequence list */

ElemType
ReduceMin(SeqList* L, int& flag);
int
ReverseList(SeqList& L);
int
DeleteX(SeqList& L, ElemType X);
int
DeleteX_st(SeqList& L, ElemType s, ElemType t);
int
DeduList(SeqList& L);
int
ComebineList(SeqList L1, SeqList L2, SeqList& L);
int
ReverseArray(ElemType* a, int la, int lb);
int
FindElem(SeqList& L, ElemType X);
int
OutputElem(SeqList& A, SeqList& B, SeqList& C, int length);
int
ReverseList2(SeqList& L, int p);
ElemType
SortList(SeqList& l1, SeqList& l2);
int
MainList(SeqList& L, ElemType& value);

/* Link list */

int
InitList(LinkList& L);
int
DeleteX_ll(LinkList& L, ElemType X);
int
Delete_min(LinkList& L);
int
ReverseLList(LinkList& L);
int
DeleteX_a2b(LinkList& L, ElemType a, ElemType b);
int
Splilt(LinkList& L, LinkList& La, LinkList& Lb);
int
Nodup(LinkList& L);
int
PublicNode(LinkList& La, LinkList& Lb, LinkList& L);
int
Intersection(LinkList& La, LinkList& Lb);
int
SubSequence(LinkList& La, LinkList& Lb);
int
CircleDualList(LinkList& L);
int
InsertCircleList(LinkList& L1, LinkList& L2);
LinkList
Locate(LinkList& L, ElemType x);
int
RightMove(LinkList& L, int k);
int
IfCircle(LinkList& L);
ElemType
TwinbornMax(LinkList& L);
int
Backwords(LinkList& L, int index, ElemType& value);
int
SameSuffix(LinkList& L1, LinkList& L2, LinkList& p);

/*Tasks*/

void
Task1();
void
Task2();
void
Task3();
void
Task4();
void
Task5();
void
Task6();
void
Task7();
void
Task8();
void
Task9();
void
Task10();
void
Task11();

