#include <iostream>
#include <iomanip>

using namespace std;

struct Node {
    int data; 			//Data de um n�
    Node *pChild[2]; 	//Ponteiros a filhos de um n�
    Node *pParent;
    char color;

    Node(int x, char cor):data(x), color(cor) {
        pChild[0] = pChild[1] = pParent = nullptr; //Sem filhos no in�cio (aponta pra nada)
    }
};

class RBTree {
protected:
	Node *pRoot;
	
	template<typename T, typename... args>
	initialize(T number, args... numbers) {
		insert(number);
		initialize(numbers...);
	}
	template<typename T>
	initialize(T number) {
		insert(number);
	}
	
public:
	
    RBTree():pRoot(nullptr) {}
    
    template<typename... args>
    RBTree(args... numbers):pRoot(nullptr) {
    	initialize(numbers...);
    }
    
    RBTree(int number):pRoot(nullptr) {
		insert(number);
	}

    bool find(int x) {
        Node **p;
        Node* pParent;
        return find(x, p, pParent);
    }

    void insert(int x) {
        Node **p;
        Node* pParent = nullptr; //Ponteiro ao n� pai
        if (!find(x, p, pParent)) {
            *p = new Node(x, 'r');
            (*p)->pParent = pParent;
        	recolor(p);
        }
    }
    
    void remove(int x) {
    	cout << "Remove " << x << endl;
        Node **p;
        Node* pParent;
        if(find(x, p, pParent))
            remove(*p);
    }

    void print() {
        print(pRoot);
    	cout << "---------------------\n" << endl;
    }
	
private:
	
	void delete2(Node*& p, Node*& pSibling, int blacksibling, int redchild0, int redchild1) { //Pelo menos um sobrinho � vermelho
		Node* pParent = *parent(&pSibling);
		cout << "Delete case 2" << endl;
		if (redchild1 && pParent->pChild[1] == pSibling) {//Right right case
			pSibling->pChild[1]->color = pParent->color;
			rotate_left(&pParent);
		}
		else if (redchild0 && pParent->pChild[0] == pSibling) {//Left left case
			pSibling->pChild[0]->color = pParent->color;
			rotate_right(&pParent);
		}
		else if (redchild0 && pParent->pChild[1] == pSibling) {//Right left case
			change_color(&(pSibling->pChild[0]));
			pSibling->color = pParent->color;
			rotate_right(&pSibling);
			rotate_left(&pParent);
		}
		else if (redchild1 && pParent->pChild[0] == pSibling) {//Left right case
			change_color(&(pSibling->pChild[1]));
			
			pSibling->color = pParent->color;
			rotate_left(&pSibling);
			rotate_right(&pParent);
		}
	}
	
	void delete3(Node* pSibling) { //Neste caso, o irm�o e seus filhos s�o pretos
		cout << "Delete case 3" << endl;
		change_color(&pSibling);
		if ((*parent(&pSibling))->color == 'r')
			change_color(parent(&pSibling));
		else {
			recur(*parent(&pSibling));
		}
	}
	
	void delete4(Node* p, Node* pSibling) { //O irm�o � vermelho
		cout << "Delete case 4" << endl;
		if ((*parent(&pSibling))->pChild[0] == pSibling) { //Left case
			change_color(&pSibling);
			change_color(&(pSibling->pChild[1]));
			rotate_right(parent(&pSibling));
		} else { //Right case
			change_color(&pSibling);
			change_color(&(pSibling->pChild[0]));
			rotate_left(parent(&pSibling));
		}
	}
	void recur(Node* p) {
		if (p != pRoot) { 		//Se p n�o � root
			Node* pSibling = *sibling(&p);		
			int blacksibling = 0;
			if (pSibling)
				if (pSibling->color == 'b')
					blacksibling = 1;
			else
				blacksibling = 1;
			int redchild0 = 0;
			if (pSibling)
				if (pSibling->pChild[0])
					if ((pSibling->pChild[0])->color == 'r')
						redchild0 = 1;
			int redchild1 = 0;
			if (pSibling)
				if (pSibling->pChild[1])
					if ((pSibling->pChild[1])->color == 'r')
						redchild1 = 1;
			if (blacksibling && (redchild0 || redchild1)) {
				delete2(p, pSibling, blacksibling, redchild0, redchild1);
			}
			else if (blacksibling && !(redchild0 || redchild1)) { //Se o irm�o � preto e os dois filhos s�o pretos
				delete3(pSibling);
			}			
			else if (!blacksibling) {
				delete4(p, pSibling);
			}
		}
	}
	
	//void remove_root()
	
