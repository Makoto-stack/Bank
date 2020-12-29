#ifndef transaction_h
#define transaction_h

#include <iostream>
#include <string>
using namespace std;

class Transaction {
	//Overloads the ostream << operator to print out transaction objects
	//Using more expressive out statements to make debugging easier
	friend ostream& operator<<(ostream& Out, const Transaction& Acc);
public:
	/*Constructor for Transaction class takes a TransactionString and parses the
	information into relevant private variables*/
	explicit Transaction(string TransactionString);
	//returns transaction type
	char getTransactionType();

	//returns account number
	int getAccountNum();
	//returns fund number
    int getFundNum();
	//returns account name
	string getAccountName();
	//returns transfer account number
	int getTransferAccountNum();
	//returns transfer account number
	int getTransferFundNum();
	//returns transaction amount
	int getTransactionAmount();
	//indicates whether transaction succeeded or not
	void setTransactionSuccess(bool Successful);

private:
    string AccountName = "blank";
	char TransactionType = ' ';
    bool TransactionSuccess = false;

	int AccountNum = -1;
    int FundNum = -1;

	int TransferAccountNum = -1;
	int TransferFundNum = -1;
	int TransactionAmount = -1;

};
#endif