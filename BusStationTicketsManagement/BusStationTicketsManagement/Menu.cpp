#include <iostream>
#include <string>
using namespace std;

int MainWindowSelect()
{
	string menu[3] = { "1.����Ա��¼\n","2.��ͨ�˿͵�¼\n","3.�˳�\n" };
	int choice;
	while(1)
	{
		system("cls");
		for (int i = 0; i < 3; i++)
			cout << menu[i];
		cout << "������ѡ��1��3����" << endl;
		cin >> choice;
		if (choice == 1 || choice == 2 || choice == 3)
			return choice;
	}
}
int AdminWindowSelect()
{
	string menu[5] = { "1.���ӳ�����Ϣ\n","2.�鿴���г�����Ϣ\n","3.������Ϣ��ѯ\n","4.ע������\n","5.�˳�\n" };
	int choice;
	while (1)
	{
		system("cls");
		for (int i = 0; i < 5; i++)
			cout << menu[i];
		cout << "������ѡ��1��5����" << endl;
		cin >> choice;
		if (choice > 0 && choice < 6)
			return choice;
	}
}
int PassagerWindowSelect()
{
	string menu[4] = { "1.������Ϣ��ѯ\n","2.����Ʊ\n","3.��Ʊ\n","4.�˳�\n" };
	int choice;
	while (1)
	{
		system("cls");
		for (int i = 0; i < 4; i++)
			cout << menu[i];
		cout << "������ѡ��1��4����" << endl;
		cin >> choice;
		if (choice > 0 && choice < 5)
			return choice;
	}
}