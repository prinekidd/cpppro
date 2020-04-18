#include "SrvBusiness.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <json/json.h>
#include "MYSQLDB.h"
#include <commdef.h>
#include "ServerModel.h"

using namespace boost::property_tree;

Json::Value SrvBusiness::UserLogin(std::string json_userdata, std::string ipaddr, std::string &account)
{
	Json::CharReaderBuilder b;
	Json::CharReader* reader(b.newCharReader());
	Json::Value root;
	JSONCPP_STRING errs;
	if (reader->parse(json_userdata.c_str(), json_userdata.c_str() + std::strlen(json_userdata.c_str()),&root, &errs))
	{
		int ret = -1;
		std::string msg;
		std::string pwd = root["password"].asString();
		int acc = root["account"].asInt();
		std::string ret_str;
		if (std::find(m_curLoginUser.begin(), m_curLoginUser.end(), acc) == m_curLoginUser.end())
		{
			if (MYSQLSERVER->signInQuery(acc, pwd, ret_str))
			{
				if (std::find(m_curLoginUser.begin(), m_curLoginUser.end(), acc) == m_curLoginUser.end())
				{
					ret = 0;
					m_curLoginUser.push_back(acc);
					msg = "success";
					boost::format fmt("%d,'%s',NOW()");
					fmt% acc% ipaddr;
					MYSQLSERVER->InsertRecord(fmt.str());
				}
				else
				{
					ret = 1;
					msg = "failed";
				}
			}
			else
			{
				ret = 1;
				ret_str = "failed";
			}
		}
		else
		{
			ret = 1;
			ret_str = "you account has been logined!";
		}

		Json::Value root_ret;
		root_ret["code"] = ret;
		root_ret["msg"] = ret_str;
		cout << "用户登录" << acc << "结果：" << ret << endl;
		return root_ret;
	}
}

Json::Value SrvBusiness::UserRegist(std::string json_userdata)
{
	Json::CharReaderBuilder b;
	Json::CharReader* reader(b.newCharReader());
	Json::Value root;
	JSONCPP_STRING errs;
	if (reader->parse(json_userdata.c_str(), json_userdata.c_str() + std::strlen(json_userdata.c_str()), &root, &errs))
	{
		int ret = -1;
		std::string msg="regist failed!";
		std::string pwd = root["password"].asString();
		std::string acc = root["account"].asString();
		int account = MYSQLSERVER->GenarateAcc();
		boost::format fmt("%d,'%s','%s'");
		fmt% account% pwd% acc;

		if (MYSQLSERVER->InsertData("user_list", fmt.str()))
		{
			ret = QQCOMMOMOP::SUCCESS;
			msg = "success";
		}
		
		Json::Value root_ret;
		root_ret["code"] = ret;
		root_ret["msg"] = msg;
		cout << "用户注册" << account << "结果：" << ret << endl;
		return root_ret;
	}
	return std::string();
}

INT64 SrvBusiness::GetCurTimeStmp()
{
	//那我就用使用boost的方法来取嘛
	boost::posix_time::ptime epoch(boost::gregorian::date(1970, boost::gregorian::Jan, 1));
	boost::posix_time::time_duration time_from_epoch =boost::posix_time::second_clock::universal_time() - epoch;
	return time_from_epoch.total_seconds();
}

void SrvBusiness::SetLoginIndex(int idx)
{
	m_login_index = idx;
}


std::string SrvBusiness::OnClientMsgHandle(const std::string& json_userdata, spSock_t sock)
{
	Json::CharReaderBuilder crb;
	Json::CharReader* reader(crb.newCharReader());
	Json::Value root;
	JSONCPP_STRING errs;
	if (reader->parse(json_userdata.c_str(), json_userdata.c_str() + std::strlen(json_userdata.c_str()), &root, &errs))
	{
		int msg_type = root["msg_type"].asInt();
		std::string data = root["data"].toStyledString();
		Json::Value ret_jsonstr;
		switch (msg_type)
		{
		/*用户注册*/
		case CLIENTCOMMAND::ClientRegistAccRq:
		{
			ret_jsonstr =UserRegist(data);
			SendResponceToClient(CLIENTCOMMAND::ClientRegistAccRs, ret_jsonstr, sock);
		}
			break;
		/*用户登录*/
		case CLIENTCOMMAND::ClientLoginRq:
		{
			std::string acc;
			ret_jsonstr=UserLogin(data, sock->remote_endpoint().address().to_string(), acc);
			SendResponceToClient(CLIENTCOMMAND::ClientLoginRs, ret_jsonstr, sock);
		}
			break;
		/*用户登出*/
		case CLIENTCOMMAND::ClientLogOutRq:
		{
			Json::CharReaderBuilder b;
			Json::CharReader* reader(b.newCharReader());
			Json::Value root_data;
			JSONCPP_STRING errs;
			if (reader->parse(data.c_str(), data.c_str() + std::strlen(data.c_str()), &root_data, &errs))
			{
				int ret = -1;
				std::string msg = "logout failed!";
				int use_id = root_data["account"].asInt();
				for (list<int>::iterator iter = m_curLoginUser.begin(); iter != this->m_curLoginUser.end();)
				{
					if (*iter == use_id)
					{
						ret = 0;
						msg = "logout success";
						m_curLoginUser.erase(iter++);
					}
					else
						++iter;
				}
				Json::Value root_ret;
				root_ret["code"] = ret;
				root_ret["msg"] = msg;
				cout << "用户登出" << use_id << "结果：" << ret << endl;
				SendResponceToClient(CLIENTCOMMAND::ClientLogOutRs, root_ret, sock);
			}
		}
			break;
		default:
			break;
		}
		return ret_jsonstr.toStyledString();
	}
	return "";
}

void SrvBusiness::SendResponceToClient(CLIENTCOMMAND msg_type, const Json::Value& json_msg, spSock_t sock)
{
	Json::Value root_ret;
	root_ret["msg_type"] = msg_type;
	root_ret["data"] = json_msg;
	sock->async_write_some(boost::asio::buffer(root_ret.toStyledString()), boost::bind(&CServer::send_handler, m_pCServer, _1, sock)); //发送数据
}
