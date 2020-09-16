// Server.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#pragma comment(lib, "ws2_32.lib")
#include <winsock.h>
using namespace std;

bool compare(char first_word[], char second_word[], int size)
{
	bool result = true;
	for (int i = 0; i < sizeof(first_word); i++)
	{
		if (first_word[i] != second_word[i])
			result = false;
	}
	return result;
}

int main()
{
	WSADATA wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);
	if (WSAStartup(DLLVersion, &wsaData) != 0)
	{
		cout << "Lib Error" << endl;
		exit(1);
	}
	SOCKADDR_IN addr;
	int sizeofaddr = sizeof(addr);
	addr.sin_addr.s_addr = 0;
	addr.sin_port = htons(1111);
	addr.sin_family = AF_INET;

	SOCKET slisten = socket(AF_INET, SOCK_STREAM, NULL);
	bind(slisten, (SOCKADDR*)&addr, sizeof(addr));
	listen(slisten, SOMAXCONN);
	SOCKET newConnection;
	newConnection = accept(slisten, (SOCKADDR*)&addr, &sizeofaddr);
	if (newConnection == 0)
	{
		cout << "Error";
	}
	else {
		cout << "Client Connected!" << endl;
	}
	char first_word[100];
	char second_word[100];
	recv(newConnection, first_word, sizeof(first_word), 0);//get message
	recv(newConnection, second_word, sizeof(first_word), 0);
	//cout « mama;
	char result[6];
	if (sizeof(first_word) == sizeof(second_word))
	{
		if (compare(first_word, second_word, sizeof(first_word)) == true)
			strcpy_s(result, "true");
		else strcpy_s(result, "false");
	}
	//else result = false;
	send(newConnection, result, sizeof(result), NULL);
	return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы
// 1. В окне обозревателя решений можно добавлять файлы и управлять ими.
// 2. В окне Team Explorer можно подключиться к системе управления версиями.
// 3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
// 4. В окне "Список ошибок" можно просматривать ошибки.
// 5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
// 6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
