//#define _CRT_SECURE_NO_WARNINGS
//#include <stdlib.h>
//#include <stdio.h>
//#include <string.h>
//#include "WinSock2.h"
//#pragma comment(lib,"ws2_32.lib")
//
//int main(){
//
//	DWORD wVersion = MAKEWORD(2, 2);
//	WSADATA wsaData;
//	int resultMode = WSAStartup(wVersion, &wsaData);
//	if (resultMode != 0){
//		switch (resultMode)
//		{
//		case WSASYSNOTREADY:
//			printf("���������״̬");
//			break;
//		case WSAVERNOTSUPPORTED:
//			printf("����ϵ������Ա�����鵱ǰ���������汾");
//			break;
//		case WSAEINPROGRESS:
//			printf("���������");
//			break;
//		case WSAEPROCLIM:
//			printf("��رղ���Ҫ������Ա�֤��Դ����");
//			break;	
//		default:
//			break;
//		}
//	}
//
//	if (2 != HIBYTE(wsaData.wVersion) || 2 != LOBYTE(wsaData.wVersion)){
//		WSACleanup();
//		return 0;
//	}
//
//	SOCKET socketServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
//	if (SOCKET_ERROR == socketServer){
//		int a = WSAGetLastError();
//	
//		closesocket(socketServer);
//		WSACleanup();
//		return 0;
//	}
//
//	struct sockaddr_in serverMsg;
//	serverMsg.sin_family = AF_INET;
//	serverMsg.sin_port = htons(5005);
//	serverMsg.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
//	if (SOCKET_ERROR == connect(socketServer, (struct sockaddr*)&serverMsg, sizeof(serverMsg))){
//		int ret = WSAGetLastError();
//	
//		closesocket(socketServer);
//		WSACleanup();
//		return 0;
//	}
//	
//	char buf[1500] = { 0 };
//	int res = recv(socketServer, buf, 1499, 0);
//	if (res == 0){
//		printf("�����ж�\n");
//	}
//	else if (SOCKET_ERROR == res){
//		int resultMode = WSAGetLastError();
//	}
//	else{
//		printf("%s\n", buf);
//	}
//	
//	int isGo = 1;
//	do{	
//		scanf("%s", buf);
//			
//		if (buf == "stop"){
//			isGo = 0;
//		}
//		if (SOCKET_ERROR == send(socketServer, buf, strlen(buf), 0)){
//			int resultMode = WSAGetLastError();
//	
//			closesocket(socketServer);
//			WSACleanup();
//			return 0;
//		}
//	
//			
//		int res = recv(socketServer, buf, 1499, 0);
//		if (res == 0){
//			printf("�����ж�\n");
//		}
//		else if (SOCKET_ERROR == res){
//			int resultMode = WSAGetLastError();
//		}
//		else{
//			printf("%s\n", buf);
//		}
//	} while (isGo);
//
//	system("pause");
//	return 0;
//}