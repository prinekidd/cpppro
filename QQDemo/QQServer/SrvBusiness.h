#pragma once
#include <singleton.h>
#include <string>
#include <map>
#include <list>
#include "ServerModel.h"
#include <json/json.h>
class CServer;
typedef long long INT64;
class SrvBusiness
{
public:
	SrvBusiness() {};
	~SrvBusiness() {};
	CServer* m_pCServer;
public:
	Json::Value UserLogin(std::string json_userdata, std::string ipaddr, std::string &account);
	Json::Value  UserRegist(std::string json_userdata);
	INT64 GetCurTimeStmp();
	void SetLoginIndex(int idx);
	
	//处理客户端发送过来的消息
	std::string OnClientMsgHandle(const std::string & json_userdata, spSock_t sock);

	void  SendResponceToClient(CLIENTCOMMAND msg_type, const Json::Value& json_msg,spSock_t sock);
private:
	int m_login_index = 0;
	std::list<int> m_curLoginUser;
};


#define SRVBUSINESS singleton<SrvBusiness>::instance()