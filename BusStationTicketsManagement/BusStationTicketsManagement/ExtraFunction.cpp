#pragma	once
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include "BusInfo.h"
#include "Function.h"

#include <iomanip>
using namespace std;

void ShowBusInfo(vector<Timetable>, int);

bool cmp_no(Timetable T1, Timetable T2) { return (T1.no < T2.no); }
void SortbyNo(vector<Timetable> timetables) //(Ex-1)将容器中元素按车次进行升序排序
{
	sort(timetables.begin(), timetables.end(), cmp_no);
}
void ShowTimetable_no(vector<Timetable> timetables) //(Ex-2)以车次升序排列显示所有车次信息
{
	SortbyNo(timetables);
	int idx = 0;
	while (idx < timetables.size())
		ShowBusInfo(timetables, idx++);
}

bool cmp_last(Timetable T1, Timetable T2) { return (T1.GetLastStation() < T2.GetLastStation()); }
void SortbyLast(vector<Timetable> timetables) //(Ex-3)将容器中元素按终点站进行升序排序
{
	sort(timetables.begin(), timetables.end(), cmp_last);
}
void ShowTimetable_last(vector<Timetable> timetables) //(Ex-4)以终点站升序排列显示所有车次信息
{
	sort(timetables.begin(), timetables.end(), cmp_last);
	int idx = 0;
	while (idx < timetables.size())
		ShowBusInfo(timetables, idx++);
}

int LogLoad(vector<Timetable>& analysis) //(Ex-5)将所有日志文件全部导入新vector容器，返回导入的日志文件数量
{   
    while (1)
    {
	system("cls");
	cout << "请分别输入需要统计的年份、月份：【使用空格分隔】";
    int year, month, count = 0;
	cin >> year >> month;
    if (year > 2000 && month > 0 && month < 13)
    {
        for (int day = 1; day <= 31; day++)
        {
            string LogFilename = to_string(year) + (month < 10 ? "-0" : "-") + to_string(month) + (day < 10 ? "-0" : "-") + to_string(day) +
#if BIN
                ".log.bin";
#else
                ".log";
#endif
            fstream read;
            read.open(LogFilename, ios::in);
            if (read.is_open())
            {
                ReadFromFile(analysis, LogFilename);
                count++;
                continue;
            }
            else continue;
        }
        return count;
    }
    else
    {
        cout << "输入无效，请重新输入。" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); //丢弃缓冲区内容
        continue;
    }
    return 0;
    }
}
void Statistics(const vector<Timetable>& analysis, int days) 
{
    if (days == 0) 
    {
        cout << "无任何有效日志文件，无法统计。" << endl;
        return;
    }

    struct Stats 
    {
        long long totalSold = 0;
        long long totalIncome = 0;
    };

    map<string, Stats> statMap;

    for (const auto& t : analysis)
    {
        statMap[t.no].totalSold += t.GetSold();
        statMap[t.no].totalIncome += 1LL * t.GetSold() * t.GetFare(); //1LL可防止表达式相乘结果(int)超出int最大值，将表达式按long long类型计算
    }

    for (const auto& p : statMap) {
        const string& no = p.first;
        const Stats& s = p.second;
        double avgSold = (double)s.totalSold / days;
        double avgIncome = (double)s.totalIncome / days;
        cout << "车次：" << no << "\n总售票数：" << s.totalSold << "\n总收入：" << s.totalIncome << "\n日均售票数："
            << setprecision(2) << avgSold << "\n日均收入：" << setprecision(2) << avgIncome << endl;
    }
}