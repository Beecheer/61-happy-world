#include <iostream>
#include <string>
using namespace std;

int MainWindowSelect()
{
	string menu[3] = { "1.管理员登录\n","2.普通顾客登录\n","3.退出\n" };
	int choice;
	while(1)
	{
		system("cls");
		for (int i = 0; i < 3; i++)
			cout << menu[i];
		cout << "请输入选择（1～3）：" << endl;
		cin >> choice;
		if (choice == 1 || choice == 2 || choice == 3)
			return choice;
	}
}
int AdminWindowSelect()
{
	string menu[5] = { "1.增加车次信息\n","2.查看所有车次信息\n","3.车辆信息查询\n","4.注销车次\n","5.退出\n" };
	int choice;
	while (1)
	{
		system("cls");
		for (int i = 0; i < 5; i++)
			cout << menu[i];
		cout << "请输入选择（1～5）：" << endl;
		cin >> choice;
		if (choice > 0 && choice < 6)
			return choice;
	}
}
int PassagerWindowSelect()
{
	string menu[4] = { "1.车辆信息查询\n","2.购买车票\n","3.退票\n","4.退出\n" };
	int choice;
	while (1)
	{
		system("cls");
		for (int i = 0; i < 4; i++)
			cout << menu[i];
		cout << "请输入选择（1～4）：" << endl;
		cin >> choice;
		if (choice > 0 && choice < 5)
			return choice;
	}
}