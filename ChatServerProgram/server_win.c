
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

	// 1번째 인자는 IPv4 프로토콜 체계를 의미
	// 2번째 인자 SOCK_STREAM은 TCP 소켓 타입을 의미
	// 3번째 인자는 0을 넣어주면 1,2번째 인자를 보고 알아서 들어간다
	hServSock = socket(PF_INET, SOCK_STREAM, 0);

	// IPv4 : 4바이트 주소체계
	servaddr_in.sin_family = AF_INET;
	// sin_addr은 32비트 IP주소를 의미. INADDR_ANY는 현재 PC의 IP라서 다른 PC에서 프로그램을 실행해도 문제없다
	// htonl은 host to network long의 약자로 호스트의 바이트 순서를 네트워크 바이트 순서로 변환해주는 함수이다.
	// 네트워크 바이트 순서는 빅 엔디안이 기준이고, 리눅스에선 long이 4바이트이다
	servaddr_in.sin_addr.s_addr = htonl(INADDR_ANY);
	// sin_port는 16비트 소켓 Port번호. 네트워크 바이트 순서대로 저장해야 한다는게 중요
	// argv[1]은 포트 번호
	
	if(argc == 2)
		servaddr_in.sin_port = htons(atoi(argv[1]));

	else
		servaddr_in.sin_port = htons(7989);

	// bind 함수로 소켓에 주소 할당
	if (bind(hServSock, (struct sockaddr*)&servaddr_in, sizeof(servaddr_in)) == -1)
		printf("bind Error occured! \n");


	// 소켓이 연결 요청이 가능한 상태가 되게 한다
	if (listen(hServSock, 5) == SOCKET_ERROR)
		printf("listen Error occured! \n");

	char buff[400];
	int recv_len = 0;

	while (1)
	{
		szClntAddr = sizeof(clntaddr_in);
		// 클라이언트의 연결 요청을 수락하고 서버는 실제로 리턴받은 소켓으로 클라이언트와 소통한다
		// accept 호출하고나면 2번째 인자에 클라이언트의 정보가 담겨진다
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