
#include "ClientManager.h"
#include "Client/ClientWindow.h"
#include "IMGUI/IMGUIManager.h"
#include "IMGUI/IMGUIChatBox.h"

#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <string.h>
//#include <winsock2.h>
#include <process.h>

SOCKET CClientManager::m_Socket = 0;
char CClientManager::m_ID[100];

DEFINITION_SINGLE(CClientManager)


CClientManager::CClientManager()
{
}

CClientManager::~CClientManager()
{

}

bool CClientManager::Init(char* ID)
{
	WSADATA wsaData;
	struct sockaddr_in serv_addr;

	// 콘솔창 키보드 입력을 다시 콘솔창에 출력하지 않게 하는 옵션
	//echooff(stdin);

	strcpy_s(m_ID, sizeof(m_ID), ID);
	printf("ID : %s\n", ID);

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		printf("WSAStartUp() error!");

	m_Socket = socket(PF_INET, SOCK_STREAM, 0);

	if (m_Socket == SOCKET_ERROR)
	{
		printf("connect() error \n");
		return false;
	}

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	serv_addr.sin_port = htons(7999);


	if (connect(m_Socket, (SOCKADDR*)&serv_addr, sizeof(serv_addr)) == SOCKET_ERROR)
	{
		printf("connect() error \n");
		return false;
	}
	unsigned threadID = 0;
	_beginthreadex(NULL, 0, CClientManager::rcv, (void*)m_Socket, 0, &threadID);


	// Client의 채팅 입력을 받아서 서버로 뿌리는 쓰레드 생성
	//CreateInputThread();

	// Client용 IMGUI Window 생성
	CreateClientChatWindow();

	return true;
}

int CClientManager::Run()
{
	return 0;
}

void CClientManager::CreateClientChatWindow()
{
	CIMGUIManager::GetInst()->AddWindow<CClientWindow>("ClientChatWindow");
}


unsigned int __stdcall CClientManager::rcv(void* arg)
{
	//printf("rcv thread created\n");
	int sock = *(int*)(&arg);
	char buff[500];
	int len;
	while (1)
	{
		len = recv(sock, buff, sizeof(buff), 0);

		if (len == -1)
		{
			printf("sock close\n");
			break;
		}
		//printf("%s", buff);
		CClientWindow* Window = (CClientWindow*)CIMGUIManager::GetInst()->FindIMGUIWindow("ClientChatWindow");

		if (Window)
		{
			CIMGUIChatBox* ChatBox = (CIMGUIChatBox*)Window->FindWidget("ChatBox");

			if (ChatBox)
			{
				ChatBox->AddItem(buff);
			}

		}


	}

	return 0;
}

//unsigned int __stdcall CClientManager::ClientChatThread(void* arg)
//{
//	char chat[200];
//	char msg[200];
//
//	while (1)
//	{
//		fgets(chat, sizeof(chat), stdin);
//
//		sprintf(msg, "[%s] : %s", m_ID, chat);
//
//		printf("%s", msg);
//		send(m_Socket, msg, (int)(strlen(msg) + 1), 0);
//		Sleep(DWORD(0.4f));
//	}
//
//	return 0;
//}
