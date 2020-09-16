// Client.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#pragma comment(lib, "ws2_32.lib")
#include <winsock.h>
using namespace std;

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
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(1111);
	addr.sin_family = AF_INET;

	SOCKET Connection = socket(AF_INET, SOCK_STREAM, NULL);
	if (connect(Connection, (SOCKADDR*)&addr, sizeof(addr)) != 0)
	{
		cout << "Error: failed connect to server\n";
		return 1;
	}
	cout << "Connected\n";

	char first_word[100];
	char second_word[100];
	cout << "Enter two words\n";
	cin>>first_word;
	cin >> second_word;
	send(Connection, first_word, sizeof(first_word), 0);//sending message
	send(Connection, second_word, sizeof(second_word), 0);

	char result[6];

	recv(Connection, result, sizeof(result), NULL);
	cout << result;

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