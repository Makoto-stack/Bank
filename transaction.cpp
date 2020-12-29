#include "transaction.h"

//Overloads the ostream << operator to print out transaction objects
//Using more expressive out statements to make debugging easier
ostream& operator<<(ostream& Out, const Transaction& Acc) {
    if (Acc.TransactionType == 'O') {
        Out << "Type: " << Acc.TransactionType << " Acc Name: " 
		<< Acc.AccountName << " Acc#: " << Acc.AccountNum;
    }
    if (Acc.TransactionType == 'W' || Acc.TransactionType == 'D') {
        Out << "Type: " << Acc.TransactionType << " Acc#: " << Acc.AccountNum 
		<< " Fund: " << Acc.FundNum << " Amount: " << Acc.TransactionAmount;
        if (!Acc.TransactionSuccess) {
            Out << " (failed)";
        }
    }
    if (Acc.TransactionType == 'T') {
        Out << "Type: " << Acc.TransactionType << " Acc#: " << Acc.AccountNum <<
		" Fund: " << Acc.FundNum << " Amount: " << Acc.TransactionAmount << " Acc#: "
		<< Acc.TransferAccountNum << " Fund: " << Acc.TransferFundNum;
        if (!Acc.TransactionSuccess) {
            Out << " (failed)";
        }
    }
    if (Acc.TransactionType == 'H') {
        Out << "Type: " << Acc.TransactionType << " " << Acc.AccountNum;
        if (Acc.FundNum != -1)
            Out << Acc.FundNum;
        if (!Acc.TransactionSuccess){
            Out << " (failed)";
        }
    }
    return Out;
}

/*Constructor for Transaction class takes a TransactionString and parses the
	information into relevant private variables*/
Transaction::Transaction(string TransactionString) {
    TransactionType = TransactionString.front();
    std::string delimiter = " ";
    int start = 2;
    int end = TransactionString.find(delimiter, start);
    if (TransactionType == 'O' ) {
        end = TransactionString.find(delimiter, end + 1);
        AccountName = TransactionString.substr (start, end - start);
        start = (end + 1);
        AccountNum = stoi(TransactionString.substr (start, (end - start - 1)));
    }
    if (TransactionType == 'W' || TransactionType == 'D') {
        AccountNum = stoi(TransactionString.substr (start, (end - start - 1)));
        FundNum = stoi(TransactionString.substr (start + 4, 1));
        start = (end + 1);
        TransactionAmount = 
		stoi(TransactionString.substr (start, (TransactionString.size() - 8)));
    }
    if (TransactionType == 'T') {
        AccountNum = stoi(TransactionString.substr (start,(end - start - 1)));
        FundNum = stoi(TransactionString.substr (start + 4, 1));
        start = (end + 1);
        end = TransactionString.find(delimiter, start);
        TransactionAmount = stoi(TransactionString.substr (start, (end - start)));
        start = (end + 1);
        TransferAccountNum = stoi
		(TransactionString.substr(start, (TransactionString.size() - start - 1)));
        TransferFundNum = stoi(TransactionString.substr(TransactionString.size()-1,1));
    }
    if (TransactionType == 'H') {

        if (TransactionString.size() == 6) {
            AccountNum = 
			stoi(TransactionString.substr(start, (TransactionString.size() - start)));
        } else {
            AccountNum = stoi
			(TransactionString.substr(start, ((TransactionString.size() - 1) - start)));
            FundNum = stoi(TransactionString.substr(start + 4, 1));
        }
    }
}

//returns transaction type
char Transaction::getTransactionType() {
	return TransactionType;
}

//returns account number
int Transaction::getAccountNum() {
	return AccountNum;
}

//returns account name
string Transaction::getAccountName() {
	return AccountName;
}

//returns transfer account number
int Transaction::getTransferAccountNum() {
	return TransferAccountNum;
}

//returns transction amount
int Transaction::getTransactionAmount() {
	return TransactionAmount;
}

//returns fund number
int Transaction::getFundNum(){
    return FundNum;
}

//returns transfer fund number
int Transaction::getTransferFundNum() {
    return TransferFundNum;
}

//indicates whether transaction succeeded or not
void Transaction::setTransactionSuccess(bool Successful) {
    TransactionSuccess = Successful;
}
