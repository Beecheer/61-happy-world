#pragma once
#include <vector>
#include "BusInfo.h"

void SortbyNo(vector<Timetable> timetables);
void ShowTimetable_no(vector<Timetable> timetables);
void SortbyLast(vector<Timetable> timetables);
void ShowTimetable_last(vector<Timetable> timetables);
int LogLoad(vector<Timetable>&);
void Statistics(const vector<Timetable>&, int);