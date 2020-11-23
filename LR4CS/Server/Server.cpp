#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include<sys/socket.h>
#include<sys/signal.h>
#include<sys/wait.h>
#include<sys/resource.h>
#include<netinet/in.h>
#include <sys/un.h>


using namespace std;

const int MAX_EMPLOYEE = 5;

class Employee
{
	char name[20], surname[20], patronymic[20];
	long number_employee;
	int hours_in_month;
	float tariff;
public:

	Employee(string name, string surname, string patronymic, long number_employee, int hours_in_month, float tariff)
	{
		strcpy(this->name, name.c_str());
		strcpy(this->surname, surname.c_str());
		strcpy(this->patronymic, patronymic.c_str());
		this->number_employee = number_employee;
		this->hours_in_month = hours_in_month;
		this->tariff = tariff;
	}

	Employee() {}

	float get_wages()
	{
		return tariff * (float)hours_in_month;
	}

} employee[5];


void add_list_employees();
void task();
void view();
int get_count_employees(Employee[],float);
void reaper(int);
int Func();



int connection;

int main()
{
	add_list_employees();
	
	struct sockaddr_in  addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(1280);
	addr.sin_addr.s_addr = 0;

	int s = socket(AF_INET, SOCK_STREAM, 0);

	bind(s, (sockaddr*)&addr, sizeof(addr));
	listen(s, 5);
	cout << "Server complete!" << endl;

	int size = sizeof(addr);


	(void)signal(SIGCHLD, reaper);
	while (true)
	{
		if ((connection = accept(s, NULL, NULL)) < 0)
		{
			cerr << "Error connection!" << endl;
			exit(1);
		}
		cout << "Client connected!" << endl;

		switch (fork()) {
		case 0:
			(void)close(s);
			exit(Func());
		default:
			(void)close(connection);
		}
	}

}

void add_list_employees()
{
	employee[0] = Employee("Vadim","Loput","Alexandrovich", 1569872, 120, 100);
	employee[1] = Employee("Maksim", "Belogriwiy", "Urievich", 1975238, 150, 60);
	employee[2] = Employee("Denia", "Miseiko", "Alexandroviz", 1438954,15, 120);
	employee[3] = Employee("Vlad", "Karpovich", "Vitalievich", 24687135, 130, 90);
	employee[4] = Employee("Anton", "Vinokurov", "Artemovich", 7521368, 160, 150);
}

void task()
{
	float wages;
	if (recv(connection, (char*)&wages, sizeof(float), 0) >= 0)
	{
		int i = get_count_employees(employee, wages);
		send(connection, (char*)&i, sizeof(i), 0);
		for (int j = 0; j < 5; j++)
		{
			if (employee[j].get_wages() < wages)
				send(connection, (char*)&employee[j], sizeof(Employee), 0);
		}
	}
}

void view()
{
	for (int i = 0; i < 5; i++)
		send(connection, (char*)&employee[i], sizeof(Employee), 0);
}

int get_count_employees(Employee arr[],float wages)
{
	int i=0;
	for (int j = 0; j < 5; j++)
	{
		if (arr[j].get_wages() < wages)
			i++;
	}
	return i;
}

void reaper(int sig) {
	int status;
	while (wait3(&status, WNOHANG, (struct rusage*)0) >= 0);
}

int Func()
{
	int i;
	while (recv(connection, (char*)&i, sizeof(int), 0) >= 0)
	{
		switch (i)
		{
		case 1: cout << "Choose: task " << endl;  task(); break;
		case 2: cout << "Choose: view employees " << endl; view(); break;
		case 3: cout << "Client deleted!" << endl; exit(0); break;
		default: system("cls"); cerr << "Data transmission error!" << endl; return 1;
		}
	}
	if(i!=3)
	cout << "Client deleted!" << endl;
}
