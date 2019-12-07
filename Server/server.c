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
//			printf("请重启电脑，或检查网络库异常");
//			break;
//		}
//		case WSAVERNOTSUPPORTED:
//		{
//			printf("请联系开发人员，更新版本库");
//			break;
//		}
//		case WSAEINPROGRESS:{
//			printf("请重新启动软件");
//			break;
//		}
//		case WSAEPROCLIM:
//		{
//			printf("请尝试关掉不必要程序，以提供充足资源");
//			break;
//		}
//		case WSAEFAULT:{
//			printf("代码异常");
//			break;
//		}
//		}
//	}
//
//	//校验版本
//	if (2 != HIBYTE(wdScokMsg.wVersion) || 2 != LOBYTE(wdScokMsg.wVersion)){
//		//清理/关闭网络库
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
//	printf("一号客户端连接成功\n");
//
//	if (SOCKET_ERROR == send(socketClient, "xinyu,服务器收到了", sizeof("xinyu,服务器收到了"), 0)){
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
//			printf("连接中断\n");
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