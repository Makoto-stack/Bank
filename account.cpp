#include "account.h"

using namespace std;

//insertion operator for account
ostream& operator<<(ostream& Out, const Account& Acc) {
	Out << Acc.AccountName << " Acc#:" << Acc.AccountNum << endl;
	for (int i = 0 ; i <= 9; i++)
	    Out << Acc.MyFund[i].FundName << ": $" << Acc.MyFund[i].Balance << endl;
	return Out;
}

//constructor creates account from transaction
Account::Account(Transaction* T) {
	AccountName = T->getAccountName();
	AccountNum = T->getAccountNum();
    MyFund[0].FundName = "Money Market";
    MyFund[1].FundName = "Prime Money Market";
    MyFund[2].FundName = "Long-Term Bond";
    MyFund[3].FundName = "Short-Term Bond";
    MyFund[4].FundName = "500 Index Fund";
    MyFund[5].FundName = "Capital Value Fund";
    MyFund[6].FundName = "Growth Equity Fund";
    MyFund[7].FundName = "Growth Index Fund";
    MyFund[8].FundName = "Value Fund";
    MyFund[9].FundName = "Value Stock Index";
}

//destructor wipes dynamically allocated transaction history
Account::~Account(){
    for (int i = 0; i <= 9; ++i) {
        for (auto it = MyFund[i].TransactionHistory.begin();
             it != MyFund[i].TransactionHistory.begin(); ++it)
            delete *it;
    }
}

//returns account number
int Account::getAccountNum() {
    return AccountNum;
}

//process transactions based on type, calls appropriate helper functions
bool Account::processTransaction(Transaction* T) {
    bool Successful = false;

	if (T->getTransactionType() == 'D')
        Successful = processDeposit(T);
	
	if (T->getTransactionType() == 'W')
        Successful = processWithdrawal(T);
	
	if (T->getTransactionType() == 'T')
        Successful = processTransfer(T);
	
	if (T->getTransactionType() == 'H')
        Successful = displayHistory(T);

	if (Successful)
        T->setTransactionSuccess(Successful);
	if(T->getTransactionType() != 'H')
        MyFund[T->getFundNum()].TransactionHistory.push_back(T);
	return Successful;
}

//process transfers, contingent on both accounts and fund types
bool Account::processTransfer(Transaction* T) {
    int FundNumToBeWithdrawn = T->getFundNum();
    int FundNumToBeDeposited = T->getTransferAccountNum();
    if (FundNumToBeDeposited != FundNumToBeWithdrawn){
        return processWithdrawal(T);
    } else {
        if ((FundNumToBeWithdrawn == 0 && FundNumToBeDeposited == 1) || 
        (FundNumToBeWithdrawn == 1 && FundNumToBeDeposited == 0) ||
        (FundNumToBeWithdrawn == 2 && FundNumToBeDeposited == 3) || 
        (FundNumToBeWithdrawn == 3 && FundNumToBeDeposited == 2)) {
            if (MyFund[FundNumToBeWithdrawn].Balance >= T->getTransactionAmount()){
                MyFund[FundNumToBeWithdrawn].Balance -= T->getTransactionAmount();
                MyFund[FundNumToBeDeposited].Balance += T->getTransactionAmount();
                return true;
            }
            return false;
        } else {
           if (processWithdrawal(T)){
               MyFund[FundNumToBeDeposited].Balance += T->getTransactionAmount();
               return true;
            }
           return false;
        }
    }
}

//process withdrawals
bool Account::processWithdrawal(Transaction* T) {
    if (T->getFundNum() == 0) {
        if (T->getTransactionAmount() <= MyFund[0].Balance) {
            MyFund[0].Balance -= T->getTransactionAmount();
            return true;
        }
        if (T->getTransactionAmount() <= MyFund[0].Balance + MyFund[1].Balance) {
            int Supplement = T->getTransactionAmount() - MyFund[0].Balance;
            MyFund[0].Balance = 0;
            MyFund[1].Balance -= Supplement;
            return true;
        }
        return false;
    }
    if (T->getFundNum() == 1) {
        if (T->getTransactionAmount() <= MyFund[1].Balance) {
            MyFund[1].Balance -= T->getTransactionAmount();
            return true;
        }
        if (T->getTransactionAmount() <= MyFund[1].Balance + MyFund[0].Balance) {
            int Supplement = T->getTransactionAmount() - MyFund[1].Balance;
            MyFund[1].Balance = 0;
            MyFund[0].Balance -= Supplement;
            return true;
        }
        return false;
    }
    if (T->getFundNum() == 2) {
        if (T->getTransactionAmount() <= MyFund[2].Balance) {
            MyFund[2].Balance -= T->getTransactionAmount();
            return true;
        }
        if (T->getTransactionAmount() <= MyFund[2].Balance + MyFund[3].Balance) {
            int Supplement = T->getTransactionAmount() - MyFund[2].Balance;
            MyFund[2].Balance = 0;
            MyFund[3].Balance -= Supplement;
            return true;
        }
        return false;
    }
    if (T->getFundNum() == 3) {
        if (T->getTransactionAmount() <= MyFund[3].Balance) {
            MyFund[3].Balance -= T->getTransactionAmount();
            return true;
        }
        if (T->getTransactionAmount() <= MyFund[3].Balance + MyFund[2].Balance) {
            int Supplement = T->getTransactionAmount() - MyFund[3].Balance;
            MyFund[3].Balance = 0;
            MyFund[2].Balance -= Supplement;
            return true;
        }
        return false;
    }
    if (T->getTransactionAmount() > MyFund[T->getFundNum()].Balance) {
        return false;
    }
    MyFund[T->getFundNum()].Balance -= T->getTransactionAmount();
    return true;
}

//process deposits
bool Account::processDeposit(Transaction* T) {
    MyFund[T->getFundNum()].Balance += T->getTransactionAmount();
    return true;
}

//displays history of whole account or fund if specified
bool Account::displayHistory(Transaction *T) {
    if (T->getFundNum() == -1){
        cout << "Printing Transaction History for: " 
			<< AccountName << " By Fund" << endl;
        for (int i = 0; i <= 9; ++i) {
            cout << MyFund[i].FundName << ": $" << MyFund[i].Balance << endl;
            for (auto & it : MyFund[i].TransactionHistory){
                cout << *it << endl;
            }
        }
    } else {
        cout << "Printing Transaction History of: "<< AccountName
            << " for fund: " << MyFund[T->getFundNum()].FundName << endl;
        for (auto & it : MyFund[T->getFundNum()].TransactionHistory) {
            cout << *it << endl;
        }

    }

    return false;
}
