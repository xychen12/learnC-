//
//#include<iostream>
//#include<WinSock2.h>
//#pragma comment(lib, "Ws2_32.lib")
//using namespace std;
//
//int main(void){
//	//���ȴ������
//	//DWORD wVersion = MAKEWORD(2, 2);
//	DWORD mVersion = (2 & 0xFF) | ((2 & 0xFF) << 8);
//	WSADATA wsaData;
//	int resultMode = WSAStartup(mVersion, &wsaData);
//	if (resultMode != 0){
//		switch (resultMode){
//		case WSASYSNOTREADY:
//			cout << "�ײ���������δ׼����ͨ��" << endl;
//			break;
//		case WSAVERNOTSUPPORTED:
//			cout << "����ϵ������Ա�����������" << endl;
//			break;
//		case WSAEINPROGRESS:
//			cout << "�������������" << endl;
//			break;
//		case WSAEPROCLIM:
//			cout << "���ͷŵ�����Ҫ�ĳ�����׼��������Դ" << endl;
//			break;
//		case WSAEFAULT:
//			cout << "����ָ�벿���쳣" << endl;
//			break;
//		}
//	}
//	//У��汾
//	if (2 != HIWORD(wsaData.wVersion) || 2 != LOWORD(wsaData.wVersion)){
//		printf("�汾�쳣");
//		WSACleanup();
//		return 0;
//	}
//	//����SOCKET
//	SOCKET socketServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
//	if (socketServer == INVALID_SOCKET){
//		int a = WSAGetLastError();
//		cout << "socketServer����ʧ�ܣ������룺" << a << endl;
//		WSACleanup();
//		return 0;
//	}
//	//�󶨵�ַ�Ͷ˿�
//
//
//
//	system("pause");
//	return 0;
//}