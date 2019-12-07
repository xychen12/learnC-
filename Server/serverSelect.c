//#define _CRT_SECURE_NO_WARNINGS
//#define _WINSOCK_DEPRECATED_NO_WARNINGS
//
//#define FD_SETSIZE 128
//
//#include<stdlib.h>
//#include<stdio.h>
//#include<stdbool.h>
//#include <WinSock2.h>
//#pragma comment(lib, "Ws2_32.lib")
//
////selectģ��
//fd_set socketAll;
//
//BOOL WINAPI fun(DWORD DwCtrlType){
//	switch (DwCtrlType)
//	{
//	case CTRL_CLOSE_EVENT:
//		for (u_int i = 0; i < socketAll.fd_count; i++){
//			closesocket(socketAll.fd_array[i]);
//		}
//		WSACleanup();
//	}
//	return TRUE;
//}
//
//
//int main(void){
//	SetConsoleCtrlHandler(fun, TRUE);
//
//	//���ȴ������
//	WORD wVersion = MAKEWORD(2, 2);
//	WSADATA wsaData;
//	int resultMode = WSAStartup(wVersion, &wsaData);
//	if (0 != resultMode){
//		switch (resultMode)
//		{
//		case WSASYSNOTREADY:
//			printf("�ײ���������δ׼����ͨ��");
//			break;
//		case WSAVERNOTSUPPORTED:
//			printf("����ϵ������Ա�����������");
//			break;
//		case WSAEINPROGRESS:
//			printf("�������������");
//			break;
//		case WSAEPROCLIM:
//			printf("���ͷŵ�����Ҫ�ĳ�����׼��������Դ");
//			break;
//		case WSAEFAULT:
//			printf("����ָ�벿���쳣");
//			break;
//		default:
//			break;
//		}
//	}
//
//	//У��汾
//	if (2 != HIBYTE(wsaData.wVersion) || 2 != LOBYTE(wsaData.wVersion)){
//		printf("�汾�쳣");
//		WSACleanup();
//		return 0;
//	}
//
//	//����������socket
//	SOCKET socketServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
//	if (INVALID_SOCKET == socketServer){
//		int a = WSAGetLastError();
//		printf("socketServer����ʧ�ܣ������룺%d", a);
//		WSACleanup();
//		return 0;
//	}
//
//	//�󶨵�ַ�Ͷ˿�
//	struct sockaddr_in sockAddr;
//	sockAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
//	sockAddr.sin_family = AF_INET;
//	sockAddr.sin_port = htons(5005);
//
//	int resultModeBind = bind(socketServer, (const struct sockaddr*)&sockAddr, sizeof(sockAddr));
//	if (INVALID_SOCKET == resultModeBind){
//		int a = WSAGetLastError();
//		printf("�󶨵�ַ�Ͷ˿ڣ������룺%d", a);
//
//		closesocket(socketServer);
//		WSACleanup();
//		return 0;
//	}
//
//	//��ʼ����
//	int resultModeListen = listen(socketServer, SOMAXCONN);
//	if (INVALID_SOCKET == resultModeListen){
//		int a = WSAGetLastError();
//		printf("��ʼ����ʧ�ܣ������룺%d", a);
//
//		closesocket(socketServer);
//		WSACleanup();
//		return 0;
//	}
//
//	//fd_set socketAll;
//
//	FD_ZERO(&socketAll);
//	//��ӷ�����socket
//	FD_SET(socketServer, &socketAll);
//
//	struct timeval timeout;
//	timeout.tv_sec = 3;
//	timeout.tv_usec = 0;
//
//	//��ʼѭ�������������¼�
//	while (1){
//		fd_set readsockets = socketAll;
//		fd_set writesockets = socketAll;
//		//�ѷ�������writesockets������
//		FD_CLR(socketServer, &writesockets);
//
//		fd_set errorsockets = socketAll;
//
//		int resultMode = select(0, &readsockets, &writesockets, &errorsockets, &timeout);
//		if (0 == resultMode){
//			continue;
//		}
//		else if (0 < resultMode){
//			char buf[100] = { 0 };
//			int length = 0;
//			for (u_int i = 0; i < errorsockets.fd_count; i++){
//				if (SOCKET_ERROR == getsockopt(errorsockets.fd_array[i], SOL_SOCKET, SO_ERROR, buf, &length)){
//					printf("�޷���ȡ������Ϣ");
//				}
//				printf("����%s\n", buf);
//			}
//			for (u_int i = 0; i < writesockets.fd_count; i++){
//				if (SOCKET_ERROR == send(writesockets.fd_array[i], "abed", sizeof("abed"), 0)){
//					SOCKET tempSocket = writesockets.fd_array[i];
//					FD_CLR(writesockets.fd_array[i], &writesockets);
//					closesocket(tempSocket);
//				}
//			}
//			for (u_int i = 0; i < readsockets.fd_count; i++){
//				if (socketServer == readsockets.fd_array[i]){
//					//������
//					struct sockaddr_in clientMsg;
//					int len = sizeof(clientMsg);
//					SOCKET socketclient = accept(socketServer, (struct sockaddr*)&clientMsg, &len);
//					if (INVALID_SOCKET == socketclient){
//						continue;
//					}
//					FD_SET(socketclient, &socketAll);
//					send(socketclient, "���ӳɹ�", sizeof("���ӳɹ�"), 0);
//				}
//				else{
//					char buf[1500] = { 0 };
//					int resultRecv = recv(readsockets.fd_array[i], buf, 1499, 0);
//					if (0 == resultRecv){
//						printf("�ͻ�������");
//						SOCKET tempSocket = readsockets.fd_array[i];
//						FD_CLR(readsockets.fd_array[i], &readsockets);
//						closesocket(tempSocket);
//					}
//					else if (0 < resultRecv){
//						printf("%s\n", buf);
//					}
//					else{
//						int a = WSAGetLastError();
//						switch (a)
//						{
//						case 10054:
//							printf("�ͻ���ǿ������");
//							//�����������socket
//							SOCKET socketTemp = readsockets.fd_array[i];
//							FD_CLR(readsockets.fd_array[i], &socketAll);
//
//							closesocket(socketTemp);
//							break;
//						default:
//							break;
//						}
//					}
//				}
//			}
//		}
//		else{
//			int a = WSAGetLastError();
//		}
//	}
//	for (u_int i = 0; i < socketAll.fd_count; i++){
//		closesocket(socketAll.fd_array[i]);
//	}
//
//	WSACleanup();
//
//	system("pause");
//	return 0;
//}