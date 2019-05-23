#include <iostream>
#include <iomanip>

using namespace std;

struct Node{
    int data;
    Node *pChild[2];

    Node(int x):data(x) {
		pChild[0] = pChild[1] = 0;
	}
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
            //pNode = &((*pNode)->pNext);
            pNode = &((*pNode)->pChild[(*pNode)->data < x]);
            
        }
        return 0;
    }


    void insert(int x) {
        Node **pNode;
        if ((find(x, pNode))) return;
        Node *newNode = new Node(x);
        *pNode = newNode;
        length++;
    }

    void print() {
    	print(pRoot);
    	cout << endl;
    }
    
    void print(Node *p, int indent = 0) {
    	if (p) {
    		print(p->pChild[1], indent+6);
    		cout << setw(indent) << " ";
    		cout << p->data << endl;
    		print(p->pChild[0], indent+6);
		}
	}
};

int main() {
    LinkedList list;
    list.insert(6);
    list.insert(4);
    list.insert(7);
    list.insert(2);
    list.insert(1);
    list.insert(5);
    list.print();
    return 0;
}
