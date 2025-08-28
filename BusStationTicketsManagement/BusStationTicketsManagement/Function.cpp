#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iterator>
#include <cstdlib>
#include <algorithm>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <conio.h>
#include "BusInfo.h"
#include "FileLoad.h"
#include "Bin.h"
using namespace std;

bool cmp(Timetable, Timetable); //cmp�������������ڰ�����ʱ����������
void SortbyTime(vector<Timetable>);
int find(vector<Timetable>, string);
bool StopService(vector<Timetable>, string);

void Signin() //(1)����Ա�û���¼����
{
	
	string username_login = "admin";
	char password_login[] = "123";
	while (1)
	{
		string username;
		char password[64]; //���ڴ洢���������
		char ch; //���ַ�¼��
		int i = 0;

		system("cls");
		cout << "�������û�����";
		cin >> username;
		cout << "���������룺";
		while (1)
		{
			ch = _getch(); //�޻��Եض�ȡһ���ַ�
			if (ch == '\r') { //��⵽�س�����������
				password[i] = '\0'; //����ַ���������
				break;
			}
			if (i < 63) { // ��ֹ����Խ��
				password[i++] = ch;
				putchar('*'); // ��ʾ�Ǻ�
			}
		}
		if (username == username_login && !strcmp(password, password_login))
			break;
	}
}
int ReadFromFile(vector<Timetable>& timetables, const string& filename) //(2)���ļ�filename�е�������
{
#if BIN
	if (LoadFromBinary(filename).empty())
		return -1;
	else
	{
		timetables = LoadFromBinary(filename);
		return timetables.size();
	}
#else
	if (LoadFromFile(filename).empty())
		return -1;
	else
	{
		timetables = LoadFromFile(filename);
		return timetables.size();
	}
#endif
}
int AddBus(vector<Timetable>& timetables) //(3)��ӳ���
{
	string typein;
	while (1)
	{
		cout << "��������Ҫ��ӵĳ��κţ�";
		cin >> typein;
		if (find(timetables, typein) != -1)
			cout << "�Ѵ��ڸó��Σ����������롣" << endl;
		else break;
	}
	cout << "���������뷢��ʱ��(ʱ)������ʱ��(��)��ʼ��վ���յ�վ���г�ʱ����Ʊ�ۡ�����ؿ���������֮��ʹ�ÿո�ָ�����" << endl;
	string start, last;
	int h, m, f, maxn;
	float t;
	cin >> h >> m >> start >> last >> t >> f >> maxn;
	timetables.push_back(Timetable(typein, h, m, start, last, t, f, maxn, 0));
	cout << "����ɹ���" << endl;
	return timetables.size();
}
int WritetoFile(vector<Timetable> timetables, const string& filename) //(4)������������Ԫ��д���ļ�
{
#if BIN
	if (SaveToBinary(timetables, filename))
		return timetables.size();
	else return -1;
#else
	if (SaveToFile(timetables, filename))
		return timetables.size();
	else return -1;
#endif
}
void ShowBusInfo(vector<Timetable> timetables, int idx) //(5)��ʾ�������±�Ϊidx��Ԫ����Ϣ
{
	cout << "-----------------------------------" << endl;
	if (idx < timetables.size())
		timetables[idx].show();
	else cerr << "�����±�Խ�硣" << endl;
}
void ShowTimetable(vector<Timetable> timetables) //(6)�Է���ʱ������������ʾ���г�����Ϣ
{
	sort(timetables.begin(), timetables.end(), cmp);
	int idx = 0;
	while (idx < timetables.size())
		ShowBusInfo(timetables, idx++);
}
void Query(vector<Timetable> timetables) //(7)�����λ��յ�վ���в�ѯ
{
	cout << "�����복�λ��յ�վ���в�ѯ��";
	string typein;
	cin >> typein;
	int idx, flag = 0;
	for (idx = 0; idx < timetables.size(); idx++)
	{
		if (timetables[idx].Last_station == typein)
		{
			flag = 1; //���Ϊ�����յ�վ
			break;
		}
		else if (timetables[idx].no == typein)
		{
			ShowBusInfo(timetables, idx);
			flag = 2; //���Ϊ���복��
			break;
		}
	}
	if (flag == 1)
	{
		SortbyTime(timetables);
		for (idx = 0; idx < timetables.size(); idx++)
		{
			if (timetables[idx].Last_station == typein)
				ShowBusInfo(timetables, idx);
		}
	}
}
int find(vector<Timetable> timetables, string num) //(8)�����ν��в�ѯ�����������±�
{
	int index = distance(timetables.begin(), find_if(timetables.begin(), timetables.end(), [num](const Timetable& obj) {return (obj.no == num); }));
	if (index < timetables.size())
		return index;
	else return -1;
}
int find(vector<Timetable> timetables, string last_station, int* index) //(9)���յ�վ�����в�ѯ
{
	int count = 0;
	for (int i = 0; i < timetables.size(); i++)
		if (timetables[i].GetLastStation() == last_station)
			index[count++] = i;
	if (count)
		return count;
	else return -1;
}
int DelBus(vector<Timetable>& timetables) //(10)ע������
{
	cout << "��������Ҫע���ĳ��κţ�";
	string num;
	cin >> num;
	auto i = find_if(timetables.begin(), timetables.end(), [num](const Timetable& obj) {return (obj.no == num); });
	if (i != timetables.end())
		timetables.erase(i);
	else cout << "�˳��β����ڡ�" << endl;
	return timetables.size();
}
void GenerateLogFileName(string& LogFileName) //(11)���ݵ�������������־��
{
	auto now = chrono::system_clock::now();
	time_t now_c = chrono::system_clock::to_time_t(now); //����ϵͳʱ��
	stringstream ss;
	ss << put_time(localtime(&now_c), "%Y-%m-%d"); //��ʽ�����ʱ�䣺yyyy-mm-dd
#if BIN
	LogFileName = ss.str() + ".log.bin";
#else
	LogFileName = ss.str() + ".log";
#endif	
}
bool InitializationPassagerMode(vector<Timetable>& timetables, string LogFilename, const string& filename) //(12)�ж���־�ļ��Ƿ����
{
	fstream read;
	read.open(LogFilename, ios::in);
	if (read.is_open())
	{
		ReadFromFile(timetables, LogFilename);
		cout << "��־�ļ�����ɹ���" << endl;
		return true;
	}
	else
	{
		ReadFromFile(timetables, filename);
		int i = 0;
		while (i < timetables.size())
			timetables[i++].SetSold(0);
		return false;
	}
}
void TicketOrder(vector<Timetable>& timetables) //(13)��Ʊ
{
	cout << "��������Ҫ����ĳ��Σ�";
	string no;
	cin >> no;
	int i = find(timetables, no);
	while (1)
	{
		if (i == -1)
		{
			cout << "���β����ڣ����������롣" << endl;
			cin >> no;
			i = find(timetables, no);
			continue;
		}
		else if (i >= 0)
		{
			ShowBusInfo(timetables, i);
			if (StopService(timetables, no))
				cout << "�෢��ʱ������10���ӣ�ֹͣ��Ʊ��" << endl;
			else if (timetables[i].TicketAvailable() == 0)
				cout << "�ó��γ�Ʊ��������" << endl;
			else
			{
				while (1)
				{
					cout << "��������Ҫ�����Ʊ����������-1�˳�����";
					int num;
					cin >> num;
					if (num == -1)
						break;
					else if (num > timetables[i].TicketAvailable())
					{
						cout << "����Ʊ�����ڿ���Ʊ�����޷�����" << endl;
						continue;
					}
					else if (num > 0)
					{
						timetables[i].SetSold(timetables[i].GetSold() + num);
						cout << "����ɹ���" << endl;
						break;
					}
					else 
					{
						cout << "������Ч�����������롣" << endl;
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ��������������
						continue;
					}
				}
			}
		}
		break;
	}
}
void TicketDelete(vector<Timetable>& timetables) //(14)��Ʊ
{
	cout<< "��������Ҫ��Ʊ�ĳ��Σ�";
	string no;
	cin >> no;
	int i = find(timetables, no);
	while (1)
	{
		if (i == -1)
		{
			cout << "���β����ڣ����������롣" << endl;
			continue;
		}
		else if (i >= 0)
		{
			ShowBusInfo(timetables, i);
			if (StopService(timetables, no))
				cout << "�෢��ʱ������10���ӣ�ֹͣ��Ʊ��" << endl;
			else if (timetables[i].GetSold() == 0)
				cout << "�ó��γ�Ʊ��δ�۳���" << endl;
			else
			{
				while (1)
				{
					cout << "��������Ҫ��Ʊ��Ʊ����������-1�˳���Ʊ��";
					int num;
					cin >> num;
					if (num == -1)
						break;
					else if (num > timetables[i].GetSold())
					{
						cout << "��ƱƱ����������Ʊ�����޷���Ʊ��" << endl;
						continue;
					}
					else if (num > 0)
					{
						timetables[i].SetSold(timetables[i].GetSold() - num);
						cout << "��Ʊ�ɹ���" << endl;
						break;
					}
					else 
					{
						cout << "������Ч�����������롣" << endl;
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ��������������
						continue;
					}
				}
			}
		}
		break;
	}
}
bool StopService(vector<Timetable> timetables, string no) //(15)�ж��Ƿ�ֹͣ��Ʊ/��Ʊ
{
	int i = find(timetables,no);

	auto now = chrono::system_clock::now();
	time_t now_c = std::chrono::system_clock::to_time_t(now); //����ϵͳʱ��
	tm* local_tm = localtime(&now_c);
	int now_hour = local_tm->tm_hour;
	int now_minute = local_tm->tm_min;
	if (((timetables[i].GetHour() - now_hour) * 60 + timetables[i].GetMinute() - now_minute) < 10)
		return true;
	else return false;
}
void SortbyTime(vector<Timetable> timetables) //(16)��������Ԫ�ذ�����ʱ�������������
{
	sort(timetables.begin(), timetables.end(), cmp);
}
bool Quit()
{
	system("cls");
	cout << "�Ƿ�Ҫ�˳�����ϵͳ��(Y/N)" << endl;
	string typein;
	cin >> typein;
	if (typein == "Y" || typein == "y" || typein == "Yes" || typein == "YES")
		return true;
	else return false;
}


bool cmp(Timetable T1, Timetable T2) { return (T1.TimeCompare() < T2.TimeCompare()); }