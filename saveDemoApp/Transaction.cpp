#include "Transaction.h"


Transaction::Transaction(
		int account_number,
		string transaction_datetime,
		double transaction_amount,
		string post_date,
		string merchant_number,
		string merchant_description,
		string transaction_state, 
		int merchant_category_code,
		int transaction_number): 
	 account_number (account_number),
	 transaction_datetime (transaction_datetime),
	 transaction_amount (transaction_amount),
	 post_date (post_date),
	 merchant_number (merchant_number),
	 merchant_description (merchant_description),
	 transaction_state(transaction_state),
	 merchant_category_code (merchant_category_code),
	transaction_number(transaction_number){

}




Transaction::~Transaction() {
	
}




int Transaction:: get_account_number() {

	return this->account_number; 
}


string Transaction::get_transaction_datetime() {

	return this->transaction_datetime;
}



double Transaction:: get_transaction_amount() {

	return this->transaction_amount;
}

string Transaction::get_post_date() {

	return this->post_date;
}

string Transaction::get_merchant_number() {
	return this->merchant_number;
}

string Transaction::get_merchant_description() {

	return this->merchant_description;
}

string Transaction::get_transaction_state() {

	return this->transaction_state;
}

int Transaction::get_merchant_category_code() {

	return this->merchant_category_code; 
}


int Transaction::get_transaction_number() {

	return this->transaction_number; 

}






