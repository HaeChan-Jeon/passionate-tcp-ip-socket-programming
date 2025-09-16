#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <tchar.h>

int main() {
    LPCWSTR strAddr = L"203.211.218.102:9190";
    WCHAR strAddrBuf[50];
    SOCKADDR_IN servAddr;
    int size;

    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    size = sizeof(servAddr);
    WSAStringToAddressW(
        (LPWSTR)strAddr, AF_INET, NULL, (SOCKADDR*)&servAddr, &size);

    size = sizeof(strAddrBuf);
    WSAAddressToStringW(
        (SOCKADDR*)&servAddr, sizeof(servAddr), NULL, strAddrBuf, (LPDWORD)&size);

    wprintf(L"Second conv result: %s\n", strAddrBuf);
    WSACleanup();
    return 0;
}