#pragma once

#include "GameInfo.h"

class CClientManager
{
public:
	bool Init(char* ID);
	int Run();
	void CreateClientChatWindow();
	void CreateInputThread();

private:
	// ������ ����� Ŭ���̾�Ʈ ����
	static SOCKET m_Socket;
	static char m_ID[100];

public:
	static SOCKET GetSocket()
	{
		return m_Socket;
	}

private:
	static unsigned int __stdcall rcv(void* arg);
	//static unsigned int __stdcall ClientChatThread(void* arg);


	DECLARE_SINGLE(CClientManager)
};

