#include "accounttree.h"

//create BST
AccountTree::AccountTree() = default;

// Delete all nodes in BST
AccountTree::~AccountTree() {
    clear();
}

// Insert new account
bool AccountTree::insert(Account *Account) {
    Node* Parent = Root;
    Node* NewAccountNode = new Node(Account);
    if(isEmpty()){
        Root = NewAccountNode;
        return true;
    }
    Parent = findNode(Parent, NewAccountNode->Acc->getAccountNum());
    if (Parent->Acc->getAccountNum() == NewAccountNode->Acc->getAccountNum()){
        delete NewAccountNode->Acc;
        delete NewAccountNode;
        return false;
    } else {
        if (Parent->Acc->getAccountNum() > NewAccountNode->Acc->getAccountNum())
            Parent->Left = NewAccountNode;
        else
            Parent->Right = NewAccountNode;
    }
    return true;
}

//finds a node given a parent and account number
AccountTree::Node* AccountTree::
findNode(Node* Parent, const int &AccountNum) const {
    if (Parent->Acc->getAccountNum() == AccountNum)
        return Parent;
    if (Parent->Acc->getAccountNum() > AccountNum){
        if (Parent->Left == nullptr) {
            return Parent;
        } else {
            return findNode(Parent->Left, AccountNum);
        }
    } else {
        if (Parent->Right == nullptr) {
            return Parent;
        } else {
            return findNode(Parent->Right, AccountNum);
        }
    }
}

// Retrieve account
// returns true if successful AND *Acc points to account
bool AccountTree::retrieve(const int &AccountNumber, Account *&Account) const {
    Node *Node = findNode(Root, AccountNumber);
    if (Node->Acc->getAccountNum() != AccountNumber){
        return false;
    } else {
        Account = Node->Acc;
        return true;
    }
}

// Display information on all accounts
void AccountTree::display() const {
	displayNodes(Root);
}

//display nodes using inorder traversal
void AccountTree::displayNodes(Node* N) const{
	if (N != nullptr) {
		displayNodes(N->Left);
		cout << *N->Acc << endl;
		displayNodes(N->Right);
	}
}

// delete all information in AccountTree
void AccountTree::clear() {
    deleteNodes(Root);
}

//deletes nodes and the accounts within them
void AccountTree::deleteNodes(Node* N) {
    if (N != nullptr) {
        deleteNodes(N->Left);
        deleteNodes(N->Right);
        Account* A = N->Acc;
        delete A;
        delete N;
    }
}

// check if tree is empty
bool AccountTree::isEmpty() const {
  return Root == nullptr;
}


