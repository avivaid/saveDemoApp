#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <vector>
#include "Transaction.h"
using namespace std; 




class Account
{
	public: 
		Account( 
			string first_name,
			string last_name,
			string street_address,
			string unt,
			string city,
			string state, 
			int zip,
			string dob,
			string ssn,
			string email_address,
			string mobile_number,
			int account_number); 

		~Account(); 
		string get_first_name(); 
		string get_last_name();
		string get_street_address();
		string get_unt();
		string get_city();
		string get_state();
		int get_zip();
		string get_dob(); 
		string get_ssn();
		string get_email_address();
		vector <Transaction*>* get_user_transaction();
		Transaction* get_single_transaction(int i);


		int get_account_number();
		string get_mobile_number();





	private: 
		string first_name;
		string last_name;
		string street_address;
		string unt;
		string city;
		string state;
		int zip; 
		string dob;
		string ssn;
		string email_address;
		string mobile_number; 
		int account_number; 
		vector <Transaction*> user_transaction; 
		
	








};
#endif 
