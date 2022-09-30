
#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <string.h>
#include <winsock2.h>
#include <process.h>

#define CLNT_MAX 10
#define BUFFSIZE 200

int g_clnt_socks[CLNT_MAX];
int g_clnt_count = 0;

CRITICAL_SECTION cs;

void send_all_clnt(char* msg, int my_sock)
{
	EnterCriticalSection(&cs);

	for (int i = 0; i < g_clnt_count; ++i)
	{
		if (g_clnt_socks[i] != my_sock)
		{
			printf("send msg : %s", msg);
			send(g_clnt_socks[i], msg, strlen(msg) + 1, 0);
		}
	}

	LeaveCriticalSection(&cs);
}

unsigned WINAPI clnt_connection(void* arg)
{
	int clnt_sock = *(int*)(&arg);
	int str_len = 0;

	char msg[BUFFSIZE];

	while (1)
	{
		str_len = recv(clnt_sock, msg, sizeof(msg) - 1, 0);
		if (str_len == -1)
		{
			printf("%d\n", WSAGetLastError());
			printf("clnt[%d] close \n", clnt_sock);
			break;
		}

		send_all_clnt(msg, clnt_sock);
		printf("%s\n", msg);
	}

	EnterCriticalSection(&cs);

	for (int i = 0; i < g_clnt_count; ++i)
	{
		if (clnt_sock == g_clnt_socks[i])
		{
			for (; i < g_clnt_count - 1; ++i)
				g_clnt_socks[i] = g_clnt_socks[i + 1];
			break;
		}
	}

	LeaveCriticalSection(&cs);

	closesocket(clnt_sock);

	return 0;
}

int main(int argc, char* argv[])
{
	WSADATA wsaData;
	SOCKET hServSock, hClntSock;
	SOCKADDR_IN servaddr_in, clntaddr_in;
	int szClntAddr;


	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		printf("WSAStartUp() error!");

	InitializeCriticalSection(&cs);


	// 1��° ���ڴ� IPv4 �������� ü�踦 �ǹ�
	// 2��° ���� SOCK_STREAM�� TCP ���� Ÿ���� �ǹ�
	// 3��° ���ڴ� 0�� �־��ָ� 1,2��° ���ڸ� ���� �˾Ƽ� ����
	hServSock = socket(PF_INET, SOCK_STREAM, 0);

	// IPv4 : 4����Ʈ �ּ�ü��
	servaddr_in.sin_family = AF_INET;
	// sin_addr�� 32��Ʈ IP�ּҸ� �ǹ�. INADDR_ANY�� ���� PC�� IP�� �ٸ� PC���� ���α׷��� �����ص� ��������
	// htonl�� host to network long�� ���ڷ� ȣ��Ʈ�� ����Ʈ ������ ��Ʈ��ũ ����Ʈ ������ ��ȯ���ִ� �Լ��̴�.
	// ��Ʈ��ũ ����Ʈ ������ �� ������� �����̰�, ���������� long�� 4����Ʈ�̴�
	servaddr_in.sin_addr.s_addr = htonl(INADDR_ANY);
	// sin_port�� 16��Ʈ ���� Port��ȣ. ��Ʈ��ũ ����Ʈ ������� �����ؾ� �Ѵٴ°� �߿�
	servaddr_in.sin_port = htons(7999);

	// bind �Լ��� ���Ͽ� �ּ� �Ҵ�
	if (bind(hServSock, (struct sockaddr*)&servaddr_in, sizeof(servaddr_in)) == -1)
		printf("bind Error occured! \n");


	// ������ ���� ��û�� ������ ���°� �ǰ� �Ѵ�
	if (listen(hServSock, 5) == SOCKET_ERROR)
		printf("listen Error occured! \n");


	int recv_len = 0;

	while (1)
	{
		szClntAddr = sizeof(clntaddr_in);
		// Ŭ���̾�Ʈ�� ���� ��û�� �����ϰ� ������ ������ ���Ϲ��� �������� Ŭ���̾�Ʈ�� �����Ѵ�
		// accept ȣ���ϰ��� 2��° ���ڿ� Ŭ���̾�Ʈ�� ������ �������
		hClntSock = accept(hServSock, (struct sockaddr*)&clntaddr_in, &szClntAddr);

		EnterCriticalSection(&cs);
		g_clnt_socks[g_clnt_count++] = hClntSock;
		LeaveCriticalSection(&cs);

		unsigned threadID;

		_beginthreadex(NULL, 0, clnt_connection, (void*)hClntSock, 0, &threadID);
	}

	DeleteCriticalSection(&cs);

	closesocket(hServSock);

	WSACleanup();

	return 0;
}