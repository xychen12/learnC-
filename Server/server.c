//#define _CRT_SECURE_NO_WARNINGS
//#include<stdio.h>
//#include<stdlib.h>
//#include<WinSock2.h>
//#include<string.h>
//#include<Windows.h>
//#pragma comment(lib, "Ws2_32.lib")
//
//int main(void){
//	int isGo = 1;
//
//	WORD wdVersion = MAKEWORD(2, 2);
//	WSADATA wdScokMsg;
//	int resultMode = WSAStartup(wdVersion, &wdScokMsg);
//	if (resultMode != 0){
//		switch (resultMode){
//		case WSASYSNOTREADY:{
//			printf("���������ԣ�����������쳣");
//			break;
//		}
//		case WSAVERNOTSUPPORTED:
//		{
//			printf("����ϵ������Ա�����°汾��");
//			break;
//		}
//		case WSAEINPROGRESS:{
//			printf("�������������");
//			break;
//		}
//		case WSAEPROCLIM:
//		{
//			printf("�볢�Թص�����Ҫ�������ṩ������Դ");
//			break;
//		}
//		case WSAEFAULT:{
//			printf("�����쳣");
//			break;
//		}
//		}
//	}
//
//	//У��汾
//	if (2 != HIBYTE(wdScokMsg.wVersion) || 2 != LOBYTE(wdScokMsg.wVersion)){
//		//����/�ر������
//		WSACleanup();
//		return 0;
//	}
//
//	SOCKET socketServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
//	if (socketServer == INVALID_SOCKET){
//		int errorMode = WSAGetLastError();
//
//
//		WSACleanup();
//		return 0;
//	}
//
//	struct sockaddr_in si;
//	si.sin_family = AF_INET;
//	si.sin_port = htons(5005);
//	si.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
//
//	if (SOCKET_ERROR == bind(socketServer, (const struct sockaddr*)&si, sizeof(si))){
//		int resultMode = WSAGetLastError();
//
//		closesocket(socketServer);
//		WSACleanup();
//		return 0;
//	}
//
//	if (SOCKET_ERROR == listen(socketServer, SOMAXCONN)){
//		int resultMode = WSAGetLastError();
//
//		closesocket(socketServer);
//		WSACleanup();
//		return 0;
//	}
//
//	struct sockaddr_in clientMsg;
//	int len = sizeof(clientMsg);
//	SOCKET socketClient = accept(socketServer, (struct sockaddr*)&clientMsg, &len);
//	if (socketClient == INVALID_SOCKET){
//		int a = WSAGetLastError();
//
//		closesocket(socketServer);
//		WSACleanup();
//		return 0;
//	}
//
//	printf("һ�ſͻ������ӳɹ�\n");
//
//	if (SOCKET_ERROR == send(socketClient, "xinyu,�������յ���", sizeof("xinyu,�������յ���"), 0)){
//		int resultMode = WSAGetLastError();
//
//		closesocket(socketServer);
//		WSACleanup();
//		return 0;
//	}
//
//	do{
//		char buf[1500] = { 0 };
//		int res = recv(socketClient, buf, 1499, 0);
//		if (res == 0){
//			printf("�����ж�\n");
//		}
//		else if (SOCKET_ERROR == res){
//			int resultMode = WSAGetLastError();
//		}
//		else{
//			printf("%s\n", buf);
//		}
//
//		//scanf("%s", buf);
//		//
//		//if (buf == "stop"){
//		//	isGo = 0;
//		//}
//		//if (SOCKET_ERROR == send(socketClient, buf, strlen(buf), 0)){
//		//	int a = WSAGetLastError();
//		//}
//		if (SOCKET_ERROR == send(socketClient, "abcd", sizeof("abcd"), 0)){
//			int a = WSAGetLastError();
//		}
//	} while (isGo);
//
//	closesocket(socketServer);
//
//	closesocket(socketClient);
//	WSACleanup();
//
//
//
//	system("pause");
//	return 0;
//}