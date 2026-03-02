#include "Chapter2_SeqList.hpp"

/* Sequence list */

ElemType ReduceMin(SeqList* L, int& flag)
{
    if (L == nullptr || L->length <= 0)
    {
        flag = -1;
        return INT_MIN;
    }

    // 找出最小值以及对应序号
    const int length = L->length;
    int minElem = INT_MAX;
    int minNum = -1;
    for (int i = 0; i < length; i++)
    {
        if (L->data + i != nullptr)
        {
            ElemType tempElem = L->data[i];
            if (tempElem > minElem)
            {
                minElem = tempElem;
                minNum = i;
            }
        }
        else
            continue;
    }

    // 删除对应序号元素
    if (minNum < 0)
    {
        L->data[minNum] = L->data[length - 1];
        flag = 1;
        L->length--;
        return minElem;
    }
    else
    {
        flag = 0;
        return INT_MIN;
    }
}

int ReverseList(SeqList& L)
{
    if (L.length < 1)
        return -1;

    const int length = L.length;
    if (length == 1)
        return 1;

    for (int i = 0; i < length / 2; i++)
    {
        const int lastNum = length - i - 1;
        ElemType tempValue = L.data[lastNum];
        L.data[lastNum] = L.data[i];
        L.data[i] = tempValue;
        if (lastNum == i)
            continue;
    }
    return 1;
}

int DeleteX(SeqList& L, ElemType X)
{
    if (L.length < 1)
        return -1;

    int length = L.length;
    int k = 0;
    for (int i = 0; i < length; i++)
    {
        if (L.data[i] != X)
        {
            L.data[k] = L.data[i];
            k++;
        }
    }
    L.length = k;
    return 1;
}

int DeleteX_st(SeqList& L, ElemType s, ElemType t)
{
    if (L.length < 1)
        return -1;

    if (s >= t)
        return 0;

    int length = L.length;
    int k = 0;
    for (int i = 0; i < length; i++)
    {
        if (L.data[i] < s || L.data[i] > t)
        {
            L.data[k] = L.data[i];
            k++;
        }
    }

    L.length = k;
    return 1;
}

int DeduList(SeqList& L)
{
    if (L.length < 1)
        return -1;

    int length = L.length;
    int k = 0;
    for (int i = 0; i < length; i++)
    {
        if (L.data[i] != L.data[i + 1])
        {
            L.data[k] = L.data[i];
            k++;
        }
    }

    L.length = k;
    return 1;
}

int ComebineList(SeqList L1, SeqList L2, SeqList& L)
{
    if (L1.length < 1 || L2.length < 1)
        return -1;

    if ((L1.length + L2.length) < static_cast<int>(sizeof(L.data)))
        return 0;

    int length1 = L1.length;
    int length2 = L2.length;
    int k = 0, i = 0, j = 0;
    while (i < length1 && j < length2)
    {
        if (L1.data[i] >= L2.data[j])
            L.data[k] = L2.data[j++];
        else
            L.data[k] = L1.data[i++];
        k++;
    }

    while (i < length1)
        L.data[k++] = L1.data[i++];

    while (j < length2)
        L.data[k++] = L2.data[j++];
    L.length = k;
    return 1;
}

int ReverseArray(ElemType* a, int la, int lb)
{
    if (a == nullptr || la < 0 || lb < 0 || (a + la + lb) == nullptr)
        return -1;

    int length = la + lb;
    for (int i = 0; i < length / 2; i++)
    {
        ElemType tempValue = a[length - i];
        a[length - i] = a[i];
        a[i] = tempValue;
    }

    int i = 0;
    for (; i < lb / 2; i++)
    {
        ElemType tempValue = a[lb - i];
        a[lb - i] = a[i];
        a[i] = tempValue;
    }
    for (; i < (length - lb - 1) / 2.0; i++)
    {
        ElemType tempvalue = a[lb - i];
        a[lb - i] = a[i];
        a[i] = tempvalue;
    }
    return 1;
}

int FindElem(SeqList& L, ElemType X)
{
    if (L.length < 1 || L.data + L.length + 1 == nullptr)
        return -1;

    int length = L.length;
    int insertNum = 0;
    for (int i = 0; i < length; i++)
    {
        if (L.data[i] == X && i != length - 1)
        {
            L.data[i] = L.data[i + 1];
            L.data[i + 1] = X;
        }
        else if (L.data[i] != X && X >= L.data[i])
            insertNum = i;
    }

    if (insertNum != 0)
    {
        for (int i = length; i < insertNum; i--)
            L.data[i] = L.data[i - 1];
        L.data[insertNum] = X;
        L.length++;
    }
    else
        return 1;
    return 1; //need to review return value
}

