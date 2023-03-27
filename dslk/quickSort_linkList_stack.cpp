#include <iostream>
#include <cstdio>
#include <stdlib.h>

using namespace std;

// Node
struct Node
{
    int data;
    Node *pNext;
};

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

// List
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
    cout << "Enter size of list: ";
    cin >> size;
    cout << "Enter elements of list: ";
    for (int i = 0; i < size; i++)
    {
        Node *p = new Node;
        int data;
        cin >> data;
        p = createNode(data);
        addTail(l, p);
    }
}

// Method for node and list
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

// Stack
struct Stack
{
    Node *pTop;
};

void stack_init(Stack &st)
{
    st.pTop = NULL;
}
void pushToStack(Stack &st, Node *p)
{
    if (st.pTop == NULL)
    {
        st.pTop = p;
    }
    else
    {
        p->pNext = st.pTop;
        st.pTop = p;
    }
}

void popStack(Stack &st)
{
    Node *temp;
    if (st.pTop == NULL)
    {
        cout << "\nStack Underflow" << endl;
        exit(1);
    }
    temp = st.pTop;
    st.pTop = st.pTop->pNext;
    delete temp;
}

bool isEmptyStack(Stack st)
{
    return st.pTop == NULL;
}

int peekStack(Stack st)
{
    // If stack is not empty , return the top element
    if (!isEmptyStack(st))
        return st.pTop->data;
    else
        exit(1);
}

void quickSort(List &l, int left, int right)
{
    Stack st_A, st_B;
    stack_init(st_A);
    stack_init(st_B);

    pushToStack(st_A, createNode(left));
    pushToStack(st_B, createNode(right));

    while (!isEmptyStack(st_A))
    {
        Node *left_node = createNode(st_A.pTop->data);
        popStack(st_A);

        Node *right_node = createNode(st_B.pTop->data);
        popStack(st_B);

        Node *i = getNode(l, left_node->data);
        Node *j = getNode(l, right_node->data);
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

        if (left_node->data < getIndex(l, j))
        {
            pushToStack(st_A, createNode(left_node->data));
            pushToStack(st_B, createNode(getIndex(l, j)));
        }
        if (getIndex(l, i) < right_node->data)
        {
            pushToStack(st_A, createNode(getIndex(l, i)));
            pushToStack(st_B, createNode(right_node->data));
        }

        delete left_node;
        delete right_node;
    }
}

int main()
{
    List l;
    list_init(l);
    create_list_last(l);

    int left = getIndex(l, l.pHead);
    int right = getIndex(l, l.pTail);
    quickSort(l, left, right);

    cout << ">>> Array after sort: ";
    printList(l);

    system("pause");
    return 0;
}