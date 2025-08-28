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

bool cmp(Timetable, Timetable); //cmp函数声明，用于按发车时间升序排序
void SortbyTime(vector<Timetable>);
int find(vector<Timetable>, string);
bool StopService(vector<Timetable>, string);

void Signin() //(1)管理员用户登录函数
{
	
	string username_login = "admin";
	char password_login[] = "123";
	while (1)
	{
		string username;
		char password[64]; //用于存储输入的密码
		char ch; //逐字符录入
		int i = 0;

		system("cls");
		cout << "请输入用户名：";
		cin >> username;
		cout << "请输入密码：";
		while (1)
		{
			ch = _getch(); //无回显地读取一个字符
			if (ch == '\r') { //检测到回车键结束输入
				password[i] = '\0'; //添加字符串结束符
				break;
			}
			if (i < 63) { // 防止数组越界
				password[i++] = ch;
				putchar('*'); // 显示星号
			}
		}
		if (username == username_login && !strcmp(password, password_login))
			break;
	}
}
int ReadFromFile(vector<Timetable>& timetables, const string& filename) //(2)从文件filename中导入数据
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
int AddBus(vector<Timetable>& timetables) //(3)添加车次
{
	string typein;
	while (1)
	{
		cout << "请输入需要添加的车次号：";
		cin >> typein;
		if (find(timetables, typein) != -1)
			cout << "已存在该车次，请重新输入。" << endl;
		else break;
	}
	cout << "请依次输入发车时间(时)、发车时间(分)、始发站、终点站、行车时长、票价、最大载客量【各项之间使用空格分隔】：" << endl;
	string start, last;
	int h, m, f, maxn;
	float t;
	cin >> h >> m >> start >> last >> t >> f >> maxn;
	timetables.push_back(Timetable(typein, h, m, start, last, t, f, maxn, 0));
	cout << "导入成功。" << endl;
	return timetables.size();
}
int WritetoFile(vector<Timetable> timetables, const string& filename) //(4)将容器中所有元素写入文件
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
void ShowBusInfo(vector<Timetable> timetables, int idx) //(5)显示容器中下标为idx的元素信息
{
	cout << "-----------------------------------" << endl;
	if (idx < timetables.size())
		timetables[idx].show();
	else cerr << "错误：下标越界。" << endl;
}
void ShowTimetable(vector<Timetable> timetables) //(6)以发车时间升序排列显示所有车次信息
{
	sort(timetables.begin(), timetables.end(), cmp);
	int idx = 0;
	while (idx < timetables.size())
		ShowBusInfo(timetables, idx++);
}
void Query(vector<Timetable> timetables) //(7)按车次或终点站进行查询
{
	cout << "请输入车次或终点站进行查询：";
	string typein;
	cin >> typein;
	int idx, flag = 0;
	for (idx = 0; idx < timetables.size(); idx++)
	{
		if (timetables[idx].Last_station == typein)
		{
			flag = 1; //标记为输入终点站
			break;
		}
		else if (timetables[idx].no == typein)
		{
			ShowBusInfo(timetables, idx);
			flag = 2; //标记为输入车次
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
int find(vector<Timetable> timetables, string num) //(8)按车次进行查询，返回索引下标
{
	int index = distance(timetables.begin(), find_if(timetables.begin(), timetables.end(), [num](const Timetable& obj) {return (obj.no == num); }));
	if (index < timetables.size())
		return index;
	else return -1;
}
int find(vector<Timetable> timetables, string last_station, int* index) //(9)按终点站名进行查询
{
	int count = 0;
	for (int i = 0; i < timetables.size(); i++)
		if (timetables[i].GetLastStation() == last_station)
			index[count++] = i;
	if (count)
		return count;
	else return -1;
}
int DelBus(vector<Timetable>& timetables) //(10)注销车次
{
	cout << "请输入需要注销的车次号：";
	string num;
	cin >> num;
	auto i = find_if(timetables.begin(), timetables.end(), [num](const Timetable& obj) {return (obj.no == num); });
	if (i != timetables.end())
		timetables.erase(i);
	else cout << "此车次不存在。" << endl;
	return timetables.size();
}
void GenerateLogFileName(string& LogFileName) //(11)根据当天日期生成日志名
{
	auto now = chrono::system_clock::now();
	time_t now_c = chrono::system_clock::to_time_t(now); //调用系统时间
	stringstream ss;
	ss << put_time(localtime(&now_c), "%Y-%m-%d"); //格式化输出时间：yyyy-mm-dd
#if BIN
	LogFileName = ss.str() + ".log.bin";
#else
	LogFileName = ss.str() + ".log";
#endif	
}
bool InitializationPassagerMode(vector<Timetable>& timetables, string LogFilename, const string& filename) //(12)判断日志文件是否存在
{
	fstream read;
	read.open(LogFilename, ios::in);
	if (read.is_open())
	{
		ReadFromFile(timetables, LogFilename);
		cout << "日志文件导入成功。" << endl;
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
void TicketOrder(vector<Timetable>& timetables) //(13)购票
{
	cout << "请输入需要购买的车次：";
	string no;
	cin >> no;
	int i = find(timetables, no);
	while (1)
	{
		if (i == -1)
		{
			cout << "车次不存在，请重新输入。" << endl;
			cin >> no;
			i = find(timetables, no);
			continue;
		}
		else if (i >= 0)
		{
			ShowBusInfo(timetables, i);
			if (StopService(timetables, no))
				cout << "距发车时间少于10分钟，停止售票。" << endl;
			else if (timetables[i].TicketAvailable() == 0)
				cout << "该车次车票已售罄。" << endl;
			else
			{
				while (1)
				{
					cout << "请输入需要购买的票数：【输入-1退出购买】";
					int num;
					cin >> num;
					if (num == -1)
						break;
					else if (num > timetables[i].TicketAvailable())
					{
						cout << "购买票数大于可售票数，无法购买。" << endl;
						continue;
					}
					else if (num > 0)
					{
						timetables[i].SetSold(timetables[i].GetSold() + num);
						cout << "购买成功。" << endl;
						break;
					}
					else 
					{
						cout << "输入无效，请重新输入。" << endl;
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 丢弃缓冲区内容
						continue;
					}
				}
			}
		}
		break;
	}
}
void TicketDelete(vector<Timetable>& timetables) //(14)退票
{
	cout<< "请输入需要退票的车次：";
	string no;
	cin >> no;
	int i = find(timetables, no);
	while (1)
	{
		if (i == -1)
		{
			cout << "车次不存在，请重新输入。" << endl;
			continue;
		}
		else if (i >= 0)
		{
			ShowBusInfo(timetables, i);
			if (StopService(timetables, no))
				cout << "距发车时间少于10分钟，停止退票。" << endl;
			else if (timetables[i].GetSold() == 0)
				cout << "该车次车票尚未售出。" << endl;
			else
			{
				while (1)
				{
					cout << "请输入需要退票的票数：【输入-1退出退票】";
					int num;
					cin >> num;
					if (num == -1)
						break;
					else if (num > timetables[i].GetSold())
					{
						cout << "退票票数大于已售票数，无法退票。" << endl;
						continue;
					}
					else if (num > 0)
					{
						timetables[i].SetSold(timetables[i].GetSold() - num);
						cout << "退票成功。" << endl;
						break;
					}
					else 
					{
						cout << "输入无效，请重新输入。" << endl;
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 丢弃缓冲区内容
						continue;
					}
				}
			}
		}
		break;
	}
}
bool StopService(vector<Timetable> timetables, string no) //(15)判断是否停止售票/退票
{
	int i = find(timetables,no);

	auto now = chrono::system_clock::now();
	time_t now_c = std::chrono::system_clock::to_time_t(now); //调用系统时间
	tm* local_tm = localtime(&now_c);
	int now_hour = local_tm->tm_hour;
	int now_minute = local_tm->tm_min;
	if (((timetables[i].GetHour() - now_hour) * 60 + timetables[i].GetMinute() - now_minute) < 10)
		return true;
	else return false;
}
void SortbyTime(vector<Timetable> timetables) //(16)将容器中元素按发车时间进行升序排序
{
	sort(timetables.begin(), timetables.end(), cmp);
}
bool Quit()
{
	system("cls");
	cout << "是否要退出整个系统？(Y/N)" << endl;
	string typein;
	cin >> typein;
	if (typein == "Y" || typein == "y" || typein == "Yes" || typein == "YES")
		return true;
	else return false;
}


bool cmp(Timetable T1, Timetable T2) { return (T1.TimeCompare() < T2.TimeCompare()); }