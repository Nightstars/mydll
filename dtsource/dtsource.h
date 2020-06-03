#pragma once
//base query
extern "C" _declspec(dllexport) int q_base(const char* db_url, const char* db_name, const char* db_sql, char* result[256]);
//query num of recoders
extern "C" _declspec(dllexport) int q_rc(const char* db_url, const char* db_name, const char* db_sql, char** result);
//query recoder size
extern "C" _declspec(dllexport) int q_rcnum(const char* db_url,const char* db_name, const char* db_sql, char** result);
//query all databases
extern "C" _declspec(dllexport) int q_db(const char* db_url,char** result);
//query all datatables in a sure database
extern "C" _declspec(dllexport) int q_dt(const char* db_url, const char* db_name, char** result);
//query clum type
extern "C" _declspec(dllexport) int q_type(const char* db_url, const char* db_name, const char* dt_name, char** result);
