#define _CRT_SECURE_NO_WARNINGS

#define FD_SETSIZE 128
//��������
#define MAX_COUNT 1024
#define MAX_RECV_COUNT 1024

#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include<WinSock2.h>
#include<MSWSock.h>
#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "Mswsock.lib")

//��������ʱ�����������Զ���
SOCKET g_allSock[MAX_COUNT];
OVERLAPPED g_allOlp[MAX_COUNT];
int g_count;
char str[MAX_RECV_COUNT];

int PostAccept();
int PostRecv(int index);
int PostSend(int index);

void clear(){
	for (int i = 0; i < g_count; i++){
		closesocket(g_allSock[i]);
		WSACloseEvent(g_allOlp[i].hEvent);
	}
}

BOOL WINAPI fun(DWORD DwCtrlType){
	switch (DwCtrlType)
	{
	case CTRL_CLOSE_EVENT:
		for (int i = 0; i < g_count; i++){
			closesocket(g_allSock[i]);
			WSACloseEvent(g_allOlp[i].hEvent);
		}
		break;
	default:
		break;
	}
	return TRUE;
}

int main(){

	SetConsoleCtrlHandler(fun, TRUE);

	bool isGo = 1;

	WORD wVersion = MAKEWORD(2, 2);
	WSADATA wsaData;
	int resultMode = WSAStartup(wVersion, &wsaData);

	if (0 != resultMode){
		switch (resultMode)
		{
		case WSASYSNOTREADY:
			printf("ϵͳ�쳣��������ϵͳ\n");
			break;
		case WSAVERNOTSUPPORTED:
			printf("����ϵ������Ա");
			break;
		case WSAEPROCLIM:
			printf("�ڴ�ռ䲻�㣬��׼������ռ�");
			break;
		case WSAEFAULT:
			printf("ָ���쳣���������");
			break;
		default:
			break;
		}
	}

	//У��汾
	if (2 != HIBYTE(wsaData.wVersion) || 2 != LOBYTE(wsaData.wVersion)){
		printf("�汾������Ҫ��");
		WSACleanup();
		return 0;
	}

	//WSA  windowר�� windows socket async
	//WSASocket��4������������������ϸ������
	WSAPROTOCOL_INFO info;

	//�����ɹ��ص�IO���Ƶķ�����socket
	SOCKET socketServer = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
	if (INVALID_SOCKET == socketServer){
		int a = WSAGetLastError();

		WSACleanup();
		return 0;
	}

	struct sockaddr_in si;
	si.sin_family = AF_INET;
	si.sin_port = htons(5005);
	si.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	if (SOCKET_ERROR == bind(socketServer, (const struct sockaddr*)&si, sizeof(si))){
		int a = WSAGetLastError();

		closesocket(socketServer);
		WSACleanup();
		return 0;
	}

	if (SOCKET_ERROR == listen(socketServer, SOMAXCONN)){
		int a = WSAGetLastError();

		closesocket(socketServer);
		WSACleanup();
		return 0;
	}

	//�������socketװ��sock����
	g_allSock[g_count] = socketServer;
	g_allOlp[g_count].hEvent = WSACreateEvent();
	g_count++;

	//��ʼaccept���ȴ��ͻ��˽���
	if (0 != PostAccept()){
		//�ر�����socket���¼�
		clear();
		WSACleanup();
		return 0;
	}

	while (1){
		//ѯ�ʲ����Ƿ�����¼�
        //����ֻ��Ҫ����������Ϳ�����
		int nRes = WSAWaitForMultipleEvents(1, &(g_allOlp[0].hEvent), FALSE, WSA_INFINITE, TRUE);
		if (WSA_WAIT_FAILED == nRes || WSA_WAIT_IO_COMPLETION == nRes){
			continue;
		}
		//���ź���Ϊ��
		WSAResetEvent(g_allOlp[0].hEvent);

		//����Ƿ�����socket���������������, Ͷ��acceptEx
		PostSend(g_count);
		printf("accept\n");
		//�������������
		//�������ݣ��������ݺ󣬽��������ٴ���Ϊ���տͻ��˵�״̬
		//����Ƿ�����socket���յ���Ϣ����ôһ�������һ���������Ľ�����Ϣ�����Խ����Ҫ�����ݽ���Ͷ�ݳ�ȥ
		PostRecv(g_count);
		g_count++;
		PostAccept();
	}

	clear();
	WSACleanup();

	system("pause");
	return 0;
}