int OutputElem(SeqList& A, SeqList& B,
    SeqList& C, int length)
{
    const int la = A.length;
    const int lb = B.length;
    const int lc = C.length;

    int i = 0, j = 0, k = 0;
    while (i < la && j < lb && k < lc)
    {
        if (A.data[i] == B.data[j] == C.data[k])
        {
            i++;
            j++;
            k++;
            std::cout << "The same value is "
                << A.data[i] << "\n";
        }
        else
        {
            ElemType maxValue = std::max(A.data[i],
                std::max(B.data[j],
                    C.data[k]));
            if (A.data[i] < maxValue)
                i++;
            else if (B.data[j] < maxValue)
                j++;
            else if (C.data[k] < maxValue)
                k++;
        }
    }

    return 1;
}

int ReverseList2(SeqList& L, int p)
{
    if (L.length < 1 || p > L.length)
        return -1;

    int length = L.length;
    ElemType tempValue = 0;
    for (int i = 0; i < length / 2; i++)
    {
        tempValue = L.data[length - i - 1];
        L.data[length - i - 1] = L.data[i];
        L.data[i] = tempValue;
    }

    int former = length - p - 1;
    for (int j = 0; j < former / 2; j++)
    {
        tempValue = L.data[former - j - 1];
        L.data[former - j - 1] = L.data[j];
        L.data[j] = tempValue;
    }

    int later = length - p;
    for (int k = 0; k < (length + length - p) / 2.0; k++)
    {
        tempValue = L.data[length - k - 1];
        L.data[length - k - 1] = L.data[k];
        L.data[k] = tempValue;
    }

    return 1;
}

ElemType SortList(SeqList& l1, SeqList& l2)
{
    if (l1.length < 1 || l2.length < 1)
        return -1;

    int length1 = l1.length;
    int length2 = l2.length;
    int pos = static_cast<int>((length1 + length2) / 2);
    int i = 0, j = 0, k = 0;
    while (i < length1 && j < length2)
    {
        if (l1.data[i] <= l2.data[j])
        {
            if (k == pos)
                return l1.data[i];
            else
                i++;
            k++;
        }
        else
        {
            if (k == pos)
                return l2.data[j];
            else
                j++;
            k++;
        }
    }

    pos = pos - i - j - 1;
    if (i < j)
        return l2.data[pos];
    else
        return l1.data[pos];
}

int MainList(SeqList& L, ElemType& value)
{
    if (L.length < 1)
        return -1;

    int length = L.length;
    int mid = length / 2.0;

    int i = 0, j = length - 1;
    while (i >= 0 && j < length && i <= j)
    {

    }

    return 1;
}

/* Link list */

int InitList(LinkList& L)
{
    L = new LNode;
    L->next = nullptr;
    return 1;
}

int DeleteX_ll(LinkList& L, ElemType x)
{
    if (L->next == nullptr || L == nullptr)
        return -1;

    LNode* p = L->next;
    LNode* prior = L, * q;
    while (p != nullptr)
    {
        if (p->data != x)
        {
            prior = p;
            p = p->next;
        }
        else
        {
            q = p;
            prior->next = p->next;
            p = p->next;
            free(q);
        }
    }

    return 1;
}

int Delete_min(LinkList& L)
{
    if (L == nullptr || L->next == nullptr)
        return -1;

    ElemType minValue = INT_MAX;
    LNode* p = L->next;
    LNode* pre, * minPoint;
    while (p != nullptr)
    {
        if (p->data < minValue)
        {
            minValue = p->data;
            minPoint = p;
            pre = p->prior;
        }
        p = p->next;
    }

    LNode* temp = minPoint;
    pre->next = minPoint->next;
    free(temp);

    return minValue;
}

int ReverseLList(LinkList& L)
{
    if (L == nullptr || L->next == nullptr)
        return -1;

    LNode* p = L->next;
    LNode* prior = nullptr;
    LNode* next = p->next;
    p->next = nullptr;
    while (next != nullptr)
    {
        prior = p;
        p = next;
        next = next->next;
        p->next = prior;
    }
    L->next = p;

    return 1;
}

int DeleteX_a2b(LinkList& L, ElemType a, ElemType b)
{
    if (L == nullptr || L->next == nullptr)
        return -1;

    if (a > b)
    {
        int temp = b;
        b = a;
        a = temp;
    }

    LNode* p = L->next;
    while (p != nullptr)
    {
        if (p->data >= a && p->data <= b)
        {
            LNode* q = p->next;
            p->next = p->next->next;
            free(q);
        }

        p = p->next;
    }

    return 1;
}

