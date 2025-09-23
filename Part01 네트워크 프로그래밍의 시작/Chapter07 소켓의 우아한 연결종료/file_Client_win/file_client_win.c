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
	FILE* fp;

	char buf[BUF_SIZE];
	int readCnt;
	struct sockaddr_in servAdr;

	if (argc != 3) {
		printf("Usage : %s <IP> <port>\n", argv[0]);
		exit(1);
	}
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ErrorHandling("WSAStartup() error!");

	if (fopen_s(&fp, "receive.dat", "wb") != 0) {
		ErrorHandling("File open error");
	}
	hSocket = socket(PF_INET, SOCK_STREAM, 0);

	memset(&servAdr, 0, sizeof(servAdr));
	servAdr.sin_family = AF_INET;
	if (InetPtonA(AF_INET, argv[1], &servAdr.sin_addr) <= 0) {
		ErrorHandling("Invalid IP address");
	}
	servAdr.sin_port = htons(atoi(argv[2]));

	connect(hSocket, (struct sockaddr*)&servAdr, sizeof(servAdr));

	while ((readCnt = recv(hSocket, buf, BUF_SIZE, 0)) != 0) {
		fwrite(buf, 1, readCnt, fp);
	}

	puts("Received file data");
	send(hSocket, "Thank you", 10, 0);
	fclose(fp);
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
