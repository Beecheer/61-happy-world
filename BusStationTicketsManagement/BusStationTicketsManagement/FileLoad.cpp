#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include "BusInfo.h"
#include "Bin.h"
using namespace std;

#if BIN
// ���� vector ���������ļ�
bool SaveToBinary(const vector<Timetable>& data, const string& filename) 
{
    ofstream ofs(filename, ios::binary);
    if (!ofs) {
        cerr << "�޷����ļ�д��: " << filename << endl;
        return false;
    }
    size_t n = data.size();
    ofs.write((char*)&n, sizeof(n)); // ��д��Ԫ�ظ���
    for (const auto& t : data) {
        t.writeBinary(ofs);
    }
    return true;
}

// �Ӷ������ļ���ȡ
vector<Timetable> LoadFromBinary(const string& filename) 
{
    vector<Timetable> result;
    ifstream ifs(filename, ios::binary);
    if (!ifs) {
        cerr << "�޷����ļ���ȡ: " << filename << endl;
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
// �� vector д���ļ�
bool SaveToFile(const vector<Timetable>& data, const string& filename)
{
    ofstream ofs(filename);
    if (!ofs) 
    {
        cerr << "�޷����ļ�д��: " << filename << endl;
        return false;
    }
    for (const auto& t : data) 
    {
        ofs << t.toString() << endl;
    }
    return true;
}

// ���ļ���ȡ�� vector
vector<Timetable> LoadFromFile(const string& filename)
{
    vector<Timetable> result;
    ifstream ifs(filename);
    if (!ifs) {
        cerr << "�޷����ļ����ж�ȡ: " << filename << endl;
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

