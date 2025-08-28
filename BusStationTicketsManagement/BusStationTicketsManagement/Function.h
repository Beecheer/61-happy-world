#pragma once
#include <vector>
#include "BusInfo.h"
void Signin();
int ReadFromFile(vector<Timetable>&, const string&);
int AddBus(vector<Timetable>&);
int WritetoFile(vector<Timetable>, const string&);
void ShowBusInfo(vector<Timetable>, int);
void ShowTimetable(vector<Timetable>);
void GenerateLogFileName(string&);
void Query(vector<Timetable>);
int find(vector<Timetable>, string);
int find(vector<Timetable>, string, int*);
int DelBus(vector<Timetable>&);
void GenerateLogFilename(string);
bool InitializationPassagerMode(vector<Timetable>&, string, const string&);
void TicketOrder(vector<Timetable>&);
void TicketDelete(vector<Timetable>&);
bool StopService(vector<Timetable>, string);
void SortbyTime(vector<Timetable>);
bool Quit();