	void remove2(Node*& p) { 	//p � preto e seu filho tamb�m (ele pode ser NIL)
		Node* pSibling;
		if (p != pRoot)
			pSibling = *sibling(&p);
		delete1(p);
		if (p != pRoot) { 		//Se p n�o � root
			
			//Verifico as cores de irm�o e seus filhos
			//A gente sabe que o irm�o existe
			int blacksibling = 0;
			if (pSibling != nullptr) {
				if (pSibling->color == 'b')
					blacksibling = 1;
			} else
					blacksibling = 1;
			int redchild0 = 0;
			if (pSibling)
				if (pSibling->pChild[0])
					if ((pSibling->pChild[0])->color == 'r')
						redchild0 = 1;
			int redchild1 = 0;
			if (pSibling)
				if (pSibling->pChild[1])
					if ((pSibling->pChild[1])->color == 'r')
						redchild1 = 1;
			if (blacksibling && (redchild0 || redchild1)) {
				delete2(p, pSibling, blacksibling, redchild0, redchild1);
			}
			else if (blacksibling && !(redchild0 || redchild1)) {
				delete3(pSibling);
			}			
			else if (!blacksibling) {
				delete4(p, pSibling);
			}
		}
	}
	
	void delete1(Node*& p) { //Quando vamos apagar um n�
		Node* pParent = *parent(&p);
        p = p->pChild[p->pChild[1]!=nullptr];	//A gente apaga esse n� substituindo-o pelo seu filho
		if (p) {//Se p n�o for nullptr
			p->pParent = pParent;
        	p->color = 'b';
        }
	}

    void remove(Node *&p) {							//Removendo um n�
        if (!p->pChild[0] || !p->pChild[1])	{		//Se o n� tem no m�ximo um filho
        	if (p->color == 'r') {					//Se p � vermelho
				cout << "Delete case 1" << endl;
        		delete1(p); 
			}  						//Caso 1
        	else if (p->pChild[0] || p->pChild[1]) 	//Se tem algum filho
        		if (p->pChild[p->pChild[1]!=nullptr]->color == 'r') {//E esse filho � vermelho
					cout << "Delete case 1" << endl;
        			delete1(p);
        		}
        		else { 								//p � preto e seu filho tamb�m
        			remove2(p);
        		}
        	else { 									//p � preto sem filhos
        		remove2(p);
        	}
     	} else {										//Se o n� tem dois filhos
            Node **succesor = &(p->pChild[1]);		
            find_min(succesor);						//A gente acha o sucessor (que vai ter no m�ximo um filho)
            p->data = (*succesor)->data;			//Copia seu data
            remove(*succesor);						//E remove esse n�
        }
    }

    void find_min(Node **&p) {
        while((*p)->pChild[0]){
            p = &((*p)->pChild[0]);
        }
    }
	
	void insert1(Node** p) {
		(*p)->color = 'b';
		// cout << "Recolor root" << endl;
	}
	
	void insert2() {
		// cout << "Nothing" << endl;
	}
	
	void insert3(Node** p) {
		// cout << "Change parent uncle color" << endl;
		change_color(parent(p));
		change_color(uncle(p));
		change_color(grandpa(p));
		// cout << "Vou chamar o recolor, em?" << endl;
		recolor(grandpa(p));
	}
	
	void insert4_step2 (Node* pMe, Node* pParent, Node* pGrandpa) {
		//Qual lado vamos rotacionar no avo?
		if (pGrandpa->pChild[0]) {
		// cout << "HERE" << endl;
			if (pParent == pGrandpa->pChild[0])
			{
				// cout << "Rotate right no avo" << endl;
				rotate_right(&pGrandpa);
			} else {
			// cout << "Rotate left no avo" << endl;	
			rotate_left(&pGrandpa);			
			}
		} else {
			// cout << "Rotate left no avo" << endl;	
			rotate_left(&pGrandpa);			
		}
		// cout << "Troca de cores do pai e do avo" << endl;
		change_color(&pGrandpa);
		change_color(&pParent);
	}
		
	
	void insert4_step1(Node** p) {
		Node* pMe = *p;
		Node* pParent = *parent(p);
		Node* pGrandpa = *parent(&pParent);	
		//Precisamos garantir que nosso n� est� fora da "sub�rvore" do avo, ou seja,
		//filho esquerdo do filho esquerdo do v� ou filho direito do filho direito do avo.
		if (pGrandpa->pChild[0] == pParent && pParent->pChild[1] == pMe) {
			// cout << "Rotate left no pai" << endl;
			rotate_left(&pParent);
			Node* pAux = pMe;
			pMe = pParent;
			pParent = pAux;
		} else if (pGrandpa->pChild[1] == pParent && pParent->pChild[0] == pMe) {
			// cout << "Rotate right no pai" << endl;
			rotate_right(&pParent);
			Node* pAux = pMe;
			pMe = pParent;
			pParent = pAux;
		}		
		insert4_step2(pMe, pParent, pGrandpa);
	}
    
