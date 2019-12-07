//
//#include<iostream>
//#include<WinSock2.h>
//#pragma comment(lib, "Ws2_32.lib")
//using namespace std;
//
//int main(void){
//	//首先打开网络库
//	//DWORD wVersion = MAKEWORD(2, 2);
//	DWORD mVersion = (2 & 0xFF) | ((2 & 0xFF) << 8);
//	WSADATA wsaData;
//	int resultMode = WSAStartup(mVersion, &wsaData);
//	if (resultMode != 0){
//		switch (resultMode){
//		case WSASYSNOTREADY:
//			cout << "底层子网络尚未准备好通信" << endl;
//			break;
//		case WSAVERNOTSUPPORTED:
//			cout << "请联系开发人员，更新网络库" << endl;
//			break;
//		case WSAEINPROGRESS:
//			cout << "请重新启动软件" << endl;
//			break;
//		case WSAEPROCLIM:
//			cout << "请释放掉不必要的程序，以准备充足资源" << endl;
//			break;
//		case WSAEFAULT:
//			cout << "代码指针部分异常" << endl;
//			break;
//		}
//	}
//	//校验版本
//	if (2 != HIWORD(wsaData.wVersion) || 2 != LOWORD(wsaData.wVersion)){
//		printf("版本异常");
//		WSACleanup();
//		return 0;
//	}
//	//创建SOCKET
//	SOCKET socketServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
//	if (socketServer == INVALID_SOCKET){
//		int a = WSAGetLastError();
//		cout << "socketServer创建失败，错误码：" << a << endl;
//		WSACleanup();
//		return 0;
//	}
//	//绑定地址和端口
//
//
//
//	system("pause");
//	return 0;
//}