//Please compile this with ISO C++ 11

#include <iostream>
#include <initializer_list>
#include <exception>

using namespace std;

class NotFoundException: public exception {
public:
	virtual const char* what() const throw()
	{
		return "Element not found";
	}
} NotFound;

template<class S>
struct Node {
	S data;
	Node* pNext; //O ponteiro que aponta para um outro nó
	
	Node(S x): data(x), pNext(NULL) {}; //O nó inicia com o dado e apontando para nada
};

template<class S>
class LinkedList {
	Node<S> *pRoot; //Aponta para o início da lista
	int length;
	
	template<typename T, typename... args>
	initialize(T number, args... numbers) {
		insert(number);
		initialize(numbers...);
	}
	template<typename T>
	initialize(T number) {
		insert(number);
	}
	
	//Initializer list
//	LinkedList(): pRoot(NULL), length(0) {}; //Quando cria uma Linked List, ela inicia sem nós e sem tamanho
//	LinkedList(initializer_list<int> list) { //Initializer list
//		for (auto a: list) insert(a);
//	};

public:
	template<typename... args>
	LinkedList(args... numbers) {
		length = 0;
		pRoot = 0;
		initialize(numbers...);
	}
	template<typename T>
	LinkedList(T number) {
		length = 0;
		pRoot = 0;
		insert(number);
	}	
	
	LinkedList() {
		length = 0;
		pRoot = 0;
	}
	
	bool find(S x, Node<S>**& pNode) { //Aqui pegamos a referência de pNode (ponteiro a um ponteiro a um nó)
		pNode = &pRoot; //Aponta para o nó root
		while(*pNode) { //Enquanto não chegar ao final da lista
			if ((**pNode).data == x) return true; //Se encontra
			pNode = &((**pNode).pNext); //Agora pNode aponta para o próximo nó
		}
		return false; //Não encontrou
	}
	
	void insert(S x) {
		Node<S>** pNode;
//		cout << *pNode;
//		cout << endl;
		if(find(x, pNode)) return; //Verifica se está na lista
		Node<S> *newNode = new Node<S>(x); //Dinâmica, pra não perder; ponteiro, pois dinâmica
		*pNode = newNode; //O último nó aponta para o novo último nó
		length++;
	}
	
	void print() {
		Node<S>** pNode;
		pNode = &pRoot;
		while (*pNode) {
			cout << (*pNode)->data << " ";
			pNode = &((*pNode)->pNext);
		}
		cout << endl;
	}
	
	void remove(S x) {
		Node<S>** pNode;
		if(!find(x, pNode)) throw NotFound;
		*pNode = (*pNode)->pNext;
	}
	
	void destroy() {
		Node<S>* pNode = pRoot;
		S data;		
		for (int i = 0; i < length; i++)
		{
			data = pNode->data;
			pRoot = pRoot->pNext;
			delete pNode;
			cout << data << " deleted";
			cout << endl;
			pNode = pRoot;
		}
		
//		Node** pNode = &(pRoot->pNext);
//		cout << (*pNode)->data;
//		cout << endl;
//		delete pRoot;
//		cout << (*pNode)->data;
//		cout << endl;
	}
	
	class Iterator {
		Node<S> *pNodo;
	public:
		Iterator() {
			pNodo = NULL;		
		}
		Iterator(Node<S> *pNode) {
			pNodo = pNode;	
		}
		void operator=(Node<S>* pNode) {
			pNodo = pNode;
		}
		Node<S>* p() {
			return pNodo;
		}
		void operator=(Iterator it) {
			pNodo = it.p();
		}
		bool operator!=(Iterator it) {
			if (pNodo != it.p()) return true;
			return false;
		}
		void operator++() {
			pNodo = pNodo->pNext;
		}
		S operator*() {
			return pNodo->data;
		}
	};
	
	Iterator begin() {
		Iterator it = pRoot;
		return it;
	}
	
	Iterator end() {
		Node<S>* pNode = pRoot;
		while (pNode) {
			pNode = pNode->pNext;
		}
		Iterator it;
		it = pNode;
		return it;
	}
};

int main() {
    // Option 1: Variadic Templates
    LinkedList<int> list1(1, 2, 10, 2, 3);
    list1.print();
    // create a linked list for three data types
    LinkedList<int> ilist(1, 10, 2);
    ilist.print();
    // output: 1 10 2 
    LinkedList<float> flist(1.2, 1.4, 100000);
    flist.print();
    // output: 1.2 1.4 100000 
    LinkedList<std::string> slist("one", "two", "three");
    slist.print();
    // output: one two three
    LinkedList<int>::Iterator it;
    for (it=list1.begin(); it!=list1.end(); ++it) {
        std::cout << *it << " ";
    }
    cout << endl;
    // Correct way to handle exceptions
    try {
        list1.remove(20);
    } catch (const NotFoundException& e) {
        cerr << e.what();
    }
    // output: Element not found
}
