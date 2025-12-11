#pragma once
#include<iostream>
#include<fstream>
#include<string>

using namespace std;

void Write(ofstream& out, int num, int t);

bool isLeap(int year);

struct Date {
	int year, month, day;

	void InputConsole() {
		cin >> year >> month >> day;
		return;
	}

	void InputFile(ifstream& inp) {
		inp >> year >> month >> day;
		return;
	}

	void OutputConsole() {
		cout << year << "/" << month << "/" << day << "\n";
		return;
	}

	void OutputFile(ofstream& out) {
		Write(out, year, 4); out << "- ";
		Write(out, month, 2); out << "- ";
		Write(out, day, 2);
		out << "\n";
		return;
	}

};

void outputDateWithFormat(ofstream& out, Date *d, string s);

int DatetoId(Date *d);
Date IdtoDate(int id);

int Compare(Date *a, Date *b);
void Tomorrow(Date *d);
void Yesterday(Date *d);

void Increase(Date *d, int k);
void Decrease(Date *d, int k);

int ComputeSameYear(Date *d);
int Compute1970(Date *d);

string DateofWeek(Date *d);

bool DateEqual(Date *a, Date *b);

Date Today();