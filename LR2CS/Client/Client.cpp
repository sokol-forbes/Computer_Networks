

#include <iostream>
#include <winsock2.h>
#include <conio.h>
#pragma warning (disable : 4996)
#pragma comment (lib, "wsock32.lib")
using namespace std;


int check_number();

int main()
{
	
	cout << "****** CLIENT *******" << endl;
	WSADATA WSAData;
	WORD DLLVersion = MAKEWORD(2, 2);
	if (WSAStartup(DLLVersion, &WSAData) != 0)
	{
		cout << "Lib error" << endl;
		return 0;
	}

	SOCKET sClient = socket(AF_INET, SOCK_DGRAM, NULL);
	SOCKADDR_IN addr;
	addr.sin_port = htons(1280);
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");


	int number;
	do
	{
		cout << "Enter number : ";
	} while ((number = check_number()) == -1);
	
	
	sendto(sClient, (char*)&number, sizeof(int), 0, (SOCKADDR*)&addr, sizeof(addr));

	

	int size = sizeof(addr);
	
	recvfrom(sClient, (char*)&number, sizeof(number), 0, (SOCKADDR*)&addr, &size);
	cout << endl;

	 cout <<number<< endl;
	


}


int  check_number()
{
	char s;
	int j = 0, i = 0;
	while ((s = _getch()) != '\r')
	{
		if (s == 8)
		{
			if (i)
			{
				i--;
				cout << (char)8 << " " << char(8);
				j /= 10;
			}
		}
		else if (i >= 5)
		{
			system("cls");
			cout << "Number must consist of 5 mumbers\n" << endl;
		 system("pause & cls");
			return -1;
		}
		else if (s >= '0' && s <= '9')
		{
			cout << s;
			j = j * 10 + (s - '0');
			i++;
		}
	}

	if (s == '\r' && i)
		return j;
	else
	{
		system("cls");
		cout << "Input error!\n" << endl;
		system("pause & cls");
		return -1;
	}
}