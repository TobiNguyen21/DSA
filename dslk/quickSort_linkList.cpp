#include <iostream>

using namespace std;

struct Node
{
    int data;
    Node *pNext;
};

struct List
{
    Node *pHead;
    Node *pTail;
};

void list_init(List &l)
{
    l.pHead = NULL;
    l.pTail = NULL;
}

Node *createNode(int data)
{
    Node *p = new Node;
    if (p == NULL)
    {
        cout << "Bo nho day";
        exit(1);
    }
    else
    {
        p->data = data;
        p->pNext = NULL;
    }
    return p;
}

void printList(List l)
{
    for (Node *k = l.pHead; k != NULL; k = k->pNext)
    {
        cout << k->data << " ";
    }
    cout << "\n";
}

void addTail(List &l, Node *p)
{
    if (l.pHead == NULL)
    {
        l.pHead = l.pTail = p;
    }
    else
    {
        l.pTail->pNext = p;
        l.pTail = p;
    }
}

void create_list_last(List &l)
{
    int size;
    cout << "Nhap do dai list: ";
    cin >> size;
    for (int i = 0; i < size; i++)
    {
        Node *p = new Node;
        int data;
        cin >> data;
        p = createNode(data);
        addTail(l, p);
    }
}

Node *getNode(List &l, int index)
{
    Node *p = l.pHead;
    int i = 0;
    while (p != NULL && i < index)
    {
        p = p->pNext;
        i++;
    }
    return p;
}

int getIndex(List &l, Node *p)
{
    Node *q = l.pHead;
    int i = 0;
    while (q != p && q != NULL)
    {
        q = q->pNext;
        i++;
    }
    return i;
}

Node *getPrevNode(List &l, Node *p)
{
    Node *q = l.pHead;
    while (q->pNext != p && q->pNext != NULL)
    {
        q = q->pNext;
    }
    return q;
}

void quickSort(List &l, int left, int right)
{
    if (left >= right)
        return;
    Node *i = getNode(l, left);
    Node *j = getNode(l, right);
    int x = i->data;
    do
    {
        while (i->data < x)
        {
            i = i->pNext;
        }
        while (j->data > x)
        {
            j = getPrevNode(l, j);
        }
        if (getIndex(l, i) <= getIndex(l, j))
        {
            swap(i->data, j->data);
            i = i->pNext;
            j = getPrevNode(l, j);
        }
    } while (getIndex(l, i) < getIndex(l, j));

    if (left < getIndex(l, j))
        quickSort(l, left, getIndex(l, j));
    if (getIndex(l, i) < right)
        quickSort(l, getIndex(l, i), right);
}

int main()
{
    List l;
    list_init(l);
    create_list_last(l);
    printList(l);

    int left = getIndex(l, l.pHead);
    int right = getIndex(l, l.pTail);
    quickSort(l, left, right);

    printList(l);

    return 0;
}