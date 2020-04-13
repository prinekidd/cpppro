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
	MYSQL_RES* res; //����ṹ�������е�һ����ѯ�����
	char query[150];
	MYSQL_ROW column; //һ�������ݵ����Ͱ�ȫ(type-safe)�ı�ʾ����ʾ�����е���
	char field[32][32];  //���ֶ�����ά����
	MYSQL_FIELD* fd;  //�ֶ�������

	void finishQuery() {
		MYSQL_RES* pRes;
		do {
			pRes = mysql_use_result(&m_mysql);
			mysql_free_result(pRes);
		} while (!mysql_next_result(&m_mysql));
	}
};


#define MYSQLSERVER singleton<MYSQLDB>::instance()