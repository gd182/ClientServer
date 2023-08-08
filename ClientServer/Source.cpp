#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream> 
#include <sstream>
#include <string>
#include <winsock2.h> 
#pragma comment(lib, "WS2_32.lib")

using namespace std;


void main() {
	setlocale(LC_ALL, "ru");
	WSADATA WSAData;
	WSAStartup(MAKEWORD(2, 2), &WSAData);
	SOCKET s;
	s = socket(AF_INET, SOCK_STREAM, 0);

	SOCKADDR_IN sa;
	memset(&sa, 0, sizeof(sa));
	sa.sin_family = AF_INET;
	sa.sin_port = htons(1234);

	sa.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

	connect(s, (SOCKADDR*)&sa, sizeof(sa));

	while (true) {
		string BufM;
		getline(cin, BufM);
		int lenM = BufM.length();
		send(s, (char*)&lenM, sizeof(lenM), 0);
		send(s, (char*)BufM.c_str(), sizeof(BufM[0]) * lenM, 0);
		recv(s, (char*)&lenM, sizeof(lenM), 0);
		BufM = "";
		BufM.resize(lenM);
		recv(s, (char*)BufM.c_str(), sizeof(BufM[0]) * lenM, 0);
		cout << BufM << endl;
		/*char st[30];
		memset(&st, 0, sizeof(st));
		recv(s, st, sizeof(st), 0);
		cout << st << endl;*/
	}
	closesocket(s);
	system("pause");

}