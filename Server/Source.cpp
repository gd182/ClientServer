#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream> 
#include <cstdio> 
#include <cstring> 
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

	bind(s, (SOCKADDR*)&sa, sizeof(sa));
	listen(s, 100);
	SOCKET client_s;
	SOCKADDR_IN client_addr;
	int client_addr_size = sizeof(client_addr);
	while (client_s = accept(s, (SOCKADDR*)&client_addr, &client_addr_size)) {
		cout << "Client connect"<<endl;
		int lenM;
		while (recv(client_s, (char*)&lenM, sizeof(lenM), 0) > 0) {
			string BufM = "";
			BufM.resize(lenM);
			recv(client_s, (char*)BufM.c_str(), sizeof(BufM[0]) * lenM, 0);
			cout << BufM << endl;
			BufM = "Сообщение полученно";
			lenM = BufM.length();
			send(client_s, (char*)&lenM, sizeof(lenM), 0);
			send(client_s, (char*)BufM.c_str(), sizeof(BufM[0])*lenM, 0);
			//recv(client_s, (char*)&lenM, sizeof(lenM), 0);

		}
	}
}