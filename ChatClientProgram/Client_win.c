
#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <string.h>
#include <winsock2.h>

#define BUFFSIZE 400
#define NAMESIZE 20

char message[BUFFSIZE];


int main(int argc, char* argv[])
{
	SOCKET sock;
	WSADATA wsaData;

	struct sockaddr_in serv_addr;
	//pthread_t snd_thread, rcv_thread;
	void* thread_result;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		printf("WSAStartUp() error!");

	sock = socket(PF_INET, SOCK_STREAM, 0);

	if (sock == SOCKET_ERROR)
	{
		printf("socket() error \n");
		printf("%d", WSAGetLastError());
	}

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	if (argc == 1)
		serv_addr.sin_port = htons(7989);
	else
		serv_addr.sin_port = htons(atoi(argv[1]));

	if (connect(sock, (SOCKADDR*)&serv_addr, sizeof(serv_addr)) == SOCKET_ERROR)
	{
		printf("connect() error \n");
		printf("%d", WSAGetLastError());
		return 0;
	}

	unsigned char msg[100] = { 0x01, 2, 3, 4, 5, 6, 1, 2, 3, 4, 2, 1, 2, 3, 0xc };
	while (1)
	{
		printf("send : ");

		for (int i = 0; i < 15; ++i)
		{
			printf("%02X", msg[i]);
		}
		printf("\n");
		send(sock, msg, 15, 0);
		Sleep(1);
	}

	closesocket(sock);

	WSACleanup();

	return 0;
}