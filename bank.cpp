
#include "bank.h"

//constructor
Bank::Bank() = default;
//destructor
Bank::~Bank() = default;

/*Creates and fills the transaction queue and
then exexcutes the individual transactions objects*/
void Bank::processTransactions(const string &FileName) {
    string line;
    ifstream BankTransactionLog(FileName);
    if (BankTransactionLog.is_open()){
        while( getline (BankTransactionLog, line)){
            auto* T = new Transaction(line);
            TransactionQueue.push(T);
        }
        BankTransactionLog.close();
    } else {
        cout << "ERROR: Unable to open file: " << FileName << endl;
    }
    while (!TransactionQueue.empty()){
        Transaction* T = TransactionQueue.front();
        TransactionQueue.pop();
        if (T->getTransactionType() == 'O'){
            auto* A = new Account(T);
            if(!Accounts.insert(A))
                cout << "Error: Acc#: " << A->getAccountNum() << " Already exists!" << endl;
        } else if (T->getTransactionType() == 'T') {
            Account *Send;
            int AccountNumberSend = T->getAccountNum();
            int FundNumberSend = T->getFundNum();
            if (!Accounts.retrieve(AccountNumberSend, Send)) {
                cout << "Error: Acc#: " << AccountNumberSend << " Does Not Exist!" << endl;
                continue;
            }

            int ValueTransfer = T->getTransactionAmount();

            Account *Receive;
            int AccountNumberReceive = T->getTransferAccountNum();
            int FundNumberReceive = T->getTransferFundNum();
            if (!Accounts.retrieve(AccountNumberReceive, Receive)){
                cout << "Error: Acc#: " << AccountNumberReceive << " Does Not Exist!" << endl;
                continue; //Needs throw error
            }
            if (FundNumberSend != FundNumberReceive) {
                if (!Send->processTransaction(T))
                    continue;
                string Deposit = "D " + to_string(AccountNumberReceive) + 
				to_string(FundNumberReceive) + " " + to_string(ValueTransfer);
                auto* D = new Transaction(Deposit);
                Receive->processTransaction(D);
            }else {
                if (!Send->processTransaction(T)){
                    cout << "Insufficient Amount in Acc# " << Send->getAccountNum()
                        << " in fund #" << FundNumberSend << endl;
                    continue;
                }
            }
        } else if(T->getTransactionType() == 'W' ||
		T->getTransactionType() == 'D' || 
		T->getTransactionType() == 'H') {
            Account* A;
            int AccountNumber = T->getAccountNum();
            Accounts.retrieve(AccountNumber,A);
            A->processTransaction(T);
        }
    }
}

//displays all accounts contained in the bank's Acc Tree
void Bank::displayAllBankBalances() const {
	Accounts.display();
}


