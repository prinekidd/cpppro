#pragma once

enum QQCOMMOMOP
{
	UNKONWWRONG = -1,
	SUCCESS,
};


//�ͻ�������

enum CLIENTCOMMAND
{
	ClientRegistAccRq = 1,
	ClientRegistAccRs ,

	ClientLoginRq,
	ClientLoginRs ,

	ClientLogOutRq,
	ClientLogOutRs,

	ClientHeatBeatRq,
	ClientHeatBeatRs,
};

enum CLIENTSTATUS
{
	unkown = -1,
	offline,
	online,
};

enum SERVERCOMMAND
{
	
};