    void rotate_left(Node** p) {
    	Node* pMe = *p;
    	Node* pParent = *(parent(p));
    	Node* pChild = (*p)->pChild[1];

    	if (pParent) {
    		if (pParent->data > pMe->data) 
		    	pParent->pChild[0] = pChild;
		    else
				pParent->pChild[1] = pChild;
			pChild->pParent = pParent;
		} else {
			pChild->pParent = nullptr;
		}
    	pMe->pChild[1] = pChild->pChild[0]; //Meu filho agora � o filho do meu filho
    	if (pMe->pChild[1]) (pMe->pChild[1])->pParent = pMe; //Se esse filho n�o for nulo, o pai dele agora sou eu		
    	pChild->pChild[0] = pMe; //Meu filho agora aponta pra mim
    	pMe->pParent = pChild; //Meu pai agora � meu filho
    	if (!pParent) {
    		pRoot = pChild;
		}
	}
    
    void rotate_right(Node** p) {
    	Node* pMe = *p;
    	Node* pParent = *(parent(p));
    	Node* pChild = (*p)->pChild[0];
    	if (pParent) {
    		if (pParent->data > pMe->data) 
		    	pParent->pChild[0] = pChild;
		    else
				pParent->pChild[1] = pChild;
			pChild->pParent = pParent;
		} else {
			pChild->pParent = nullptr;
		}
    	pMe->pChild[0] = pChild->pChild[1]; //Meu filho agora � o filho do meu filho
    	if (pMe->pChild[0]) (pMe->pChild[0])->pParent = pMe; //Se esse filho n�o for nulo, o pai dele agora sou eu		
    	pChild->pChild[1] = pMe; //Meu filho agora aponta pra mim
    	pMe->pParent = pChild; //Meu pai agora � meu filho
    	if (!pParent) {
    		pRoot = pChild;
		}
	}
	
    bool find(int x, Node **&p, Node*& pParent) {
        p = &pRoot;
        while(*p) {
            if ((*p)->data==x) return true;
            pParent = *p; //Passamos a apontar pro pai
            p = &((*p)->pChild[(*p)->data < x]);
        }
        return false;
    }

    void print(Node *p, int indent=0) {
        if (p) {
            print(p->pChild[1], indent+4);
            cout << setw(indent) << ' ';
            //cout<< p->data << ":" << p->color;
//            if (p->pParent)
//				cout << ":" << (p->pParent)->data << endl;
//			else
//				cout << endl;
			cout << p->data;
			if (p->color == 'b') cout << ".";
			cout << endl;
            print(p->pChild[0], indent+4);
        }
    }
    
    Node** parent(Node** p) {
    	Node** pParent = &((*p)->pParent);
    	return pParent;
    }
    
    Node** grandpa(Node** p) {
    	Node** pGrandpa = parent(parent(p));
    	return pGrandpa;
    }
    
    Node** uncle(Node** p) {
    	Node** pParent = parent(p);
    	Node** pGrandpa = parent(pParent);
    	Node** pUncle;
    	if ((*pGrandpa)->pChild[0] == *pParent) pUncle = &((*pGrandpa)->pChild[1]);
    	else pUncle = &((*pGrandpa)->pChild[0]);
    	return pUncle;
    }
    
    Node** sibling(Node** p) {
    	Node** pParent = parent(p);
    	if (*pParent) {
    		Node** pSibling = &((*pParent)->pChild[(*pParent)->pChild[0] == *p]);
    		return pSibling;
    	}
    	else
    		return nullptr;
	}
    
    void change_color(Node** p) {
    	if ((*p)->color == 'b') (*p)->color = 'r';
    	else  (*p)->color = 'b';
    }
    
    void recolor(Node** p) {
        if (*p == pRoot) {		//Recolor no root
        	insert1(p);
		}
		else if ((*parent(p))->color == 'b') insert2();	//Caso em que o n� pai � preto
		else if (*uncle(p)) {
			if ((*uncle(p))->color == 'r') {	//Caso em que os n�s pai e uncle s�o vermelhos
				insert3(p);
			} else {
				insert4_step1(p);
			}
		} else {
			insert4_step1(p);
		}
	}
};

int main() {
  // this constructor must call the function insert multiple times 
  // respecting the order
  RBTree tree(41, 38, 31, 12, 19, 8);
  tree.print();

  // testing the remove function
  tree.remove(8);
  tree.print();
}
