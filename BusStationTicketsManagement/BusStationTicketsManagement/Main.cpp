#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include "BusInfo.h"
#include "Function.h"
#include "FileLoad.h"
#include "ExtraFunction.h"
#include "Bin.h"

using namespace std;

int MainWindowSelect();
int AdminWindowSelect();
int PassagerWindowSelect();
void AdminMode(vector<Timetable>&, const string&);
void PassagerMode(vector<Timetable>&, const string&);


int main()
{
	int UserChoice;
	vector<Timetable> timetables;
	while (1)
	{
		switch (UserChoice = MainWindowSelect())
		{
		case 1:AdminMode(timetables, FILENAME); continue;  //管理员模式
		case 2:PassagerMode(timetables, FILENAME); continue;  //顾客模式
		case 3:if (!Quit())continue; //退出
		}
		if (UserChoice == 3)break;
		return 0;
	}
	/*
	vector<Timetable> timetables;
	cout << "导入共" << ReadFromFile(timetables, "test.txt") << "条数据。" << endl;
	ShowTimetable(timetables);
	cout << AddBus(timetables);
	test.push_back({ "G101", 8, 30, "Beijing", "Shanghai", 4.5, 560, 1000, 600 });
	test.push_back({ "D202", 9, 15, "Nanjing", "Guangzhou", 8.0, 420, 800, 300 });
	saveToFile(test, "test.bin");
	vector<Timetable> test2 = LoadFromFile("test.txt");
	n = test2.size();
	cout << n << endl;
	test2.at(1).show();
	*/
}

void AdminMode(vector<Timetable>& timetables, const string& filename)
{
	Signin();
	int n = ReadFromFile(timetables, FILENAME);
	while (1)
	{
		int AdminChoice;
		switch (AdminChoice = AdminWindowSelect())
		{
		case 1:n = AddBus(timetables); cout << "成功添加车次，现有" << n << "个车次。" << endl; WritetoFile(timetables, filename); system("pause"); break; //增加车次信息，并及时写到文件中
		case 2:ShowTimetable(timetables); system("pause"); break; //浏览时刻表<发车时间>
		case 3:ShowTimetable_no(timetables); system("pause"); break; //浏览时刻表<车次>
		case 4:ShowTimetable_last(timetables); system("pause"); break; //浏览时刻表<终点站>
		case 5:Query(timetables); system("pause"); break; //车辆信息查询
		case 6:n = DelBus(timetables); system("pause"); WritetoFile(timetables, filename); break; //注销车次，并及时写到文件中
		case 7: { vector<Timetable> analysis; int days = LogLoad(analysis); Statistics(analysis, days); system("pause"); break; } //统计当月日志数据，展示车次、总收入、日均售票数、日均乘车人数
		case 8:WritetoFile(timetables, filename); return; //返回上级菜单，并将信息保存回 bus.txt 文件
		}
	}
}
void PassagerMode(vector<Timetable>& timetables, const string& filename)
{
	string LogFileName;
	GenerateLogFileName(LogFileName); //根据当前日期生成日志名
	InitializationPassagerMode(timetables, LogFileName, filename);
	int PassagerChoice;
	while (1)
	{
		switch (PassagerChoice = PassagerWindowSelect())
		{
		case 1:Query(timetables); system("pause"); break; //车辆信息查询
		case 2:TicketOrder(timetables); WritetoFile(timetables, LogFileName); system("pause"); break; //购买车票，并更改文件信息
		case 3:TicketDelete(timetables); WritetoFile(timetables, LogFileName); system("pause"); break; //退回车票，并更改文件信息
		case 4:WritetoFile(timetables, LogFileName); return; //返回上级菜单
		}
	}
}
