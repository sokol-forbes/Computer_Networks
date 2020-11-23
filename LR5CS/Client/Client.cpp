// Client.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>
#include <iostream>
#include <conio.h>
#include <ctime>
#include <sstream>
#include <string>
#pragma comment(lib,"ws2_32.lib")

using namespace std;


bool check_command(string&);
bool check_address(string&);
bool check_message(string&);
void check_str(char[]);

int main()
{
	WORD wVersion = MAKEWORD(2, 2);
	WSADATA wsaData;

	if (WSAStartup(wVersion, &wsaData) != 0)
	{
		cerr << "Error client! #" << WSAGetLastError() << endl;
		exit(1);
	}

	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(1280);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	SOCKET s = socket(AF_INET, SOCK_STREAM, 0);

	if (connect(s, (SOCKADDR*)&addr, sizeof(addr)) != 0)
	{
		cerr << "Error connect with server! #" << WSAGetLastError() << endl;
		exit(1);
	}


	char buf[256];
	recv(s, buf, sizeof(buf), 0);
	cout << buf;

	char buf2[1150];

	while (true)
	{
		check_str(buf);
		send(s, buf, sizeof(buf), 0);
		if (!strcmp(buf, "-quit"))
			exit(0);

		if (recv(s, buf2, sizeof(buf2), 0) >= 0)
			cout << buf2;

	}

}



bool check_command(string& str)
{
	char q;
	str.clear();
	while ((q = _getch()) != (' '))
	{
		if (q == '\r')
			break;
		if (q == 8)
		{
			if (!str.empty())
			{
				cout << (char)8 << " " << char(8);
				str.erase(str.length() - 1);
			}
		}
		else if (q >= 'a' && q <= 'z' || q >= 'A' && q <= 'Z' || q == '-')
		{
			cout << q;
			if (q >= 'A' && q <= 'Z')
				q += 32;
			str += char(q);
		}
	}

	if (str.length() == 0 || str.length() >= 8)
	{
		system("cls");
		if (str.length() == 0)
			cout << "Incorrect command entry!" << endl;
		else
			cout << "Command is too big!" << endl;
		system("pause & cls");
		return true;
	}

	if (str[0] != '-')
		cout << " <";
	return false;
}

bool check_address(string& str)
{
	char q;
	str.clear();

	while ((q = _getch()) != '>')
	{
		if (q == '\r')
			break;
		if (q == 8)
		{
			if (!str.empty())
			{
				cout << (char)8 << " " << char(8);
				str.erase(str.length() - 1);
			}
		}
		else if (q >= 'a' && q <= 'z' || q >= 'A' && q <= 'Z' || q >= '0' && q <= '9' || q == '@' || q == '.')
		{
			cout << q;
			str += char(q);
		}
	}


	if (str.length() == 0 || str.length() >= 20)
	{
		system("cls");
		if (str.length() == 0)
			cout << "Incorrect address entry!" << endl;
		else
			cout << "Address is too big!" << endl;

		system("pause & cls");
		return true;
	}

	cout << "> /";
	return false;
}

bool check_message(string& str)
{
	char q;
	str.clear();
	time_t t = time(0);
	tm* now = localtime(&t);

	stringstream ss;
	ss << "Date: " << now->tm_mday << ":" << (now->tm_mon + 1) << ":" << (now->tm_year + 1900) << " Time: " << now->tm_hour << ":" << now->tm_min << ":" << now->tm_sec << " ";
	str += ss.str();
	int i = str.size();

	while ((q = _getch()) != '/')
	{
		if (q == '\r')
			break;
		if (q == 8)
		{
			if ((str.size() - i))
			{
				cout << (char)8 << " " << char(8);
				str.erase(str.length() - 1);
			}
		}
		else if (q >= 'a' && q <= 'z' || q >= 'A' && q <= 'Z' || q >= '0' && q <= '9' || q == '@' || q == '.' || q == ' ' || q == ',' || q == '!' || q == '?')
		{
			cout << q;
			str += char(q);
		}
	}


	if ((str.length() - i) == 0 || (str.length() - i) >= 100)
	{
		system("cls");
		if ((str.length() - i) == 0)
			cout << "Incorrect message entry!" << endl;
		else
			cout << "Message is too big!" << endl;
		system("pause & cls");
		return true;
	}

	cout << "/";
	return false;
}

void check_str(char buf[])
{
	buf[0] = '\0';
	string command, address, message;
	while (true)
	{
		cout << "\nEnter -help for get information about commands\nPlease enter command" << endl;
		if (check_command(command))
			continue;
		if (command[0] == '-')
		{
			cout << "\n";
			if (command != "-help" && command != "-quit")
			{
				system("cls");
				cout << "Invalid command!" << endl;
				system(" pause & cls");
				continue;
			}
			strcat(buf, command.c_str());
			break;
		}
		else if (command != "readmsg" && command != "send")
		{
			system("cls");
			cout << "Invalid command!" << endl;
			system(" pause & cls");
			continue;
		}

		command += " <";
		if (check_address(address))
			continue;
		address += "> /";

		if ((command == "readmsg <"))
		{
			cout << (char)8 << " " << char(8) << endl;
			strcat(buf, command.c_str());
			strcat(buf, address.c_str());
			break;
		}

		if (check_message(message))
			continue;
		else
		{
			cout << "\n";
			message += "/";
			strcat(buf, command.c_str());
			strcat(buf, address.c_str());
			strcat(buf, message.c_str());
			break;
		}

	}


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