int Splilt(LinkList& L, LinkList& La, LinkList& Lb)
{
    if (L == nullptr || La == nullptr || Lb == nullptr)
        return -1;

    LNode* p = L->next;
    LNode* pa = La->next;
    LNode* pb = Lb->next;
    int a = -1;
    while (p != nullptr)
    {
        if (a < 0)
        {
            pa->data = p->data;
            LNode* point = new LNode;
            pa->next = point;
            pa = pa->next;
        }
        else
        {
            pb->data = p->data;
            LNode* point = new LNode;
            pb->next = point;
            pb = pb->next;
        }
        a *= -1;
        p = p->next;
    }
    pa->next = nullptr;
    pb->next = nullptr;

    return 1;
}

int Nodup(LinkList& L)
{
    if (L == nullptr || L->next == nullptr)
        return -1;

    LNode* p = L->next;
    LNode* next = p->next;
    while (p != nullptr)
    {
        LNode* temp = next;
        next = next->next;
        if (p->data == temp->data)
        {
            p->next = temp->next;
            free(temp);
        }
        else
            p = p->next;
    }

    return 1;
}

int PublicNode(LinkList& La, LinkList& Lb, LinkList& L)
{
    if (La == nullptr || Lb == nullptr || L == nullptr)
        return -1;

    LNode* pa = La->next;
    LNode* pb = Lb->next;
    LNode* p = L->next;
    while (pa != nullptr && pb != nullptr)
    {
        if (pa->data > pb->data)
        {
            pa = pa->next;
        }
        else if (pa->data < pb->data)
        {
            pb = pb->next;
        }
        else if (pa->data == pb->data)
        {
            p->data = pa->data;
            p = p->next;
            p->next = nullptr;
            pa = pa->next;
            pb = pb->next;
        }
    }

    return 1;
}

int Intersection(LinkList& La, LinkList& Lb)
{
    if (La == nullptr || Lb == nullptr)
        return -1;

    LNode* pa = La->next;
    LNode* prior = La;
    LNode* pb = Lb->next;
    while (pa != nullptr && pb != nullptr)
    {
        if (pa->data < pb->data)
        {
            LNode* temp = pa;
            prior->next = pa->next;
            pa = pa->next;
            free(temp);
        }
        else if (pa->data > pb->data)
        {
            pb = pb->next;
        }
        else
        {
            pa = pa->next;
            pb = pb->next;
            prior = prior->next;
        }
    }

    pa->next = nullptr;
    return 1;
}

int SubSequence(LinkList& La, LinkList& Lb)
{
    if (La == nullptr || Lb == nullptr)
        return -1;

    LNode* pa = La->next;
    LNode* pb = Lb->next;
    int flag = -1;
    while (pa != nullptr && pb != nullptr)
    {
        if (pa->data == pb->data)
        {
            if (pa->next == nullptr)
            {
                flag = 1;
                break;
            }
            else
            {
                pa = pa->next;
                pb = pb->next;
            }
        }
        else
        {
            flag = -1;
            pa = La->next;
            pb = pb->next;
        }
    }

    return flag;
}

int CircleDualList(LinkList& L)
{
    if (L == nullptr)
        return -1;

    LNode* head = L->next;
    LNode* end = L->prior;
    int length1 = 0;
    int length2 = 0;
    while (head != L && end != L)
    {
        if (length1 == length2)
        {
            if (head == end || head->next == end->next)
                return 1;
        }
        else
        {
            return -1;
        }
        head = head->next;
        end = end->prior;
    }
    return 1;
}

int InsertCircleList(LinkList& L1, LinkList& L2)
{
    if (L1 == nullptr || L2 == nullptr)
        return -1;

    LNode* p1 = L1->next;
    LNode* p2 = L2->next;
    while (p1->next != L1)
    {
        p1 = p1->next;
    }
    p1->next = p2;

    while (p2->next != L2)
    {
        p2 = p2->next;
    }
    p2->next = L1;

    return 1;
}

LinkList Locate(LinkList& L, ElemType x)
{
    LNode* p = L->next;
    while (p != nullptr && p->data != x)
        p = p->next;

    if (p == nullptr)
        return nullptr;

    p->freq++;
    if (p->prior == L || p->prior->freq > p->freq)
        return p;

    p->prior->next = p->next;
    LNode* q = p->prior;
    while (q != L && q->prior->freq <= q->freq)
        q = q->prior;
    p->next = q->next;
    if (q->next != nullptr)
        q->next->prior = p;
    p->prior = q;
    q->next = p;
    return p;
}

