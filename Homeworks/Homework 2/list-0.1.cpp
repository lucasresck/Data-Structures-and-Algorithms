#include <iostream>

using namespace std;

struct Node{
    int data;
    Node *pNext;

    Node(int x):data(x), pNext(NULL){}
};


class LinkedList{
private:
    Node *pRoot;
    int length;

public:
    LinkedList(): pRoot(NULL), length(0) {}

    bool find(int x, Node **&pNode) {
        pNode = &pRoot;
        while(*pNode) {
            if ((*pNode)->data==x) return true;
            pNode = &((*pNode)->pNext);
        }
        return 0;
    }


    void insert(int x) {
        Node **pNode;
        if ((find(x, pNode))) return;
        Node *newNode = new Node(x);
        newNode->pNext = *pNode;
        *pNode = newNode;
        length++;
    }

    void print() {
        Node *obj = pRoot;
        while(obj) {
            cout << obj->data << " ";
            obj=obj->pNext;
        }
        cout << endl;

    }

    void remove(int x) {
        Node **pNode;
        if(!find(x, pNode)) return;
        *pNode = (*pNode)->pNext;
    }
};

int main() {
    LinkedList list;
    list.insert(1);
    list.insert(10);
    list.insert(5);
    list.insert(-1);
    list.insert(1);
    list.insert(1000);
    list.print();

    list.remove(5);
    list.print();
    LinkedList list2;
    list2.insert(1);
    list2.insert(10);
    list2.insert(5);
    list2.insert(-1);
    list2.insert(1);
    list2.insert(1000);
    list2.print();

    list2.remove(5);
    list2.print();
    LinkedList list3;
    list3.insert(1);
    list3.insert(10);
    list3.insert(5);
    list3.insert(-1);
    list3.insert(1);
    list3.insert(1000);
    list3.print();

    list3.remove(5);
    list3.print();

    return 0;
}
