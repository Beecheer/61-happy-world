#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include "Bin.h"
using namespace std;

class Timetable
{
private:
	int hour;
	int minute;
	string Starting_station;
	string Last_station;
	float time;
	int fare;
	int max_number;
	int sold_number;

#if BIN
	// ���ߺ�����д�ַ�������д���ȣ���д���ݣ�
	static void writeString(ofstream& ofs, const string& s) {
		size_t len = s.size();
		ofs.write((char*)&len, sizeof(len));
		ofs.write(s.c_str(), len);
	}

	// ���ߺ��������ַ���
	static string readString(ifstream& ifs) {
		size_t len;
		ifs.read((char*)&len, sizeof(len));
		string s(len, '\0');
		ifs.read(&s[0], len);
		return s;
	}
#endif

public:
	string no;
	Timetable(string num = "", int h = -1, int min = -1, string ss = "", string ls = "", float t = -1.0, int f = -1, int maxn = -1, int sold = -1) : \
		no(num),hour(h), minute(min), Starting_station(ss), Last_station(ls), time(t), fare(f), max_number(maxn), sold_number(sold) {}
	void show()
	{
		cout << "���Σ�" << no << "\n����ʱ�䣺" << (hour < 10 ? "0" : "") << hour << ":" << (minute < 10 ? "0" : "") << minute \
			<< "\n���վ��" << Starting_station << "\n�յ�վ��" << Last_station << "\n�г�ʱ�䣺" << time \
			<< "\nƱ�ۣ�" << fare << "\n�������" << max_number << "\n����Ʊ����" << sold_number << endl;
	}

#if BIN
	// д�뵽�������ļ�
	void writeBinary(ofstream& ofs) const {
		writeString(ofs, no);
		ofs.write((char*)&hour, sizeof(hour));
		ofs.write((char*)&minute, sizeof(minute));
		writeString(ofs, Starting_station);
		writeString(ofs, Last_station);
		ofs.write((char*)&time, sizeof(time));
		ofs.write((char*)&fare, sizeof(fare));
		ofs.write((char*)&max_number, sizeof(max_number));
		ofs.write((char*)&sold_number, sizeof(sold_number));
	}

	// �Ӷ������ļ���ȡ
	static Timetable readBinary(ifstream& ifs) {
		string no = readString(ifs);
		int hour, minute, fare, maxn, sold;
		float t;
		string start = readString(ifs);
		string last = readString(ifs);
		ifs.read((char*)&hour, sizeof(hour));
		ifs.read((char*)&minute, sizeof(minute));
		ifs.read((char*)&t, sizeof(t));
		ifs.read((char*)&fare, sizeof(fare));
		ifs.read((char*)&maxn, sizeof(maxn));
		ifs.read((char*)&sold, sizeof(sold));
		return Timetable(no, hour, minute, start, last, t, fare, maxn, sold);
	}
#else
	string toString() const // ������ļ���һ��
	{
		stringstream ss;
		ss << no << " "	<< hour << " " << minute << " "	<< Starting_station << " " << Last_station << " " \
			<< time << " " << fare << " " << max_number << " " << sold_number;
		return ss.str();
	}
	static Timetable fromString(const string& line) // ��һ���ı��н���
	{
		string no, start, last;
		int h, m, f, maxn, sold;
		float t;
		stringstream ss(line);
		ss >> no >> h >> m >> start >> last >> t >> f >> maxn >> sold;
		return Timetable(no, h, m, start, last, t, f, maxn, sold);
	}
#endif
	
	int GetHour() const { return hour; }
	int GetMinute() const { return minute; }
	string GetLastStation() const { return Last_station; }
	int GetSold() const { return sold_number; }
	void SetSold(int s) { sold_number = s; }
	int TimeCompare()
	{
		return (hour * 100 + minute);
	}
	int TicketAvailable()
	{
		return (max_number - sold_number);
	}
	
	friend void Query(vector<Timetable> timetables);
};