int PostAccept(){
	while (1){
		//�����ͻ���socket
		g_allSock[g_count] = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
		g_allOlp[g_count].hEvent = WSACreateEvent();

		char str[1024] = { 0 };
		DWORD dwRecvcount;
		bool bRes = AcceptEx(g_allSock[0], g_allSock[g_count], str, 0, sizeof(struct sockaddr_in) + 16, sizeof(struct sockaddr_in) + 16, &dwRecvcount, &g_allOlp[0]);
		//���Ϊtrue�����ϴ������Ϊfalse����ȴ�
		if (bRes){
			//��������
			//�����Կͻ���socketͶ�ݽ�����Ϣ���¼�
			PostRecv(g_count);
			//�������send
			send(g_allSock[g_count], "�յ��ˣ���", sizeof("�յ��ˣ���"), 0);
			//�ͻ�������++
			g_count++;
			//�ٴ������ϵͳͶ�ݷ������¼�
			PostAccept();
			continue;
		}
		else{
			//�첽�ȴ������߳��ִ���
			int a = WSAGetLastError();
			if (ERROR_IO_PENDING == a){
				//�첽�ȴ�
				break;
			}
			else{
				break;
			}
		}
	}
	return 0;
}

void CALLBACK RecvCall(DWORD dwError, DWORD cbTransferred, LPWSAOVERLAPPED lpOverlapped, DWORD dwFlags){
	int i = 0;
	for (i; i < g_count; i++){
		if (lpOverlapped == g_allOlp[i].hEvent){
			break;
		}
	}

	i = lpOverlapped - &g_allOlp[0];

	if (10054 == dwError || 0 == cbTransferred)
	{
		//ɾ���ͻ���
		printf("close\n");
		//�ͻ�������
		//�ر�
		closesocket(g_allSock[i]);
		WSACloseEvent(g_allOlp[i].hEvent);
		//��������ɾ��
		g_allSock[i] = g_allSock[g_count - 1];
		g_allOlp[i] = g_allOlp[g_count - 1];
		//������ - 1
		g_count--;
	}
	else{
		printf("%s\n", str);
		memset(str, 0, MAX_RECV_COUNT);
		PostRecv(i);
	}
}

int PostRecv(int index){

	WSABUF wsabuf;
	wsabuf.buf = str;
	wsabuf.len = MAX_RECV_COUNT;

	DWORD dwRecvCount;
	DWORD dwFlag = 0;

	int nRes = WSARecv(g_allSock[index], &wsabuf, 1, &dwRecvCount, &dwFlag, &g_allOlp[index], RecvCall);
	if (0 == nRes){
		//�������
		printf("%s\n", wsabuf.buf);
		//���
		memset(wsabuf.buf, 0, MAX_RECV_COUNT);
		//������Ҫsend

		//����Ͷ�ݽ��������¼��������ȴ��Ž���
		PostRecv(index);
		return 0;
	}
	else{
		int a = WSAGetLastError();

		if (ERROR_IO_PENDING == a){
			return 0;
		}
		else{
			return 0;
		}
	}
}

void CALLBACK SendCall(DWORD dwError, DWORD cbTransferred, LPWSAOVERLAPPED lpOverlapped, DWORD dwFlags){
	printf("send over\n");
}

int PostSend(int index){

	WSABUF wsabuf;
	wsabuf.buf = "��";
	wsabuf.len = MAX_RECV_COUNT;

	DWORD dwRecvCount;
	DWORD dwFlag = 0;
	int nRes = WSASend(g_allSock[index], &wsabuf, 1, &dwRecvCount, dwFlag, &g_allOlp[index], SendCall);
	if (0 == nRes){
		//�������
		printf("���ͳɹ�\n");

		return 0;
	}
	else{
		int a = WSAGetLastError();

		if (ERROR_IO_PENDING == a){

		}
	}
}