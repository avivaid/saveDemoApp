// MySqlTest.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include "Database.h"
#include <iomanip>


using namespace std;


int main()
{
	Database db;
	cout << "Cleaning old data from database" << endl; 
	db.cleanUpOlddata(); 	
	cout << "Loading user_accont file to database" << endl;
	db.ReadAccountFile();
	cout << "Loading transcation file to database" << endl;
	db.ReadTranscationFile();
	cout << "========================================DATA LOADED ================" << endl; 
	unordered_map<int, Account*> user_account_map; 
	db.readAccontInfo(user_account_map); 
	db.ReadTranscationInfo(user_account_map);
	vector <Transaction*> flagedTranscationState;
	vector <Transaction*> flagedTranscationAmt;
	unordered_map<string, double> avg_price;
	db.murchangAvgPrice(avg_price);

	for (auto iter = user_account_map.begin(); iter != user_account_map.end(); iter++) {

		for (int i = 0; i < iter->second->get_user_transaction()->size(); i++) {
			if (iter->second->get_single_transaction(i)->get_transaction_state() != iter->second->get_state()) {
				flagedTranscationState.push_back(iter->second->get_single_transaction(i));
			}
			double price = avg_price.find(iter->second->get_single_transaction(i)->get_merchant_number())->second; 
			string tex  = avg_price.find(iter->second->get_single_transaction(i)->get_merchant_number())->first;

			if (iter->second->get_single_transaction(i)->get_transaction_amount() > (2 * price)) {
				flagedTranscationAmt.push_back(iter->second->get_single_transaction(i));
				cout << tex << "   "<< price << endl;
			}
		}// for state
	}// for 
	




	cout << endl;

	cout << "================RULE  1 REPORT =======================================================" << endl;
	cout << endl;
	cout << "Name" << setw(45)  << "Account Number" << setw(20) << "Transaction Number" << setw(10) << "Merchant" << setw(60) << "Transaction Amount" << endl;
	for (int i = 0; i < flagedTranscationAmt.size(); i++) {
		auto user = user_account_map.find(flagedTranscationAmt[i]->get_account_number());
		string fullName = user->second->get_first_name() + " " + user->second->get_last_name(); 
		cout << fullName << right << setw(40 - fullName.length()) 
			<< flagedTranscationAmt[i]->get_account_number()
			<<setw(15)	<< flagedTranscationAmt[i]->get_transaction_number() 
			  <<setw(50) << flagedTranscationAmt[i]->get_merchant_description()
		  	<<  setw(30)  << "$"<<  flagedTranscationAmt[i]->get_transaction_amount()
		<< endl; 

	}// for 
	cout << endl;
	cout << "===================================RULE  2 REPORT========================================================" << endl; 
	cout << endl;
	cout << "Name" << setw(45) << "Account Number " << setw(25) << "Transaction Number " << setw(30) << "Expected Transaction Location " << setw(30) << "Actual Transaction Location" << endl;
	for (int i = 0; i < flagedTranscationState.size(); i++) {
		auto user = user_account_map.find(flagedTranscationState[i]->get_account_number());
		string fullName = user->second->get_first_name() + " " + user->second->get_last_name();
		cout << fullName  << setw(40 - fullName.length()) << right
			<< flagedTranscationState[i]->get_account_number() 
			<< setw(32) <<right << flagedTranscationState[i]->get_transaction_number()
			<< setw(30) << right<< user->second->get_state()
			<< setw(32) << right << flagedTranscationState[i]->get_transaction_state()
			<< endl;

	}// for 

	ofstream report("report.txt"); 
		if (!report.is_open()) {
			cout << "Can not open the report file " << endl; 
		}
		else {
			report << "===================================RULE  1 REPORT========================================================" << endl;
			report << "Name" << setw(45) << "Account Number" << setw(20) << "Transaction Number" << setw(10) << "Merchant" << setw(60) << "Transaction Amount" << endl;
			for (int i = 0; i < flagedTranscationAmt.size(); i++) {
				auto user = user_account_map.find(flagedTranscationAmt[i]->get_account_number());
				string fullName = user->second->get_first_name() + " " + user->second->get_last_name();
				report << fullName << right << setw(40 - fullName.length())
					<< flagedTranscationAmt[i]->get_account_number()
					<< setw(15) << flagedTranscationAmt[i]->get_transaction_number()
					<< setw(50) << flagedTranscationAmt[i]->get_merchant_description()
					<< setw(30) <<"$"<< flagedTranscationAmt[i]->get_transaction_amount()
					<< endl;

			}// for 
			cout << endl;
			report << "===================================RULE 2 REPORT========================================================" << endl;
			cout << endl;
			report << "Name" << setw(45) << "Account Number " << setw(25) << "Transaction Number " << setw(30) << "Expected Transaction Location " << setw(30) << "Actual Transaction Location" << endl;
			for (int i = 0; i < flagedTranscationState.size(); i++) {
				auto user = user_account_map.find(flagedTranscationState[i]->get_account_number());
				string fullName = user->second->get_first_name() + " " + user->second->get_last_name();
				report << fullName << setw(40 - fullName.length()) << right
					<< flagedTranscationState[i]->get_account_number()
					<< setw(32) << right << flagedTranscationState[i]->get_transaction_number()
					<< setw(30) << right << user->second->get_state()
					<< setw(32) << right << flagedTranscationState[i]->get_transaction_state()
					<< endl;
			}// for 
		}// else 
		report.close(); 

	// CLEANUP	
	for (auto iter = user_account_map.begin(); iter != user_account_map.end(); iter++) {
		delete iter->second; 
	}// for 

	
	return 0;

}
// MySqlTest.cpp : Defines the entry point for the console application.
//

