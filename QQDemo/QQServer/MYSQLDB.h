#pragma once
#include<mysql.h>
#include <string>
#include <vector>
#include <singleton.h>

class MYSQLDB
{
public:
	MYSQLDB();
	~MYSQLDB();

	bool createDatabase(std::string& dbname);
	bool createdbTable(const std::string& query);
	bool SelectDB();
	bool InsertData(std::string table_name, const std::string& data);
	bool InitDB();

	bool signInQuery(const std::string& username, const std::string& password, std::string& result);
private:
	MYSQL      m_mysql;
	MYSQL_RES* res; //这个结构代表返回行的一个查询结果集
	char query[150];
	MYSQL_ROW column; //一个行数据的类型安全(type-safe)的表示，表示数据行的列
	char field[32][32];  //存字段名二维数组
	MYSQL_FIELD* fd;  //字段列数组

	void finishQuery() {
		MYSQL_RES* pRes;
		do {
			pRes = mysql_use_result(&m_mysql);
			mysql_free_result(pRes);
		} while (!mysql_next_result(&m_mysql));
	}
};


#define MYSQLSERVER singleton<MYSQLDB>::instance()