#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
using namespace std; 

class Transaction
{
	public:
		Transaction(
			int account_number,
			string transaction_datetime,
			double transaction_amount,
			string post_date,
			string merchant_number,
			string merchant_description,
			string transaction_state,
			int merchant_category_code,
			int transaction_number); 
		~Transaction(); 
		int get_account_number();
		string get_transaction_datetime ();
		double get_transaction_amount ();
		string get_post_date ();
		string get_merchant_number ();
		string get_merchant_description();
		string get_transaction_state ();
		int get_merchant_category_code ();
		int get_transaction_number ();


	private:
		int account_number; 
		string transaction_datetime;
		double transaction_amount;
		string post_date;
		string merchant_number;
		string merchant_description;
		string transaction_state; 
		int merchant_category_code; 
		int transaction_number; 

};
#endif 
