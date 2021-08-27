#include "Database.h"



Database::Database() {

	 logFile.open("database_log.txt");
	 if (!logFile.is_open()) {
		 cout << "Error opening the database logs " << endl; 
	 }

}



Database::~Database() {
	logFile.close(); 

}


void Database:: ReadTranscationFile() {
	MYSQL* conn = mysql_init(0);
	int linenuber = 0;
	int qstate; 
	ifstream inputFile("transactions.csv");
	if (!inputFile.is_open()) {
		cout << "Error opeing file account_info.csv" << endl;
	}
	else {
		conn = mysql_real_connect(conn, "localhost", "root", "password", "save", 3306, NULL, 0);
		if (conn) {
			string line = "";
			vector<string> row;
			// Disregarding the headers 
			getline(inputFile, line);
			linenuber++;
			while (!inputFile.eof()) {
				line = "";
				linenuber++;
				getline(inputFile, line);
				stringstream ss(line);
				string word = "";
				row.clear();
				while (getline(ss, word, ',')) {
					row.push_back(word);
				}// while
				if (row[0] == "") {
					logFile << "Query Failure: Primary key can not be null  at line number in csv " << linenuber << endl;
					continue;
				}// if 
				else {
					string state = getState(row[5]);
					row[5] = cleanMarchantDetails(row[5]);
					string query = "INSERT INTO user_transcation VALUES (";
					query += row[0] + ','
						+ "STR_TO_DATE(" + "'" + row[1] + "' ,'%m%d%Y %H:%i:%s') ,"
						+ row[2].substr(0, row[2].size() - 1) + ","
						+ "STR_TO_DATE(" + "'" + row[3] + "' ,'%m%d%Y') ,"
						+ '"' + row[4] + '"' + ','
						+ '"' + row[5] + '"' + ','
						+ '"' + state + '"' + ','
						+ row[6] + ','
						+ row[7] + ");";

					qstate = mysql_query(conn, query.c_str());
					if (!qstate)
					{
						logFile << "Query Sucess: " << query << " line number in csv " << linenuber << endl;

					}// if
					else
					{
						cout << "Query failed: " << mysql_error(conn) << endl;
						logFile << "Query failed: " << mysql_error(conn) << " line number in csv " << linenuber << endl;
						cout << query << endl;
					}// else

				}// else 
			}// while 
			inputFile.close();
			logFile << "==========================================================" << endl;
			logFile.close();
		}// if
		else {
			cout << "Connection to database has failed!" << endl;
		}// else

	}// else 
}//ReadTranscationFile


void Database:: ReadAccountFile() {
	MYSQL* conn = mysql_init(0);
	int linenuber = 0; 
	int qstate;
	ifstream inputFile("account_info.csv");
	if (!inputFile.is_open()) {
		cout << "Error opeing file account_info.csv" << endl;
	}//if 
	else {
		conn = mysql_real_connect(conn, "localhost", "root", "password", "save", 3306, NULL, 0);
		if (conn) {
			string line = "";
			vector<string> row;
			// Disregarding the headers 
			getline(inputFile, line);
			linenuber++;
			while (!inputFile.eof()) {
				line = "";
				linenuber++; 
				getline(inputFile, line);
				stringstream ss(line);
				string word = "";
				row.clear();
				while (getline(ss, word, ',')) {
					row.push_back(word);
				}// while
				if (row[11] == "") {
					logFile << "Query Failure: Primary key can not be null  at line number in csv " << linenuber << endl;
					continue;
				}// if 
				else {
					string query = "INSERT INTO user_account VALUES (";
					query += '"' + row[0] + '"' + ',' +
						'"' + row[1] + '"' + ',' +
						'"' + row[2] + '"' + ',' +
						'"' + row[3] + '"' + ',' +
						'"' + row[4] + '"' + ',' +
						'"' + row[5] + '"' + ',' +
						row[6] + ',' +
						"STR_TO_DATE(" + '"' + row[7] + '"' + "," + '"' + "%m/%d/%Y" + '"' + ") , " +
						'"' + row[8] + '"' + ',' +
						'"' + row[9] + '"' + ',' +
						row[10] + ',' +
						row[11] + ");";
					const char* q = query.c_str();
					qstate = mysql_query(conn, q);
					if (!qstate)
					{
						logFile << "Query Sucess: "<< query <<"line number in csv " << linenuber << endl;
						
					}// if
					else
					{
						cout << "Query failed: " << mysql_error(conn) << endl;
						logFile << "Query failed: " << mysql_error(conn) << " line number in csv "<<linenuber << endl;
						cout << query << endl;
					}// else 
				}// else 
			}// while 
			inputFile.close();
			logFile << "==========================================================" << endl;
		}// if
		else {
			cout<< "Connection to database has failed!"<<endl;
		}// else
	}// else 
}//ReadAccountFile

void Database::readAccontInfo(unordered_map<int, Account*>& user_account_map) {

	MYSQL* conn;
	int qstate; 
	MYSQL_ROW row;
	MYSQL_RES* res;
	conn = mysql_init(0);

	conn = mysql_real_connect(conn, "localhost", "root", "password", "save", 3306, NULL, 0);

	if (conn) {
		string query = "SELECT * FROM user_account";
		qstate = mysql_query(conn, query.c_str());
		if (!qstate)
		{
			res = mysql_store_result(conn);
			logFile << "Query Sucess : " << query << endl;
			while (row = mysql_fetch_row(res))
			{
				Account* user_account = new Account(
					row[0], row[1], row[2], row[3], row[4], row[5], stoi(row[6]), 
					row[7], row[8], row[9], row[10], stoi(row[11])); 
					user_account_map.insert({ user_account->get_account_number(), user_account }); 
					
			}// while 
		}// if 
		else
		{
			logFile << "Query failed: " << mysql_error(conn)   << endl;
		}// else 
	}// if 
	else {
		cout<< "Connection to database has failed!"<<endl;
	}// else 
	logFile << "==========================================================" << endl;
}//readAccontInfo

