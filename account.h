
#ifndef ASS5_ACCOUNT_H
#define ASS5_ACCOUNT_H

#include "transaction.h"
#include <ostream>
#include <list>

using namespace std;

class Account {
	//insertion operator for account
	friend ostream& operator<<(ostream& Out, const Account& Acc);
public:
	//constructor creates account from transaction
	explicit Account(Transaction* T);
	//destructor wipes dynamically allocated transaction history
	~Account();
	//process transactions based on type, calls appropriate helper functions
	bool processTransaction(Transaction* T);
	//returns account number
	int getAccountNum();
private:
	//struct funds holds a fund name, balance, and history for that fund
	struct Funds 
	{string FundName; int Balance = 0; list<Transaction*> TransactionHistory; };
	//process transfers, contingent on both accounts and fund types
	bool processTransfer(Transaction* T);
	//process withdrawals
	bool processWithdrawal(Transaction* T);
	//process deposits
	bool processDeposit(Transaction* T);
	//displays history of whole account or fund if specified
	bool displayHistory(Transaction* T);
	string AccountName;
	int AccountNum;
	Funds MyFund[10];
};
#endif // ASS5_ACCOUNT_H
