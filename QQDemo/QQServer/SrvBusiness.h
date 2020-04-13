#pragma once

#include <string>
#include <map>
#include <list>

typedef long long INT64;
class SrvBusiness
{
public:
	SrvBusiness() {};
	~SrvBusiness() {};

public:
	std::string UserLogin(std::string json_userdata, std::string ipaddr, std::string &account);
	INT64 GetCurTimeStmp();
	void SetLoginIndex(int idx);
	bool CheckUserPwd(std::string acc, std::string pwd);
	std::string OnClientMsgHandle(const std::string & json_userdata, std::string ipaddr);
private:
	int m_login_index = 0;
	std::list<std::string> m_curLoginUser;
};


#define SRVBUSINESS singleton<MYSQLDB>::instance()