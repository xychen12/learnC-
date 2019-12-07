#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "WinSock2.h"
#pragma comment(lib,"ws2_32.lib")

int main(void){

	//WORD a = MAKEWORD(2, 2);
	WSADATA wsaData;
	WORD wsVersion = (2 & 0xFF) | ((2 & 0xFF) << 8);
	//printf("%d,%d\n", *(char*)&wsVersion, *((char*)&wsVersion + 1));
	
	int resultMode = WSAStartup(wsVersion, &wsaData);
	if (resultMode != 0){
		switch(resultMode){
		case WSASYSNOTREADY:
			printf("���������״̬");
			break;
		case WSAVERNOTSUPPORTED:
			printf("����ϵ������Ա�����鵱ǰ���������汾");
			break;
		case WSAEINPROGRESS:
			printf("���������");
			break;
		case WSAEPROCLIM:
			printf("��رղ���Ҫ������Ա�֤��Դ����");
			break;	
		}
		return 0;
	}
	//����汾
	if (HIBYTE(wsaData.wVersion) != 2 || LOBYTE(wsaData.wVersion) != 2){
		printf("�汾�쳣");
		WSACleanup();
		return 0;
	}

	//������socket
	SOCKET socketServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (SOCKET_ERROR == socketServer){
		int a = WSAGetLastError();

		closesocket(socketServer);
		WSACleanup();
		return 0;
	}

	struct sockaddr_in serverMsg;
	serverMsg.sin_family = AF_INET;
	serverMsg.sin_port = htons(5005);
	serverMsg.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	if (SOCKET_ERROR == connect(socketServer, (struct sockaddr*)&serverMsg, sizeof(serverMsg))){
		int ret = WSAGetLastError();

		closesocket(socketServer);
		WSACleanup();
		return 0;
	}

	char buf[1500] = { 0 };
	int res = recv(socketServer, buf, 1499, 0);
	if (res == 0){
		printf("�����ж�\n");
	}
	else if (SOCKET_ERROR == res){
		int resultMode = WSAGetLastError();
	}
	else{
		printf("%s\n", buf);
	}

	int isGo = 1;
	do{	
		char buf1[1500] = { 0 };
		scanf("%s", buf1);
		int a = strcmp(buf1, "stop");
		if (a == 0){
			isGo = 0;
			break;
		}
		if (SOCKET_ERROR == send(socketServer, buf1, strlen(buf1), 0)){
			int resultMode = WSAGetLastError();

			closesocket(socketServer);
			WSACleanup();
			return 0;
		}

		char buf2[1500] = { 0 };
		int res = recv(socketServer, buf2, 1499, 0);
		if (res == 0){
			printf("�����ж�\n");
		}
		else if (SOCKET_ERROR == res){
			int resultMode = WSAGetLastError();
		}
		else{
			printf("%s\n", buf2);
		}
	} while (isGo);
	
	closesocket(socketServer);
	WSACleanup();

	system("pause");
	return 0;
}