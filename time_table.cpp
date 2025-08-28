//
// Created by zhangzhiwen on 25-8-27.
//

#include "time_table.h"

#include <algorithm>
#include <iostream>
#include <fstream>

int TimeTablesClass::find(std::string no_)
{
    for (size_t i = 0; i < time_tables.size(); ++i)
    {
        if (time_tables[i].no == no_)
            return i;
    }
    return -1;
}

std::vector<int> TimeTablesClass::findByLastStation(const std::string& last_station_)
{
    std::vector<int> indices;
    for (size_t i = 0; i < time_tables.size(); ++i)
    {
        if (time_tables[i].Last_station == last_station_)
            indices.push_back(i);
    }
    return indices;
}

int TimeTablesClass::AddTimeTable(const std::string& no_)
{
    if (find(no_) != -1)
    {
        std::cout << "车次已存在！" << std::endl;
        return -1;
    }

    TimeTable new_table;
    new_table.no = no_;
    std::cout << "请输入发车时间（小时 分钟）: ";
    std::cin >> new_table.hour >> new_table.minute;
    std::cout << "请输入始发站: ";
    std::cin >> new_table.Starting_station;
    std::cout << "请输入终点站: ";
    std::cin >> new_table.Last_station;
    std::cout << "请输入行车时长: ";
    std::cin >> new_table.time;
    std::cout << "请输入票价: ";
    std::cin >> new_table.fare;
    std::cout << "请输入最大载客量: ";
    std::cin >> new_table.max_number;
    new_table.sold_number = 0;

    time_tables.push_back(new_table);
    SortByTime();
    return time_tables.size();
}

int TimeTablesClass::DeleteTimeTable(const std::string& no_)
{
    int index = find(no_);
    if (index == -1)
    {
        std::cout << "车次不存在！" << std::endl;
        return -1;
    }

    char confirm;
    std::cout << "确定要注销车次 " << no_ << " 吗？(y/n): ";
    std::cin >> confirm;
    if (confirm == 'y' || confirm == 'Y')
    {
        time_tables.erase(time_tables.begin() + index);
        std::cout << "车次已注销。" << std::endl;
    }
    else
    {
        std::cout << "操作已取消。" << std::endl;
    }
    return time_tables.size();
}

void TimeTablesClass::SortByTime()
{
    std::sort(time_tables.begin(), time_tables.end(), [](const TimeTable& a, const TimeTable& b)
    {
        return a.hour * 60 + a.minute < b.hour * 60 + b.minute;
    });
}

void TimeTablesClass::ShowInfo(const std::string& no_)
{
    int index = find(no_);
    if (index == -1)
    {
        std::cout << "车次不存在！" << std::endl;
        return;
    }

    TimeTable& table = time_tables[index];
    std::cout << "车次: " << table.no << std::endl;
    std::cout << "发车时间: " << table.hour << ":" << table.minute << std::endl;
    std::cout << "始发站: " << table.Starting_station << std::endl;
    std::cout << "终点站: " << table.Last_station << std::endl;
    std::cout << "行车时长: " << table.time << std::endl;
    std::cout << "票价: " << table.fare << std::endl;
    std::cout << "最大载客量: " << table.max_number << std::endl;
    std::cout << "已售票数: " << table.sold_number << std::endl;
}

void TimeTablesClass::ShowTimeTables()
{
    SortByTime();
    for (const auto& table : time_tables)
    {
        std::cout << "车次: " << table.no << " 发车时间: " << table.hour << ":" << table.minute
                  << " 始发站: " << table.Starting_station << " 终点站: " << table.Last_station
                  << " 已售票数: " << table.sold_number << "/" << table.max_number << std::endl;
    }
}

void TimeTablesClass::Query(const std::string& no_)
{
    int index = find(no_);
    if (index == -1)
    {
        std::cout << "车次不存在！" << std::endl;
        return;
    }
    ShowInfo(no_);
}

void TimeTablesClass::QueryByLastStation(const std::string& last_station_)
{
    SortByTime();
    std::vector<int> indices = findByLastStation(last_station_);
    if (indices.empty())
    {
        std::cout << "没有找到终点站为 " << last_station_ << " 的车次！" << std::endl;
        return;
    }

    std::cout << "找到以下车次：" << std::endl;
    for (int index : indices)
    {
        TimeTable& table = time_tables[index];
        std::cout << "车次: " << table.no << " 发车时间: " << table.hour << ":" << table.minute
                  << " 始发站: " << table.Starting_station << " 终点站: " << table.Last_station
                  << " 已售票数: " << table.sold_number << "/" << table.max_number << std::endl;
    }
}