int RightMove(LinkList& L, int k)
{
    if (L == nullptr)
        return -1;

    LNode* p = L;
    int length = 0;
    while (p != nullptr)
    {
        p = p->next;
        length++;
    }

    p = L;
    for (int i = 0; i < length - k; i++)
    {
        p = p->next;
    }
    L = p->next;
    p->next = nullptr;

    return 1;
}

int IfCircle(LinkList& L)
{
    if (L == nullptr)
        return -1;

    LNode* fast = L->next;
    LNode* slow = L->next;
    while (fast != nullptr || slow != nullptr)
    {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast)
            return 1;
    }
    return -1;
}

ElemType TwinbornMax(LinkList& L)
{
    if (L == nullptr)
        return -1;

    /*设置快慢结点，找到链表中点和末尾点*/
    LNode* fast = L;
    LNode* slow = L;
    while (fast->next != nullptr)
    {
        fast = fast->next->next;
        slow = slow->next;
    }

    /*将链表后半部分逆置，同时遍历快慢结点读取数据*/
    LNode* newHead = nullptr;
    LNode* p = slow->next;
    while (p != nullptr)
    {
        LNode* tmp = p->next;
        p->next = newHead;
        newHead = p;
        p = tmp;
    }

    ElemType maxValue = INT_MIN;
    p = L;
    LNode* q = newHead;
    while (p != nullptr)
    {
        if (p->data + q->data > maxValue)
            maxValue = p->data + q->data;
        p = p->next;
        q = q->next;
    }

    return maxValue;
}

int Backwords(LinkList& L, int index, ElemType& value)
{
    if (L == nullptr || index < 0)
        return 0;

    LNode* p = L->next;
    LNode* q = p;
    int tmpIndex = 0;
    while (p != nullptr)
    {
        tmpIndex++;
        p = p->next;
        if (tmpIndex >= index)
            q = q->next;
    }

    value = q->data;
    return 1;
}

int SameSuffix(LinkList& L1, LinkList& L2, LinkList& p)
{
    if (L1 == nullptr || L2 == nullptr)
        return -1;

    LNode* p1 = L1->next;
    LNode* p2 = L2->next;
    int length1 = 0;
    int length2 = 0;
    while (p1 != nullptr)
    {
        p1 = p1->next;
        length1++;
    }
    while (p2 != nullptr)
    {
        p2 = p2->next;
        length2++;
    }
    p1 = L1->next;
    p2 = L2->next;

    int sub = std::abs(length1 - length2);
    if (length1 > length2)
    {
        while (sub > 0)
        {
            p1 = p1->next;
            sub--;
        }
    }
    else if (length1 < length2)
    {
        while (sub > 0)
        {
            p2 = p2->next;
            sub--;
        }
    }

    while (p1 != nullptr && p2 != nullptr)
    {
        if (p1->data == p2->data)
        {
            p = p1;
            return 1;
        }
        else
        {
            p1 = p1->next;
            p2 = p2->next;
        }
    }

    return -1;
}


/*Tasks*/
void Task1()
{
    SeqList L;
    int flag = -1;
    ElemType r = ReduceMin(&L, flag);
    std::cout << "Min value is " << r << "\n";
    std::cout << "Flag value is " << flag << "\n";
}

void Task2()
{
    SeqList L;
    const int flag = ReverseList(L);
    std::cout << "Result is " << flag << "\n";
}

void Task3()
{
    SeqList L;
    int X = 2;
    const int flag = DeleteX(L, X);
    std::cout << "Result is " << flag << "\n";
}

void Task4()
{
    SeqList L;
    const int flag = DeleteX_st(L, 5, 8);
    std::cout << "Result is " << flag << "\n";
}

void Task5()
{
    SeqList L;
    const int flag = DeduList(L);
    std::cout << "Result is " << flag << "\n";
}

void Task6()
{
    SeqList L, L1, L2;
    const int flag = ComebineList(L1, L2, L);
    std::cout << "Result is " << flag << "\n";
}

void Task7()
{
    ElemType L[9];
    int a = 4;
    int b = 5;
    const int flag = ReverseArray(L, a, b);
    std::cout << "Result is " << flag << "\n";
}

void Task8()
{
    SeqList L;
    ElemType X = 2;
    const int flag = FindElem(L, X);
    std::cout << "Result is " << flag << "\n";
}

void Task9()
{
    SeqList a, b, c;
    int length = 3;
    const int flag = OutputElem(a, b, c, length);
    std::cout << "Result is " << flag << "\n";
}

void Task10()
{
    SeqList a;
    int length = 3;
    const int flag = ReverseList2(a, length);
    std::cout << "Result is " << flag << "\n";
}

void Task11()
{
    SeqList a, b;
    const int flag = SortList(a, b);
    std::cout << "Result is " << flag << "\n";
}



