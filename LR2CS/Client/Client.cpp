

#include <iostream>
#include <winsock2.h>
#include <conio.h>
#pragma warning (disable : 4996)
#pragma comment (lib, "wsock32.lib")
using namespace std;


//int get_number(int);

int main()
{
	//setlocale(LC_ALL, "Russian");
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

	cout << "Enter number : ";
	cin >> number;
	//int = get_number(2);
	sendto(sClient, (char*)&number, sizeof(int), 0, (SOCKADDR*)&addr, sizeof(addr));

	/*cout << endl << "Enter month: ";
	month = get_number(2);
	sendto(sClient, (char*)&month, sizeof(month), 0, (SOCKADDR*)&addr, sizeof(addr));

	cout << endl << "Enter year : ";
	year = get_number(10);
	sendto(sClient, (char*)&year, sizeof(year), 0, (SOCKADDR*)&addr, sizeof(addr));*/

	int size = sizeof(addr);
	//bool check = 0;
	recvfrom(sClient, (char*)&number, sizeof(number), 0, (SOCKADDR*)&addr, &size);

	 cout <<number<< endl;
	//else cout << endl << "false";


}


//int get_number(int length)
//{
//	int index = 0;
//	char ch;
//	char str[20];
//	do
//	{
//		ch = _getch();
//		if (ch == '\r' && index == 0)
//		{
//			ch = 0;
//		}
//		else if (index == 0 && ((ch >= '1' && ch <= '9')) && ch != 8)
//		{
//			cout << ch;
//			str[index] = ch;
//			index++;
//		}
//		else if (index > 0)
//		{
//			if (ch == 8)
//			{
//				index--;
//				str[index] = '\0';
//				cout << "\b \b";
//			}
//			else if (index > length - 1)
//			{
//				;
//			}
//			else if (ch >= '0' && ch <= '9')
//			{
//				cout << ch;
//				str[index] = ch;
//				index++;
//			}
//		}
//	} while (ch != '\r');
//	str[index + 1] = '\0';
//	return atoi(str);
//}
//
//
