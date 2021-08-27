#ifndef DATABASE_H
#define DATABASE_H

#include "Account.h"
#include <mysql.h>
#include <iostream>
#include <unordered_map>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>




class Database
{
	public: 
		Database(); 
		~Database();
		void ReadAccountFile();
		void cleanUpOlddata (); 
		void ReadTranscationFile();
		void ReadTranscationInfo(unordered_map<int, Account*>& user_account_map);
		void readAccontInfo(unordered_map<int, Account*>& user_account_map);
		void murchangAvgPrice(unordered_map<string, double>& avg_price); 

	private: 
		string cleanMarchantDetails(string merchantDeatils); 
		string getState(string merchantDeatils); 
		ofstream logFile;
		

};
#endif 

