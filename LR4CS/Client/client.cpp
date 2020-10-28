#include <sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<iostream>
#include <string>
#include <termios.h>
#include <unistd.h>





using namespace std;


const int MAX_EMPLOYEES = 5;



class Employee
{
private:
	char name[20], surname[20], patronymic[20];
	long number_empoyee;
	int hours_in_month;
	float tariff;
public:
	void display()
	{
		cout << "Employee: " << surname << " " << name << " " << patronymic << "\nNumber: " << number_empoyee << "\nHours per month: " << hours_in_month << "\nTariff: " << tariff << "($)\n" << endl;
	}
	
}employee[MAX_EMPLOYEES];


void view_employees(Employee[], int);
int check_number_menu();
int menu();
void task();
bool check_dot_in_str(string);
float check_number();
int check_number_menu();

int s;

int main()
{
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(1280);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	s = socket(AF_INET, SOCK_STREAM, 0);
	if ((connect(s, (struct sockaddr*)&addr, sizeof(addr))) < 0)
	{
		cerr << "Failed to connect to server!" << endl;
		exit(1);
	}
	cout << "Successful connection to the server!\n" << endl;

	while (true)
	{
		switch (menu())
		{
		case 1: task(); break;
		case 2: {int i = 2;  send(s, (char*)&i, sizeof(int), 0); view_employees(employee, MAX_EMPLOYEES);  break; }
		case 3: {int i = 3;  send(s, (char*)&i, sizeof(int), 0);  return 0; }
		default: cout << "Wrong choice!\n";  break;
		}
	}
}


int menu()
{
	int i;
	do
	{
		cout << "Menu:\n1. Complete task\n2. View epmloyer\n3. Exit" << endl;
	}while((i = check_number_menu())==-1);
	return i;
}

void task()
{
	int i = 1;
	float wages;
	send(s, (char*)&i, sizeof(int), 0);

	do
	{
		cout << "Plese enter wages($)" << endl;
	} while ((wages = check_number()) == -1);

	send(s, (char*)&wages, sizeof(float),0);

	if (recv(s, (char*)&i, sizeof(int),0) >= 0)
	{
		if (i == 0)
		{
			cout << "No workers with lower wages!" << endl;
			return;
		}
		view_employees(employee, i);
	}
	

}

void view_employees(Employee arr[],int count)
{
	for (int i = 0; i < count; i++)
	{
		if (recv(s, (char*)&employee[i], sizeof(Employee), 0) < 0)
		{
			cout << "Error connection!" << endl;
			exit(0);
		}
	}
	for (int i = 0; i < count; i++)
		arr[i].display();
}

int check_number_menu()
{
	string number;
	bool flag = false;
		getline(cin, number);


		if (number.length() == 0)
		{
			cout << "Invalid input\n" << endl;
			return -1;
		}

		for (int i = 0; i < number.length();i++)
		{
			if (!(number[i] >= '0' && number[i] <= '9'))
			{
				flag = true;
				break;
			}
		}

		if (flag)
		{
			cout << "Invalid input\n" << endl;
			return -1;
		}
		else
			return atoi(number.c_str());
}

float check_number()
{
	float i;
	string number;
	bool flag = false;
	int j = 0;

		getline(cin, number);

		if (number.length() == 0)
		{
			cout << "Invalid input\n" << endl;
			return -1;
		}


		for (int i = 0; i < number.length(); i++)
		{

			if (!(number[i] >= '0' && number[i] <= '9' || number[i]=='.'))
			{
				flag = true;
				break;
			}

			if (number[i] == '.')
				j++;


			if (j > 1)
			{
				flag = true;
				break;
			}

		}

		if (flag)
		{
			cout << "Invalid input\n" << endl;
			return -1;
		}
		else
			return atof(number.c_str());
	
}



