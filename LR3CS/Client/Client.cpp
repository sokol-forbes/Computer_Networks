// Client.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <conio.h>
#include<WinSock2.h>

#pragma comment(lib,"ws2_32.lib")

using namespace std;


int main()
{
	WORD wVersion = MAKEWORD(2, 2);
	WSADATA wsaData;

	if (WSAStartup(wVersion, &wsaData) != 0)
	{
		cerr << "Error client! #" << WSAGetLastError() << endl;
		exit(1);
	}

	char buf[256];
	while (true)
	{
		SOCKADDR_IN addr;
		addr.sin_family = AF_INET;
		addr.sin_port = htons(1280);
		addr.sin_addr.s_addr = inet_addr("127.0.0.1");

		SOCKET s = socket(AF_INET, SOCK_STREAM, 0);
		if (connect(s, (SOCKADDR*)&addr, sizeof(addr)) != 0)
		{
			cerr << "Failed to connect to server! #" << WSAGetLastError() << endl;
			exit(1);
		}
		cout << "Please enter string(enter ""exit""  for exit)" << endl;
		cin.getline(buf, sizeof(buf));
		if (!cin)
		{
			cout << "Error input!" << endl;
			exit(1);
		}

		send(s, buf, sizeof(buf), 0);
		if (!strcmp(buf, "exit"))
			break;

		if (recv(s, buf, sizeof(buf), 0) >= 0)
			cout << "Server: " << buf << endl;
		else
		{
			cerr << "Error client! #" << WSAGetLastError() << endl;
			exit(1);
		}
		closesocket(s);
	}
	WSACleanup();
}


