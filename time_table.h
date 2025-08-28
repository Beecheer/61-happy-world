//
// Created by zhangzhiwen on 25-8-27.
//

#ifndef TIME_TABLE_H
#define TIME_TABLE_H
#include <string>
#include <vector>

struct TimeTable
{
    std::string no;
    int hour;
    int minute;
    std::string Starting_station;
    std::string Last_station;
    float time;
    int fare;
    int max_number;
    int sold_number;
};

class TimeTablesClass
{
public:
    TimeTablesClass() = default;
    ~TimeTablesClass() = default;

    int AddTimeTable(const std::string &no_);
    int DeleteTimeTable(const std::string &no_);
    void SortByTime();
    void ShowInfo(const std::string &no_);
    void ShowTimeTables();
    void Query(const std::string &no_);
    void QueryByLastStation(const std::string& last_station_);

    void TicketOrder(const std::string &no_);
    void TicketDelete(const std::string &no_);
    bool StopService(const std::string& no_);
    int ReadFromFile(const std::string& filename);
    int WriteToFile(const std::string& filename);
    void GenerateLogFileName(char* LogFileName);
    int InitializationPassagerMode(const std::string& LogFileName, const std::string& filename);



private:
    std::vector<struct TimeTable> time_tables;
    int find(std::string no_);
    std::vector<int> findByLastStation(const std::string& last_station_);
};

extern TimeTablesClass TimeTables;


#endif //TIME_TABLE_H



