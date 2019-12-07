//#define _CRT_SECURE_NO_WARNINGS
//
//#define FD_SETSIZE 128
//
//#include<stdlib.h>
//#include<stdio.h>
//#include<stdbool.h>
//#include<WinSock2.h>
//#pragma comment(lib, "Ws2_32.lib")
//
//struct fd_es_set
//{
//	unsigned short count;
//	SOCKET sockall[WSA_MAXIMUM_WAIT_EVENTS];
//	WSAEVENT eventall[WSA_MAXIMUM_WAIT_EVENTS];
//};
//
//BOOL WINAPI fun(DWORD DwCtrlType){
//	switch (DwCtrlType){
//	case CTRL_CLOSE_EVENT:
//
//		break;
//	}
//	return TRUE;
//}
//
//int main(void){
//	bool isGo = 1;
//
//	SetConsoleCtrlHandler(fun, TRUE);
//
//	WORD wVersion = MAKEWORD(2, 2);
//	WSADATA wsaData;
//	int resultMode = WSAStartup(wVersion, &wsaData);
//	if (0 != resultMode){
//		switch (resultMode)
//		{
//		case WSASYSNOTREADY:
//			printf("ϵͳ�쳣��������ϵͳ\n");
//			break;
//		case WSAVERNOTSUPPORTED:
//			printf("����ϵ������Ա");
//			break;
//		case WSAEINPROGRESS:
//			printf("�������������");
//			break;
//		case WSAEPROCLIM:
//			printf("�ڴ�ռ䲻�㣬��׼������ռ�");
//			break;
//		case WSAEFAULT:
//			printf("ָ���쳣���������");
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
//	if (INVALID_SOCKET == socketServer){
//		int errorMode = WSAGetLastError();
//
//		WSACleanup();
//		return 0;
//	}
//
//	struct sockaddr_in si;
//	si.sin_family = AF_INET;
//	si.sin_port = htons(5005);
//	si.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
//	if (SOCKET_ERROR == bind(socketServer, (const struct sockaddr*)&si, sizeof(si))){
//		int errorMode = WSAGetLastError();
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
//	struct fd_es_set esSet[20] = { 0, { 0 }, { NULL } };
//	memset(esSet, 0, sizeof(struct fd_es_set) * 20);
//
//	WSAEVENT eventServer = WSACreateEvent();
//	if (WSA_INVALID_EVENT == eventServer){
//		int resultMode = WSAGetLastError();
//
//		closesocket(socketServer);
//		WSACleanup();
//		return 0;
//	}
//	//�󶨲�Ͷ��
//	if (SOCKET_ERROR == WSAEventSelect(socketServer, eventServer, FD_ACCEPT)){
//		int a = WSAGetLastError();
//
//		WSACloseEvent(eventServer);
//		closesocket(socketServer);
//		WSACleanup();
//		return 0;
//	}
//
//	//װ��ȥ
//
//	esSet[0].eventall[esSet[0].count] = eventServer;
//	esSet[0].sockall[esSet[0].count] = socketServer;
//	esSet[0].count++;
//
//	while (true){
//		for (int j = 0; j < 20; j++){
//			if (0 == esSet[j].count){
//				continue;
//			}
//			DWORD nRes = WSAWaitForMultipleEvents(esSet[j].count, esSet[j].eventall, false, 0, false);
//			if (WSA_WAIT_FAILED == nRes){
//				//������
//				int a = WSAGetLastError();
//				printf("�����룺%d\n", a);
//				break;
//			}
//			else if (WSA_WAIT_TIMEOUT == nRes){
//				//�����ĸ�����Ϊ����ĵȴ�ʱ���ʱ������
//				continue;
//			}
//			DWORD index = nRes - WSA_WAIT_EVENT_0;
//
//
//			for (int nIndex = index; nIndex < esSet[j].count; nIndex++){
//				DWORD nRes = WSAWaitForMultipleEvents(1, &esSet[j].eventall[nIndex], false, 0, false);
//				if (WSA_WAIT_FAILED == nRes){
//					//������
//					int a = WSAGetLastError();
//					printf("�����룺%d\n", a);
//					continue;
//				}
//				else if (WSA_WAIT_TIMEOUT == nRes){
//					//�����ĸ�����Ϊ����ĵȴ�ʱ���ʱ������
//					continue;
//				}
//				WSANETWORKEVENTS NetWorkEvents;
//				//ö���¼�
//				if (SOCKET_ERROR == WSAEnumNetworkEvents(esSet[j].sockall[nIndex], esSet[j].eventall[nIndex], &NetWorkEvents)){
//					int a = WSAGetLastError();
//
//					break;
//				}
//				if (NetWorkEvents.lNetworkEvents & FD_ACCEPT){
//					if (0 == NetWorkEvents.iErrorCode[FD_ACCEPT_BIT]){
//						//��������
//						SOCKET socketClient = accept(esSet[j].sockall[nIndex], NULL, NULL);
//						if (INVALID_SOCKET == socketClient){
//							continue;
//						}
//
//						//�����¼�����
//						WSAEVENT wsaClientEvent = WSACreateEvent();
//						if (WSA_INVALID_EVENT == wsaClientEvent){
//							closesocket(socketClient);
//							continue;
//						}
//						//Ͷ��
//						if (SOCKET_ERROR == WSAEventSelect(socketClient, wsaClientEvent, FD_READ | FD_CLOSE | FD_WRITE)){
//							closesocket(socketClient);
//							WSACloseEvent(wsaClientEvent);
//							continue;
//						}
//						for (int m = 0; m < 20; m++){
//							if (esSet[m].count < 64){
//								//װ���ṹ��
//								esSet[m].sockall[esSet[m].count] = socketClient;
//								esSet[m].eventall[esSet[m].count] = wsaClientEvent;
//								esSet[m].count++;
//								break;
//							}
//						}
//
//					}
//					else{
//						continue;
//					}
//				}
//				if (NetWorkEvents.lNetworkEvents & FD_WRITE){
//					if (0 == NetWorkEvents.iErrorCode[FD_WRITE_BIT]){
//						//��ʼ��
//						if (SOCKET_ERROR == send(esSet[j].sockall[nIndex], "connect success", strlen("connect success"), 0)){
//							int a = WSAGetLastError();
//							printf("send failed,error Mode:%d\n", a);
//							continue;
//						}
//					}
//					else{
//						printf("FD_WRITE socket error,error Mode:%d\n", NetWorkEvents.iErrorCode[FD_WRITE_BIT]);
//						continue;
//					}
//				}
//				if (NetWorkEvents.lNetworkEvents & FD_READ){
//					if (0 == NetWorkEvents.iErrorCode[FD_READ_BIT]){
//						char strRecv[1500] = { 0 };
//						if (SOCKET_ERROR == recv(esSet[j].sockall[nIndex], strRecv, 1499, 0)){
//							int a = WSAGetLastError();
//							printf("recv failed,error code:%d\n", a);
//							continue;
//						}
//						printf("recv data:%s\n", strRecv);
//						//char buf[1500] = { 0 };
//						//scanf("%s", &buf);
//						//if (SOCKET_ERROR == send(esSet[j].sockall[nIndex], buf, strlen(buf), 0)){
//						//	continue;
//						//}
//					}
//					else{
//						printf("FD_READ socket error,error Mode:%d\n", NetWorkEvents.iErrorCode[FD_READ_BIT]);
//						continue;
//					}
//				}
//				if (NetWorkEvents.lNetworkEvents & FD_CLOSE){
//					if (0 == NetWorkEvents.iErrorCode[FD_CLOSE_BIT]){
//						WSAENETDOWN;
//						WSAECONNRESET;
//						WSAECONNABORTED;
//					}
//					else{
//						printf("client force out:%d\n", NetWorkEvents.iErrorCode[FD_CLOSE_BIT]);
//					}
//
//					printf("client close\n");
//					closesocket(esSet[j].sockall[nIndex]);
//					esSet[j].sockall[nIndex] = esSet[j].sockall[esSet[j].count - 1];
//					WSACloseEvent(esSet[j].eventall[nIndex]);
//					esSet[j].eventall[nIndex] = esSet[j].eventall[esSet[j].count - 1];
//
//					esSet[j].count--;
//				}
//			}
//		}
//		
//	}
//
//	//�ͷ��¼����
//	WSACloseEvent(eventServer);
//
//	closesocket(socketServer);
//
//	WSACleanup();
//
//	system("pause");
//	return 0;
//}