void TimeTablesClass::TicketOrder(const std::string& no_)
{
    int index = find(no_);
    if (index == -1)
    {
        std::cout << "车次不存在！" << std::endl;
        return;
    }

    TimeTable& table = time_tables[index];
    if (StopService(no_))
    {
        std::cout << "离发车时间不足10分钟，无法购票！" << std::endl;
        return;
    }

    if (table.sold_number >= table.max_number)
    {
        std::cout << "车票已售罄！" << std::endl;
        return;
    }

    int num;
    std::cout << "请输入要购买的车票数目: ";
    std::cin >> num;

    if (num <= 0)
    {
        std::cout << "输入错误！" << std::endl;
        return;
    }

    if (table.sold_number + num > table.max_number)
    {
        std::cout << "剩余车票不足！" << std::endl;
        return;
    }

    table.sold_number += num;
    std::cout << "购票成功！" << std::endl;
}

void TimeTablesClass::TicketDelete(const std::string& no_)
{
    int index = find(no_);
    if (index == -1)
    {
        std::cout << "车次不存在！" << std::endl;
        return;
    }

    TimeTable& table = time_tables[index];
    if (StopService(no_))
    {
        std::cout << "离发车时间不足10分钟，无法退票！" << std::endl;
        return;
    }

    if (table.sold_number <= 0)
    {
        std::cout << "该车次没有售出车票！" << std::endl;
        return;
    }

    int num;
    std::cout << "请输入要退的车票数目: ";
    std::cin >> num;

    if (num <= 0)
    {
        std::cout << "输入错误！" << std::endl;
        return;
    }

    if (table.sold_number < num)
    {
        std::cout << "退票数目超过已售出车票数目！" << std::endl;
        return;
    }

    table.sold_number -= num;
    std::cout << "退票成功！" << std::endl;
}

bool TimeTablesClass::StopService(const std::string& no_)
{
    int index = find(no_);
    if (index == -1)
        return true;

    time_t t = time(NULL);
    struct tm* local = localtime(&t);
    int current_time = local->tm_hour * 60 + local->tm_min;
    int departure_time = time_tables[index].hour * 60 + time_tables[index].minute;

    return (current_time + 10 >= departure_time);
}

int TimeTablesClass::ReadFromFile(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cout << "无法打开文件 " << filename << std::endl;
        return -1;
    }

    time_tables.clear();
    TimeTable table;
    while (file >> table.no >> table.hour >> table.minute >> table.Starting_station
               >> table.Last_station >> table.time >> table.fare >> table.max_number >> table.sold_number)
    {
        time_tables.push_back(table);
    }
    file.close();
    ShowTimeTables();
    return time_tables.size();
}

int TimeTablesClass::WriteToFile(const std::string& filename)
{
    std::ofstream file(filename);
    if (!file.is_open())
    {
        std::cout << "无法打开文件 " << filename << std::endl;
        return -1;
    }

    for (const auto& table : time_tables)
    {
        file << table.no << " " << table.hour << " " << table.minute << " " << table.Starting_station << " "
             << table.Last_station << " " << table.time << " " << table.fare << " " << table.max_number << " " << table.sold_number << std::endl;
    }
    file.close();
    return time_tables.size();
}

void TimeTablesClass::GenerateLogFileName(char* LogFileName)
{
    time_t t = time(NULL);
    struct tm* local = localtime(&t);
    sprintf(LogFileName, "%04d-%02d-%02d.log", local->tm_year + 1900, local->tm_mon + 1, local->tm_mday);
}

int TimeTablesClass::InitializationPassagerMode(const std::string& LogFileName, const std::string& filename)
{
    std::ifstream log_file(LogFileName);
    if (log_file.is_open())
    {
        log_file.close();
        return ReadFromFile(LogFileName);
    }
    else
    {
        int count = ReadFromFile(filename);
        for (auto& table : time_tables)
        {
            table.sold_number = 0;
        }
        WriteToFile(LogFileName);
        return count;
    }
}


TimeTablesClass TimeTables;

















