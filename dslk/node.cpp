#include <iostream>
#include <stdlib.h>
using namespace std;
struct node
{
    int data;
    node *pNext;
};

struct list
{
    node *pHead;
    node *pTail;
};
void createList(list &l)
{
    l.pHead = NULL;
    l.pTail = NULL;
}
node *createNode(int data)
{
    node *p = new node;
    p->data = data;
    p->pNext = NULL;
    return p;
}

void addTail(list &l, node *p)
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

void printList(list l)
{
    cout << "in danh sach: ";
    for (node *k = l.pHead; k != NULL; k = k->pNext)
    {
        cout << k->data << " ";
    }
}

int main()
{
    int sizeList;
    int data;
    list l;
    createList(l);
    cout << "Nhap size: ";
    cin >> sizeList;
    cout << "Nhap data: ";
    for (int i = 0; i < sizeList; i++)
    {
        cin >> data;
        node *p = new node;
        p = createNode(data);
        addTail(l, p);
    }

    printList(l);

    system("pause");
    return 0;
}