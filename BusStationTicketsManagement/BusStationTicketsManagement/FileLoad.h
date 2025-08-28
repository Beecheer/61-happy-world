#pragma once
#include <vector>
#include <string>
#include "BusInfo.h"
#include "Bin.h"

#if BIN
bool SaveToBinary(const vector<Timetable>&, const string&);
vector<Timetable> LoadFromBinary(const string&);
#else
bool SaveToFile(const vector<Timetable>&, const string&);
vector<Timetable> LoadFromFile(const string&);
#endif