
#ifndef ASS5_ACCOUNTTREE_H
#define ASS5_ACCOUNTTREE_H

#include "account.h"
#include <iostream>

class AccountTree {
public:
  // Create BST
  AccountTree();

  // Delete all nodes in BST
  ~AccountTree();

  // Insert new account
  bool insert(Account *Account);

  // Retrieve account
  // returns true if successful AND *Acc points to account
  bool retrieve(const int &AccountNumber, Account *&Account) const;

  // Display information on all accounts
  void display() const;

  // delete all information in AccountTree
  void clear();

  // check if tree is empty
  bool isEmpty() const;

private:
    struct Node {
  public:
    explicit Node(Account *A)
        : Acc{A}, Right{nullptr}, Left{nullptr} {};
    Account* Acc;
    Node* Right;
    Node* Left;
  };
  Node *Root = nullptr;

  //display nodes using inorder traversal
  void displayNodes(Node* N) const;
  //deletes nodes and the accounts within them
  static void deleteNodes(Node* N);
  //finds a node given a parent and account number
  Node * findNode(Node* Parent, const int &AccountNum) const;
};
#endif // ASS5_ACCOUNTTREE_H
