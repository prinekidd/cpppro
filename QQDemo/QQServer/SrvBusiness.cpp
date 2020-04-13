#include "SrvBusiness.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <json/json.h>
#include "MYSQLDB.h"
#include <commdef.h>
using namespace boost::property_tree;

std::string SrvBusiness::UserLogin(std::string json_userdata, std::string ipaddr, std::string &account)
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
		std::string acc = root["account"].asString();
		account = acc;
		std::string ret_str;
		if (MYSQLSERVER->signInQuery(acc, pwd, ret_str))
		{
			if (std::find(m_curLoginUser.begin(), m_curLoginUser.end(), acc) == m_curLoginUser.end())
			{
				ret = 0;
				m_curLoginUser.push_back(acc);
			}
			else
			{
				ret = 1;
				ret_str = acc + " 已经登录";
			}
		}

		boost::format fmt("%d,'%s', '%s','%s', %I64d");
		fmt% m_login_index++% acc% pwd %ipaddr% GetCurTimeStmp();

		MYSQLSERVER->InsertData("qquserdata",fmt.str());

		Json::Value root_ret;
		root_ret["code"] = ret;
		root_ret["msg"] = ret_str;
		std::ostringstream os;
		Json::StreamWriterBuilder sb;
		Json::StreamWriter * writerb(sb.newStreamWriter());
		writerb->write(root_ret, &os);
		return root_ret.toStyledString();
	}
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

bool SrvBusiness::CheckUserPwd(std::string acc, std::string pwd)
{
	//return MYSQLSERVER->signInQuery(acc, pwd,);
}

std::string SrvBusiness::OnClientMsgHandle(const std::string& json_userdata, std::string ipaddr)
{
	Json::CharReaderBuilder crb;
	Json::CharReader* reader(crb.newCharReader());
	Json::Value root;
	JSONCPP_STRING errs;
	if (reader->parse(json_userdata.c_str(), json_userdata.c_str() + std::strlen(json_userdata.c_str()), &root, &errs))
	{
		int msg_type = root["msg_type"].asInt();
		std::string data = root["data"].toStyledString();
		std::string ret_jsonstr;
		switch (msg_type)
		{
		/*用户登录*/
		case 1:
		{
			std::string acc;
			ret_jsonstr=UserLogin(data, ipaddr, acc);
		}
			break;
		default:
			break;
		}
		return ret_jsonstr;
	}
	return "";
}
