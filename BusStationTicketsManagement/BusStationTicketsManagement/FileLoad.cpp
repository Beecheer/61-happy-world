#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include "BusInfo.h"
#include "Bin.h"
using namespace std;

#if BIN
// 保存 vector 到二进制文件
bool SaveToBinary(const vector<Timetable>& data, const string& filename) 
{
    ofstream ofs(filename, ios::binary);
    if (!ofs) {
        cerr << "无法打开文件写入: " << filename << endl;
        return false;
    }
    size_t n = data.size();
    ofs.write((char*)&n, sizeof(n)); // 先写入元素个数
    for (const auto& t : data) {
        t.writeBinary(ofs);
    }
    return true;
}

// 从二进制文件读取
vector<Timetable> LoadFromBinary(const string& filename) 
{
    vector<Timetable> result;
    ifstream ifs(filename, ios::binary);
    if (!ifs) {
        cerr << "无法打开文件读取: " << filename << endl;
        return result;
    }
    size_t n;
    ifs.read((char*)&n, sizeof(n));
    for (size_t i = 0; i < n; i++) {
        result.push_back(Timetable::readBinary(ifs));
    }
    return result;
}
#else
// 将 vector 写入文件
bool SaveToFile(const vector<Timetable>& data, const string& filename)
{
    ofstream ofs(filename);
    if (!ofs) 
    {
        cerr << "无法打开文件写入: " << filename << endl;
        return false;
    }
    for (const auto& t : data)
    {
        ofs << t.toString() << endl;
    }
    return true;
}

// 从文件读取到 vector
vector<Timetable> LoadFromFile(const string& filename)
{
    vector<Timetable> result;
    ifstream ifs(filename);
    if (!ifs) {
        cerr << "无法打开文件进行读取: " << filename << endl;
        return result;
    }
    string line;
    while (getline(ifs, line)) {
        if (!line.empty()) {
            result.push_back(Timetable::fromString(line));
        }
    }
    return result;
}
#endif

