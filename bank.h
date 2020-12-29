
#ifndef ASS5_BANK_H
#define ASS5_BANK_H

#include "accounttree.h"
#include <fstream>
#include <string>
#include <queue>
#include "transaction.h"

using namespace std;

class Bank {
public:
	//constructor
	Bank();
	//destructor
	~Bank();
	/*Creates and fills the transaction queue and 
	then exexcutes the individual transactions objects*/
	void processTransactions(const string &FileName);
	//displays all accounts contained in the bank's Acc Tree
	void displayAllBankBalances() const;

private:
  AccountTree Accounts;
  queue<Transaction*> TransactionQueue;

};
#endif // ASS5_BANK_H
