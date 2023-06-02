#include"data_geter.h"
#include"sqlite/sqlite3.h"
#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include"TcpListener.h"
using namespace std;







std::string get_value_set(std::string name) {

	std::string sss = "SELECT * FROM ";
	sss.append(name);


	char* err;


	CString result;

	sqlite3* db;
	sqlite3_stmt* stmt;
	sqlite3_open("mydb.db", &db);
	int rs = sqlite3_exec(db, "", NULL, NULL, &err);


	

	const unsigned char* max;
	const unsigned char* min;
	const unsigned char* reg;
	const unsigned char* value;
	const unsigned char* type;


	int error = sqlite3_prepare_v2(db, sss.c_str(), -1, &stmt, 0);

	if (error != SQLITE_OK) {
	}

	else {
		while (sqlite3_step(stmt) != SQLITE_DONE) {
			reg = sqlite3_column_text(stmt, 0);
			value = sqlite3_column_text(stmt, 1);
			min = sqlite3_column_text(stmt, 2);
			max = sqlite3_column_text(stmt, 3);
			type=sqlite3_column_text(stmt, 4);

			int s = strlen((char*) reg);
			for (int i = 0; i < s; i++) {
				result.AppendChar(reg[i]);
			}

			result.AppendChar(',');
			
			 s = strlen((char*)value);
			for (int i = 0; i < s; i++) {
				result.AppendChar(value[i]);
			}

			result.AppendChar(',');


			 s = strlen((char*)min);
			for (int i = 0; i < s; i++) {
				result.AppendChar(min[i]);
			}

			result.AppendChar(',');
			 s = strlen((char*)max);
			for (int i = 0; i < s; i++) {
				result.AppendChar(max[i]);
			}

			result.AppendChar(',');


			 s = strlen((char*)type);
			for (int i = 0; i < s; i++) {
				result.AppendChar(type[i]);
			}
			result.AppendChar('\n');

		}
	}

	string s;
	s = result;
	sqlite3_close(db);
	return s;

}


std::string get_all_sets( int id){

	std::string sss = "SELECT name FROM set_";
	sss.append(std::to_string(id));

	char* err;
	CString result;
	sqlite3* db;
	sqlite3_stmt* stmt;


	sqlite3_open("mydb.db", &db);
	int rs = sqlite3_exec(db, "", NULL, NULL, &err);




	const unsigned char* max;
	int error = sqlite3_prepare_v2(db, sss.c_str(), -1, &stmt, 0);

	if (error != SQLITE_OK) {
	}

	else {
		while (sqlite3_step(stmt) != SQLITE_DONE) {
			max = sqlite3_column_text(stmt, 0);
			int s = strlen((char*)max);
			for (int i = 0; i < s; i++) {
				result.AppendChar(max[i]);
				

			}
			result.AppendChar(',');
		}
	}

	string s;
	s = result;
	sqlite3_close(db);
	return s;
	

}




std::string get_value_html(std::string name, int id) {


	std::string sss = "SELECT html FROM html_";
	sss.append(std::to_string(id));
	sss.append(" where name LIKE \"");
	sss.append(name);
	sss.append("\"");

	char* err;

	CString result;

	sqlite3* db;
	sqlite3_stmt* stmt;
	sqlite3_open("mydb.db", &db);
	int rs = sqlite3_exec(db, "", NULL, NULL, &err);

	const unsigned char* max;
	int error = sqlite3_prepare_v2(db,sss.c_str(), -1, &stmt, 0);

	if (error != SQLITE_OK) {
	}

	else {
		while (sqlite3_step(stmt) != SQLITE_DONE) {
			max = sqlite3_column_text(stmt, 0);
			int s = strlen((char*)max);
			for (int i = 0; i < s; i++) {
				result.AppendChar(max[i]);
			}
		}
	}

	string s;
	s= result;
	sqlite3_close(db);
	return s;

}



