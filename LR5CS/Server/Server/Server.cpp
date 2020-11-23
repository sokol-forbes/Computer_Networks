// Server.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#define _CRT_SECURE_NO_WARNINGS
#include <WinSock2.h>
#include <iostream>
#pragma comment(lib,"ws2_32.lib")
#include <process.h>
#include <fstream>
#include<string>


using namespace std;

void delete_msg_in_file(string);
bool send_msg(char*, char*);
bool read_msg(char*, char[]);
void mail_workinng(void*);


int main()
{
	WORD wVersion = MAKEWORD(2, 2);
	WSADATA wsaData;

	if (WSAStartup(wVersion, &wsaData) != 0)
	{
		cerr << "Error server! #" << WSAGetLastError() << endl;
		exit(1);
	}

	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(1280);
	addr.sin_addr.s_addr = 0;

	SOCKET s = socket(AF_INET, SOCK_STREAM, 0);
	if (bind(s, (SOCKADDR*)&addr, sizeof(addr)) == SOCKET_ERROR)
	{
		cerr << "Can't bind socket" << endl;
		exit(1);
	}

	listen(s, 5);

	cout << "Server created!" << endl;
	int size = sizeof(addr);

	SOCKET connection;
	while (true)
	{
		if ((connection = accept(s, (SOCKADDR*)&addr, &size)) == 0)
		{
			cerr << "Error connection! #" << WSAGetLastError() << endl;
			exit(1);
		}
		cout << "Client connected!" << endl;
		_beginthread(mail_workinng, 0, (void*)connection);
	}
}


void delete_msg_in_file(string file_name)
{
	ifstream file;
	file.open(file_name + ".txt");
	if (!file)
		return;

	string str, buf;

	while (getline(file, str))
	{
		str += "\n";
		buf += str;
	}

	bool flag = false;
	string buf2;

	while (buf.length() > 1000)
	{
		buf.erase(0, buf.find_first_of("\n"));
		buf2 = buf.substr(1, buf.length());
		buf = buf2;
		flag = true;
	}

	file.close();

	if (flag)
	{
		ofstream file1;
		file1.open(file_name + ".txt", ios::trunc);
		if (!file1)
			return;
		file1 << buf;
		file1.close();
	}
}

bool send_msg(char* addres, char* message)
{
	string file_name = addres;
	ofstream file;
	file.open(file_name + ".txt", ios::app);
	if (!file)
		return true;

	file << message << "\n";
	file.close();
	delete_msg_in_file(file_name);
	return false;
}

bool read_msg(char* addres, char buf[])
{
	string file_name = addres;
	ifstream file;
	file.open(file_name + ".txt");
	if (!file)
		return true;

	string str;
	buf[0] = '\0';
	strcat(buf, "Mail:\n");
	while (getline(file, str))
	{
		str += "\n";
		strcat(buf, str.c_str());
	}

	file.close();

	return false;
}

void mail_workinng(void* s)
{
	char buf[1150];
	send((SOCKET)s, "MAIL center connected...\n", 26, 0);

	while (recv((SOCKET)s, buf, sizeof(buf), 0) >= 0)
	{
		if (buf[0] == '-')
		{
			if (!strcmp(buf, "-help"))
			{
				cout << "Client: -help" << endl;
				send((SOCKET)s, "\nCommands:\nsend <addres> /message/ - to send a message to the address\nreadmsg <addres> - to read the message by address\n-quit - exit\n", 135, 0);
			}
			else if (!strcmp(buf, "-quit"))
			{
				cout << "Client: -quit" << endl;
				cout << "Client deleted!" << endl;
				closesocket((SOCKET)s);
				_endthread();
			}
			continue;
		}

		cout << "Client: " << buf << endl;
		char command[15];
		char* str = strtok(buf, " <>");
		strcpy_s(command, str);

		char address[22];
		str = strtok(NULL, " /<>");
		strcpy_s(address, str);


		if (!strcmp(command, "send"))
		{
			str = strtok(NULL, "/");

			char message[150];
			str = strtok(NULL, "/");
			strcpy_s(message, str);

			if (send_msg(address, message))
				send((SOCKET)s, "Failed to send a message to the address!\n", 43, 0);
			else
				send((SOCKET)s, "Message sent!\n", 15, 0);
		}
		else if (!strcmp(command, "readmsg"))
		{

			if (read_msg(address, buf))
				send((SOCKET)s, "Could not read the message by address!\n", 40, 0);
			else
				send((SOCKET)s, buf, sizeof(buf), 0);
		}
		else
			send((SOCKET)s, "Invalid command!\n", 18, 0);
	}
	cout << "Client deleted!" << endl;
}