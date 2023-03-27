#include <iostream>
using namespace std;

static int n;
struct NODE
{
    int data;
    NODE *pNext;
    NODE *pPrev;
};
struct LIST
{
    NODE *pHead;
    NODE *pTail;
};
NODE *create_NODE(int data)
{
    NODE *p = new NODE;
    p->data = data;
    p->pNext = NULL;
    p->pPrev = NULL;
    return p;
}
void create_LIST(LIST &l)
{
    l.pHead = NULL;
    l.pTail = NULL;
}
void add_Tail(LIST &l, NODE *p)
{
    if (l.pHead == NULL)
    {
        l.pHead = l.pTail = p;
    }
    else
    {
        l.pTail->pNext = p;
        p->pPrev = l.pTail;
        l.pTail = p;
    }
}
void print_LIST(LIST l)
{
    for (NODE *k = l.pHead; k != NULL; k = k->pNext)
    {
        cout << k->data << " ";
    }
}
void add_at(LIST &l, int vt, NODE *t)
{

    int temp = 0;
    if (vt == 0)
    {
        l.pHead->pPrev = t;
        t->pNext = l.pHead;
        l.pHead = t;
    }
    else if (vt == n)
    {
        add_Tail(l, t);
    }
    else
    {
        for (NODE *k = l.pHead; k != NULL; k = k->pNext)
        {
            if (temp == vt) // k= 2------1 2 3---vt=1, gt=6
            {
                k->pPrev->pNext = t; // 1-->6
                t->pPrev = k->pPrev; // 1<---6
                t->pNext = k;        // 6--->2
                k->pPrev = t;        // 6<---2
            }
            temp++;
        }
    }
}
int main()
{
    LIST l;
    create_LIST(l);
    int x;
    cout << "Nhap n: ";
    cin >> n;
    cout << "Nhap data: ";
    for (int i = 0; i < n; i++)
    {
        cin >> x;
        NODE *p = create_NODE(x);
        add_Tail(l, p);
    }
    int vt, gt;
    cout << "Nhap vi tri chen va gia tri:";
    cin >> vt >> gt;
    NODE *t = create_NODE(gt);
    add_at(l, vt, t);
    print_LIST(l);
    return 0;
}