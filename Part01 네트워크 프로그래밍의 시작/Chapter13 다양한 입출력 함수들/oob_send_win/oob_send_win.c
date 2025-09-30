#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winSock2.h>
#include <WS2tcpip.h>

#define BUF_SIZE 30
void ErrorHandling(char* message);

int main(int argc, char* argv[])
{
	WSADATA wsaData;
	SOCKET hSocket;
	struct sockaddr_in sendAdr;
	if (argc != 3) {
		printf("Usage : %s <IP> <port>\n", argv[0]);
		exit(1);
	}

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ErrorHandling("WSAStartup() error!");

	hSocket = socket(PF_INET, SOCK_STREAM, 0);
	memset(&sendAdr, 0, sizeof(sendAdr));
	sendAdr.sin_family = AF_INET;
	if (InetPtonA(AF_INET, argv[1], &sendAdr.sin_addr) <= 0) {
		ErrorHandling("Invalid IP address");
	}
	sendAdr.sin_port = htons(atoi(argv[2]));

	if (connect(hSocket, (struct sockaddr*)&sendAdr, sizeof(sendAdr)) == SOCKET_ERROR)
		ErrorHandling("connect() error!");

	send(hSocket, "123", 3, 0);
	send(hSocket, "4", 1, MSG_OOB);
	send(hSocket, "567", 3, 0);
	send(hSocket, "890", 3, MSG_OOB);

	closesocket(hSocket);
	WSACleanup();
	return 0;
}

void ErrorHandling(char* buf)
{
	fputs(buf, stderr);
	fputc('\n', stderr);
	exit(1);
}