
#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <string.h>
#include <winsock2.h>


#define CLNT_MAX 10

int g_clnt_socks[CLNT_MAX];
int g_clnt_count = 0;


int main(int argc, char* argv[])
{
	WSADATA wsaData;
	SOCKET hServSock, hClntSock;
	SOCKADDR_IN servaddr_in, clntaddr_in;
	int szClntAddr;
	char message[] = "Hello World";

	//if (argc != 2)
	//{
	//	printf("Usage : %s <port>\n", argv[0]);
	//	exit(1);
	//}

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		printf("WSAStartUp() error!");

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
	// argv[1]�� ��Ʈ ��ȣ
	
	if(argc == 2)
		servaddr_in.sin_port = htons(atoi(argv[1]));

	else
		servaddr_in.sin_port = htons(7989);

	// bind �Լ��� ���Ͽ� �ּ� �Ҵ�
	if (bind(hServSock, (struct sockaddr*)&servaddr_in, sizeof(servaddr_in)) == -1)
		printf("bind Error occured! \n");


	// ������ ���� ��û�� ������ ���°� �ǰ� �Ѵ�
	if (listen(hServSock, 5) == SOCKET_ERROR)
		printf("listen Error occured! \n");

	char buff[400];
	int recv_len = 0;

	while (1)
	{
		szClntAddr = sizeof(clntaddr_in);
		// Ŭ���̾�Ʈ�� ���� ��û�� �����ϰ� ������ ������ ���Ϲ��� �������� Ŭ���̾�Ʈ�� �����Ѵ�
		// accept ȣ���ϰ��� 2��° ���ڿ� Ŭ���̾�Ʈ�� ������ �������
		hClntSock = accept(hServSock, (struct sockaddr*)&clntaddr_in, &szClntAddr);

		//g_clnt_socks[g_clnt_count++] = hClntSock;

		recv_len = recv(hClntSock, buff, sizeof(buff), 0);

		while (1)
		{
			if (recv_len == -1)
				printf("recv Error occured! \n");

			printf("recv : ");

			for (int i = 0; i < recv_len; ++i)
			{
				printf("%02X", (unsigned char)buff[i]);
			}
			printf("\n");
			//Sleep(1);
		}
	}

	closesocket(hServSock);

	WSACleanup();

	return 0;
}