void Database::ReadTranscationInfo(unordered_map<int, Account*>& user_account_map) {

	MYSQL* conn;
	int qstate;
	MYSQL_ROW row;
	MYSQL_RES* res;
	conn = mysql_init(0);

	conn = mysql_real_connect(conn, "localhost", "root", "password", "save", 3306, NULL, 0);

	if (conn) {
		string query = "SELECT * FROM user_transcation ";
		qstate = mysql_query(conn, query.c_str());
		if (!qstate)
		{
			res = mysql_store_result(conn);
			logFile <<"Query Sucess : "<<  query << endl;
			while (row = mysql_fetch_row(res))
			{
				Transaction* user_transaction = new Transaction(
					stoi(row[0]), row[1], stod(row[2]), row[3], row[4], row[5], row[6],
					stoi(row[7]), stoi(row[8]));
					auto user = user_account_map.find(user_transaction->get_account_number());
					if (user == user_account_map.end()) {
						cout << "User with account number " << user_transaction->get_account_number() << " not found" << endl; 
					}// if 
					else {
						user->second->get_user_transaction()->push_back(user_transaction);
					}// else 
				}// while 
		}// if 
		else
		{
			logFile << "Query failed: " << mysql_error(conn)  << endl;
		}// else 
	}// if
	else {
		cout << "Connection to database has failed!"<<endl;
	}// else
	logFile << "==========================================================" << endl;
}//ReadTranscationInfo




string Database::getState(string merchantDeatils) {
	string state = merchantDeatils.substr(merchantDeatils.length() - 2, 2);
	if (state == "US" || state == "us") {
		state = merchantDeatils.substr(merchantDeatils.length() - 4, 2);
	}
	return state;
}//getState

string Database::cleanMarchantDetails(string str) {

	string my_str = ""; 
	for (int i = 0; i < str.length(); i++) {
		if (str[i] != ' ') {
			my_str += str[i];
		}
		else if (str.back()!=' ') {
			my_str += str[i];
		}
	}


	my_str.erase(std::remove(my_str.begin(), my_str.end(), '\t'), my_str.end());
	return my_str; 
}//cleanMarchantDetails

void Database::cleanUpOlddata() {
	string query[4];
	 query[0]  = "DROP TABLE user_transcation; ";
	 query[1] = "DROP TABLE user_account;";
	 query[2] =  "CREATE TABLE user_account (last_name VARCHAR(30), first_name VARCHAR(30), street_address VARCHAR(100),unt VARCHAR(10),city VARCHAR(30),state CHAR(2),zip INT,dob Date,ssn VARCHAR(12),email_address VARCHAR(50),mobile_number VARCHAR(11),account_number INT  NOT NULL,PRIMARY KEY(account_number)); ";
	 query[3] = "CREATE TABLE user_transcation (account_number INT NOT NULL,transaction_datetime DATETIME,transaction_amount  DECIMAL(10, 2),post_date DATE,merchant_number VARCHAR(30),merchant_description VARCHAR(200),transaction_state VARCHAR(2),merchant_category_code INT,transaction_number INT,FOREIGN KEY(account_number) REFERENCES user_account(account_number)); ";
	
	MYSQL* conn;
	int qstate;

	conn = mysql_init(0);

	conn = mysql_real_connect(conn, "localhost", "root", "password", "save", 3306, NULL, 0);

	if (conn) {
		for (int i = 0; i < 4; i++) {
			qstate = mysql_query(conn, query[i].c_str());
			if (!qstate)
			{
				logFile << "Query Sucess : " << query[i] << endl;

			}
			else {
				logFile << "Query failed: "<<query[i] <<" " << mysql_error(conn) << endl;
				cout << "Query failed: " << mysql_error(conn) << endl;
			}
		}// for
		
	}// if 
	else {
		cout << "Connection to database has failed!"<< endl;
	}
	logFile << "==========================================================" << endl;

}

void Database:: murchangAvgPrice(unordered_map<string, double>& avg_price) {

	MYSQL* conn;
	int qstate;
	MYSQL_ROW row;
	MYSQL_RES* res;
	conn = mysql_init(0);

	conn = mysql_real_connect(conn, "localhost", "root", "password", "save", 3306, NULL, 0);

	if (conn) {
		string query = "SELECT merchant_number, AVG(transaction_amount) FROM user_transcation GROUP BY merchant_number;  ";
		qstate = mysql_query(conn, query.c_str());
		if (!qstate)
		{
			res = mysql_store_result(conn);
			logFile << "Query Sucess : " << query << endl;
			while (row = mysql_fetch_row(res))
			{
				avg_price.insert({ row[0], stof(row[1]) }); 
			}// while 
		}// if 
		else
		{
			logFile << "Query failed: " << mysql_error(conn) << endl;
		}// else 
	}// if
	else {
		cout << "Connection to database has failed!" << endl;
	}// else
	logFile << "==========================================================" << endl;





}
