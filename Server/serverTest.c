//#define _CRT_SECURE_NO_WARNINGS
//#include<stdio.h>
//#include<stdlib.h>
//#include<WinSock2.h>
//#include<string.h>
//#include<Windows.h>
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
//		break;
//	default:
//		break;
//	}
//	return TRUE;
//}
//int main(void){
//
//	SetConsoleCtrlHandler(fun, TRUE);
//
//	//�������
//	WORD wVersion = MAKEWORD(2, 3);
//	WSADATA wsaData;
//	int resultMode = WSAStartup(wVersion, &wsaData);
//	if (0 != resultMode){
//		switch (resultMode)
//		{
//		case WSASYSNOTREADY:
//			printf("ϵͳδ׼�����\n");
//			break;
//		case WSAEPFNOSUPPORT:
//			printf("����ϵ������Ա���������");
//			break;
//		case WSAEINPROGRESS:
//			printf("�����������");
//			break;
//		case WSAEPROCLIM:
//			printf("��׼��������Դ");
//			break;
//		case WSAEFAULT:
//			printf("ָ���쳣���������");
//			break;
//		default:
//			break;
//		}
//	}
//
//	//У��汾
//	if (2 != HIBYTE(wsaData.wVersion) || 2 != LOBYTE(wsaData.wVersion)){
//		//����/�ر������
//		WSACleanup();
//		return 0;
//	}
//
//	//����������socket
//	SOCKET socketServer = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
//	if (INVALID_SOCKET == socketServer){
//		int errorMode = WSAGetLastError();
//
//		WSACleanup();
//		return 0;
//	}
//
//	//��ip�Ͷ˿�
//	struct sockaddr_in si;
//	si.sin_family = AF_INET;
//	si.sin_port = htons(5005);
//	si.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
//	
//	if (SOCKET_ERROR == bind(socketServer, (const struct sockaddr*)&si, sizeof(si))){
//		int a = WSAGetLastError();
//
//		closesocket(socketServer);
//		WSACleanup();
//		return 0;
//	}
//
//	//�����˿�
//	if (SOCKET_ERROR == listen(socketServer, SOMAXCONN)){
//		int a = WSAGetLastError();
//
//		closesocket(socketServer);
//		WSACleanup();
//		return 0;
//	}
//
//
//
//
//
//
//
//
//
//
//	//selectģ��
//	////ȫ������
//	//FD_ZERO(&socketAll);
//	////���������socket
//	//FD_SET(socketServer, &socketAll);
//
//	//struct timeval timeout;
//	//timeout.tv_sec = 3;
//	//timeout.tv_usec = 0;
//
//	////ѭ�����ÿһ���¼�
//	//while (1){
//
//	//	fd_set readSockets = socketAll;
//	//	fd_set writeSockets = socketAll;
//	//	fd_set errorSockets = socketAll;
//	//	int ret = select(0, &readSockets, &writeSockets, &errorSockets, &timeout);
//	//	if (0 == ret){
//	//		continue;
//	//	}
//	//	else if (0 < ret){
//	//		char buf[100] = { 0 };
//	//		int length = 0;
//	//		for (u_int i = 0; i < errorSockets.fd_count; i++){
//	//			if (SOCKET_ERROR == getsockopt(errorSockets.fd_array[i], SOL_SOCKET, SO_ERROR, buf, &length)){
//	//				printf("�޷���ȡ������Ϣ");
//	//			}
//	//			printf("%s\n", buf);
//	//		}
//	//		for (u_int i = 0; i < writeSockets.fd_count; i++){
//	//			//if (SOCKET_ERROR == send(writeSockets.fd_array[i], "�յ�over", sizeof("�յ�over"), 0)){
//	//			//	SOCKET tempSocket = writeSockets.fd_array[i];
//	//			//	FD_CLR(writeSockets.fd_array[i], &writeSockets);
//	//			//	closesocket(tempSocket);
//	//			//}
//	//		}
//	//		for (u_int i = 0; i < readSockets.fd_count; i++){
//	//			if (socketServer == readSockets.fd_array[i]){
//	//				struct sockaddr_in si;
//	//				int length = sizeof(si);
//	//				SOCKET socketClient = accept(readSockets.fd_array[i], (struct sockaddr*)&si, &length);
//	//				if (INVALID_SOCKET == socketClient){
//	//					continue;
//	//				}
//	//				FD_SET(socketClient, &socketAll);
//	//				send(socketClient, "���ӳɹ�", sizeof("���ӳɹ�"), 0);
//	//			}
//	//			else{
//	//				char buf[1500] = { 0 };
//	//				int resultRecv = recv(readSockets.fd_array[i], buf, 1499, 0);
//	//				if (0 == resultRecv){
//	//					printf("�ͻ�������");
//	//					SOCKET tempSocket = readSockets.fd_array[i];
//	//					FD_CLR(readSockets.fd_array[i], &readSockets);
//	//					closesocket(tempSocket);
//	//				}
//	//				else if(0 < resultRecv){
//	//					printf("%s\n", buf);
//	//				}
//	//				else{
//	//					int a = WSAGetLastError();
//
//	//					switch (a)
//	//					{
//	//					case 10054:
//	//						printf("�ͻ���ǿ������");
//	//						SOCKET tempSocket = readSockets.fd_array[i];
//	//						FD_CLR(readSockets.fd_array[i], &readSockets);
//	//						closesocket(tempSocket);
//	//						break;
//	//					default:
//	//						break;
//	//					}
//	//				}
//
//	//				char buf1[1500] = {0};
//	//				scanf("%s", buf1);
//	//				send(readSockets.fd_array[i], buf1, strlen(buf1), 0);
//	//			}
//	//		}
//	//	}
//	//	else{
//	//		int a = WSAGetLastError();
//	//		break;
//	//	}
//	//}
//
//	//for (u_int i = 0; i < socketAll.fd_count; i++){
//	//	closesocket(socketAll.fd_array[i]);
//	//}
//	//
//	//WSACleanup();
//
//
//	//��ͨCS
//	////�����ͻ���socket
//	//struct sockaddr_in msgClient;
//	//int len = sizeof(msgClient);
//	//SOCKET socketClient = accept(socketServer, (struct sockaddr*)&msgClient, &len);
//	//if (INVALID_SOCKET == socketClient){
//	//	int a = WSAGetLastError();
//
//	//	closesocket(socketServer);
//	//	WSACleanup();
//	//	return 0;
//	//}
//
//	//printf("�ͻ������ӳɹ�");
//
//	//if (SOCKET_ERROR == send(socketClient, "�������յ�", sizeof("�������յ�"), 0)){
//	//	int a = WSAGetLastError();
//
//	//	closesocket(socketServer);
//	//	WSACleanup();
//	//	return 0;
//	//}
//
//	////��ͻ����շ���Ϣ
//	//while (1){
//	//	char buf[1500] = { 0 };
//	//	int ret = recv(socketClient, buf, 1499, 0);
//	//	if (0 == ret){
//	//		printf("�ͻ�������");
//	//	}
//	//	else if (SOCKET_ERROR == ret){
//	//		int a = WSAGetLastError();
//	//	}
//	//	else{
//	//		printf("%s\n", buf);
//	//	}
//
//	//	char buf1[1500] = { 0 };
//	//	scanf("%s", &buf1);
//	//	if (SOCKET_ERROR == send(socketClient, buf1, strlen(buf1), 0)){
//	//		int a = WSAGetLastError();
//
//	//		closesocket(socketServer);
//	//		WSACleanup();
//	//		return 0;
//	//	}	
//	//}
//
//	//�ر�
//	//closesocket(socketServer);
//	//closesocket(socketClient);
//	//WSACleanup();
//
//
//	system("pause");
//	return 0;
//}