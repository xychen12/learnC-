#define _CRT_SECURE_NO_WARNINGS

#define FD_SETSIZE 128
//可以上万
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

//函数调用时，下面三个自动绑定
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
			printf("系统异常，请重启系统\n");
			break;
		case WSAVERNOTSUPPORTED:
			printf("请联系开发人员");
			break;
		case WSAEPROCLIM:
			printf("内存空间不足，请准备充足空间");
			break;
		case WSAEFAULT:
			printf("指针异常，请检查代码");
			break;
		default:
			break;
		}
	}

	//校验版本
	if (2 != HIBYTE(wsaData.wVersion) || 2 != LOBYTE(wsaData.wVersion)){
		printf("版本不符合要求");
		WSACleanup();
		return 0;
	}

	//WSA  window专用 windows socket async
	//WSASocket第4个参数，可以设置详细的属性
	WSAPROTOCOL_INFO info;

	//创建可供重叠IO机制的服务器socket
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

	//将服务端socket装入sock数组
	g_allSock[g_count] = socketServer;
	g_allOlp[g_count].hEvent = WSACreateEvent();
	g_count++;

	//开始accept，等待客户端接入
	if (0 != PostAccept()){
		//关闭所有socket和事件
		clear();
		WSACleanup();
		return 0;
	}

	while (1){
		//询问查找是否存在事件
        //这样只需要处理服务器就可以了
		int nRes = WSAWaitForMultipleEvents(1, &(g_allOlp[0].hEvent), FALSE, WSA_INFINITE, TRUE);
		if (WSA_WAIT_FAILED == nRes || WSA_WAIT_IO_COMPLETION == nRes){
			continue;
		}
		//把信号置为空
		WSAResetEvent(g_allOlp[0].hEvent);

		//如果是服务器socket，接收连接完成了, 投递acceptEx
		PostSend(g_count);
		printf("accept\n");
		//接收连接完成了
		//接收数据，接收数据后，将服务器再次置为接收客户端的状态
		//如果是服务器socket接收到消息，那么一定是最后一个发过来的接入消息，所以接入后，要把数据接收投递出去
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
		//创建客户端socket
		g_allSock[g_count] = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
		g_allOlp[g_count].hEvent = WSACreateEvent();

		char str[1024] = { 0 };
		DWORD dwRecvcount;
		bool bRes = AcceptEx(g_allSock[0], g_allSock[g_count], str, 0, sizeof(struct sockaddr_in) + 16, sizeof(struct sockaddr_in) + 16, &dwRecvcount, &g_allOlp[0]);
		//如果为true，马上处理，如果为false，则等待
		if (bRes){
			//立即返回
			//立即对客户端socket投递接收消息的事件
			PostRecv(g_count);
			//根据情况send
			send(g_allSock[g_count], "收到了，喵", sizeof("收到了，喵"), 0);
			//客户端适量++
			g_count++;
			//再次向操作系统投递服务器事件
			PostAccept();
			continue;
		}
		else{
			//异步等待，或者出现错误
			int a = WSAGetLastError();
			if (ERROR_IO_PENDING == a){
				//异步等待
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
		//删除客户端
		printf("close\n");
		//客户端下线
		//关闭
		closesocket(g_allSock[i]);
		WSACloseEvent(g_allOlp[i].hEvent);
		//从数组中删掉
		g_allSock[i] = g_allSock[g_count - 1];
		g_allOlp[i] = g_allOlp[g_count - 1];
		//个数减 - 1
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
		//立即完成
		printf("%s\n", wsabuf.buf);
		//清空
		memset(wsabuf.buf, 0, MAX_RECV_COUNT);
		//根据需要send

		//继续投递接收数据事件，继续等待着接收
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
	wsabuf.buf = "喵";
	wsabuf.len = MAX_RECV_COUNT;

	DWORD dwRecvCount;
	DWORD dwFlag = 0;
	int nRes = WSASend(g_allSock[index], &wsabuf, 1, &dwRecvCount, dwFlag, &g_allOlp[index], SendCall);
	if (0 == nRes){
		//立即完成
		printf("发送成功\n");

		return 0;
	}
	else{
		int a = WSAGetLastError();

		if (ERROR_IO_PENDING == a){

		}
	}
}