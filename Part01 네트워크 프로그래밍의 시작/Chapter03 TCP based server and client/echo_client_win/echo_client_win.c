#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <Ws2tcpip.h>

#define BUF_SIZE 1024
void ErrorHandling(char* message);

int main(int argc, char* argv[])
{
	WSADATA wsaData;
	SOCKET hServSock;
	char message[BUF_SIZE];
	int strLen;
	SOCKADDR_IN servAdr;

	if (argc != 3) {
		printf("Usage : %s <ip> <port>\n", argv[0]);
		exit(1);
	}

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ErrorHandling("WSAStartup() error!");

	hServSock = socket(PF_INET, SOCK_STREAM, 0);
	if (hServSock == INVALID_SOCKET)
		ErrorHandling("socket() error");

	memset(&servAdr, 0, sizeof(servAdr));
	servAdr.sin_family = AF_INET;
	if (InetPtonA(AF_INET, argv[1], &servAdr.sin_addr) <= 0)
		ErrorHandling("Invalid IP address");
	servAdr.sin_port = htons(atoi(argv[2]));

	if (connect(hServSock, (SOCKADDR*)&servAdr, sizeof(servAdr)) == SOCKET_ERROR)
		ErrorHandling("connect() error");
	else
		puts("Connected...........");

	while (1)
	{
		fputs("Input message(Q to quit): ", stdout);
		fgets(message, BUF_SIZE, stdin);

		if (!strcmp(message, "q\n") || !strcmp(message, "Q\n"))
			break;

		send(hServSock, message, strlen(message), 0);
		strLen = recv(hServSock, message, BUF_SIZE - 1, 0);
		message[strLen] = 0;
		printf("Message from server: %s", message);
	}
	closesocket(hServSock);
	WSACleanup();
	return 0;
}

void ErrorHandling(char* message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}