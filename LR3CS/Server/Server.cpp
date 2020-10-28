// Server.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <WinSock2.h>
#include <iostream>

#pragma comment(lib,"ws2_32.lib")

using namespace std;



DWORD WINAPI ThreadFunc(LPVOID client_socket)
{
	SOCKET s = ((SOCKET*)client_socket)[0];
	char str[256];
	while ((recv(s, str, sizeof(str), 0)))
	{
		if (strlen(str) == 0)
			send(s, "The string must not be empty", sizeof("The string must not be empty"), 0);
		else
		{
			cout << "Client: " << str << endl;
			if (!strcmp(str, "exit"))
				break;

			if (strlen(str) == 1)
				send(s, "Empty string", sizeof("Empty string"), 0);

			if (strlen(str) % 2 != 0)
			{
				for (int i = strlen(str) / 2; i < strlen(str); i++)
					str[i] = str[i + 1];
			}
			send(s, str, sizeof(str), 0);
		}
	}
	cout << "Client deleted!\n" << endl;
	closesocket(s);
	return 0;
}

int main()
{
	WORD wVersion = MAKEWORD(2, 2);
	WSADATA wsaData;
	if (WSAStartup(wVersion, &wsaData) != 0)
	{
		cerr << "Server error! #" << WSAGetLastError() << endl;
		exit(1);
	}
	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(1280);
	addr.sin_addr.s_addr = 0;

	SOCKET s = socket(AF_INET, SOCK_STREAM, 0);
	if (bind(s, (SOCKADDR*)&addr, sizeof(addr)) == SOCKET_ERROR)
	{
		cerr << "Can't bind socket #" << WSAGetLastError() << endl;
		exit(1);
	}
	listen(s, 5);
	cout << "Server created!" << endl;

	SOCKET client_socket;
	int size = sizeof(addr);

	while (client_socket = accept(s, (SOCKADDR*)&addr, &size))
	{
		cout << "Client connected!" << endl;
		DWORD thID;
		CreateThread(NULL, NULL, ThreadFunc, &client_socket, NULL, &thID);
	}

	closesocket(s);
	WSACleanup();
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
