#include "Account.h"


Account::Account(
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

	int account_number) :
		first_name (first_name), 
		last_name(last_name), 
		 street_address(street_address),
		 unt(unt),
		 city(city),
		 state(state),
		 zip(zip),
		 dob(dob),
		 ssn(ssn),
		 email_address(email_address),
		 mobile_number(mobile_number),
		 account_number(account_number){}


	Account::~Account() {
		for (int i = 0; i < user_transaction.size(); i++) {
			delete user_transaction[i]; 
		}// for 


	}// for


	vector <Transaction*>*  Account::get_user_transaction() {
		return &user_transaction;
	};


	string 	Account::get_first_name() {
		return first_name; 
	}


	string 	Account::get_last_name() {
		return last_name;
	}

	string 	Account::get_street_address() {
		return street_address; 
	}
	string 	Account::get_unt() {
		return unt; 
	}
	string 	Account::get_city() {
		return city;
	}
	string 	Account::get_state() {
		return state; 
	}
	int Account::get_zip() {
		return zip;
	}
	string	Account::get_dob() {
		return dob; 
	}	
	string 	Account::get_ssn() {
		return ssn;
	}
	string 	Account::get_email_address() {
		return email_address;
	}
	string Account::get_mobile_number() {
		return mobile_number;
	}

	int Account::get_account_number() {
		return this->account_number;
	}


	Transaction* Account::get_single_transaction(int i) {
		if (i >= this->user_transaction.size()) {
			return nullptr; 
		}
		else {
			return this->user_transaction[i]; 
		}
	}






