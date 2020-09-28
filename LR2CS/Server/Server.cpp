

#include <iostream>
#include <winsock2.h>
#include <algorithm> 
#pragma warning (disable : 4996)
#pragma comment (lib, "wsock32.lib")
using namespace std;

//bool checkdate(int, int, int);
int pro_sort(int number);

int main()
{
	//setlocale(LC_ALL, "Russian");
	cout << "****** SERVER *******" << endl;
	WSADATA WSAData;
	WORD DLLVersion = MAKEWORD(2, 2);
	if (WSAStartup(DLLVersion, &WSAData) != 0)
	{
		cout << "Lib error" << endl;
		return 0;
	}

	SOCKET sListen = socket(AF_INET, SOCK_DGRAM, NULL);
	SOCKADDR_IN addr;
	addr.sin_port = htons(1280);
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = NULL;

	bind(sListen, (SOCKADDR*)&addr, sizeof(addr));

	int size = sizeof(addr);
	int number;
	recvfrom(sListen, (char*)&number, sizeof(number), 0, (SOCKADDR*)&addr, &size);
	//recvfrom(sListen, (char*)&month, sizeof(day), 0, (SOCKADDR*)&addr, &size);
	//recvfrom(sListen, (char*)&year, sizeof(day), 0, (SOCKADDR*)&addr, &size);


	/*cout << "День : " << day << endl;
	cout << "Месяц : " << month << endl;
	cout << "Год : " << year << endl;*/

	//bool check = checkdate(day, month, year);
	/*if (check) cout << "true";
	else cout << "false";*/
	number=pro_sort(number);
	sendto(sListen, (char*)&number, sizeof(number), 0, (SOCKADDR*)&addr, sizeof(addr));


}

int pro_sort(int number)
{
	int numbers[5];
	int result[5];

	for (int i = 0; i < 5; i++)
	{
		numbers[i] = number % 10;
		number /= 10;
	}
	number = 0;
	sort(numbers, numbers + 5);
	for (int i = 0,j=4; i < 5; i++,j--)
	{
		result[i]=numbers[j];
	
	}
	for (int i = 0,j=4; i < 5; i++,j--)
	{
		number += result[i] * pow(10, j);
	}
	return number;
	/*if (year > 0 && day > 0 && day < 32 && month > 0 && month < 13 && year > 0)
	{
		int leap = 0;
		if (year % 400 == 0)
			leap++;
		else if (year % 100 == 0)
			;
		else if (year % 4 == 0)
			leap++;

		if (((month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) && (day > 0 && day <= 31)) || ((month == 4 || month == 6 || month == 9 || month == 11) && (day > 0 && day <= 30)) || (leap == 1 && month == 2 && (day > 0 && day <= 29)) || (leap == 0 && month == 2 && (day > 0 && day <= 28)))
		{

			return true;
		}
	}
	return false;*/
}