std::string get_value_photo(std::string name  , int  id) {
	sqlite3* db;
	char* err_msg = 0;
	int rc = sqlite3_open("mydb.db", &db);
	if (rc != SQLITE_OK) {

		fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);

		return "error";
	}

	std::string sss = "SELECT photo FROM image_";
	sss.append(std::to_string(id));
	sss.append(" where name LIKE \"");
	sss.append(name);
	sss.append("\"");
	
	sqlite3_stmt* pStmt;
	rc = sqlite3_prepare_v2(db, sss.c_str(), -1, &pStmt, 0);

	if (rc != SQLITE_OK) {

		fprintf(stderr, "Failed to prepare statement\n");
		fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));

		sqlite3_close(db);

		return "error";
	}

	rc = sqlite3_step(pStmt);
	int bytes = 0;

	if (rc == SQLITE_ROW) {

		bytes = sqlite3_column_bytes(pStmt, 0);
	}


	std::string s(static_cast<const char*>(sqlite3_column_blob(pStmt, 0)), bytes);
	rc = sqlite3_finalize(pStmt);
	sqlite3_close(db);
	return s;
		   
}

bool get_device_by_num(int num,CString& result) {
	char* err;
	sqlite3* db;
	sqlite3_stmt* stmt;
	sqlite3_open("mydb.db", &db);
	int rs = sqlite3_exec(db, "", NULL, NULL, &err);

	std::string number ;
	const unsigned char* max;

	number.append("select * from `translate_table` WHERE number_of_device= ");
	number.append(std::to_string(num));
	
	int error = sqlite3_prepare_v2(db, number.c_str(), -1, &stmt, 0);
	
	if (error != SQLITE_OK) {
	}
	else {
		int reg;
		int cc;

		while (sqlite3_step(stmt) != SQLITE_DONE) {
			reg = sqlite3_column_int(stmt, 0);
			max = sqlite3_column_text(stmt, 1);
			cc= sqlite3_column_int(stmt, 0);

			int s = strlen((char*)max);
			

			for (int i=0; i < s; i++) {
				result.AppendChar(max[i]);
			}	
		}		 
	}


	return 0;
}

bool get_id_by_num(int num, int& result) {
	char* err;
	sqlite3* db;
	sqlite3_stmt* stmt;
	sqlite3_open("mydb.db", &db);
	int rs = sqlite3_exec(db, "", NULL, NULL, &err);

	std::string number;
	const unsigned char* max;
	int id;

	number.append("select * from `translate_table` WHERE number_of_device= ");
	number.append(std::to_string(num));


	int error = sqlite3_prepare_v2(db, number.c_str(), -1, &stmt, 0);


	if (error != SQLITE_OK) {
	}

	else {
		int reg;
		while (sqlite3_step(stmt) != SQLITE_DONE) {
			reg = sqlite3_column_int(stmt, 0);
			max = sqlite3_column_text(stmt, 1);
			id = sqlite3_column_int(stmt, 2);
			result = int(id);
			
		}
	}
	return 0;
}


bool get_num_by_id(int num, int& result) {
	char* err;
	sqlite3* db;
	sqlite3_stmt* stmt;
	sqlite3_open("mydb.db", &db);
	int rs = sqlite3_exec(db, "", NULL, NULL, &err);

	std::string number;
	const unsigned char* max;
	int id;

	number.append("select * from `translate_table` WHERE id= ");
	number.append(std::to_string(num));


	int error = sqlite3_prepare_v2(db, number.c_str(), -1, &stmt, 0);


	if (error != SQLITE_OK) {
	}

	else {
		int reg;
		while (sqlite3_step(stmt) != SQLITE_DONE) {
			reg = sqlite3_column_int(stmt, 0);
			max = sqlite3_column_text(stmt, 1);
			id = sqlite3_column_int(stmt, 2);

			result = int(reg);

		}
	}
	return 0;
}


bool get_save_by_id(int num, int& result) {
	char* err;
	sqlite3* db;
	sqlite3_stmt* stmt;
	sqlite3_open("mydb.db", &db);
	int rs = sqlite3_exec(db, "", NULL, NULL, &err);



	std::string number;
	const unsigned char* max;
	int id;
	int save;

	number.append("select * from `translate_table` WHERE id= ");
	number.append(std::to_string(num));


	int error = sqlite3_prepare_v2(db, number.c_str(), -1, &stmt, 0);


	if (error != SQLITE_OK) {
	}

	else {
		int reg;
		while (sqlite3_step(stmt) != SQLITE_DONE) {
			reg = sqlite3_column_int(stmt, 0);
			max = sqlite3_column_text(stmt, 1);
			id = sqlite3_column_int(stmt, 2);
			save = sqlite3_column_int(stmt, 3);

			result = int(save);

		}
	}
	return 0;
}