#include<iostream>
#include<fstream>
#include"Date.h"

using namespace std;

void SaveDate() {
	int n; cin >> n;
	Date* arr; arr = new Date[n];
	for (int i = 0; i < n; ++i) {
		arr[i].InputConsole();
	}
	fstream file;
	file.open("input.bin", ios::out | ios::binary);
	file.write((char*)&n, sizeof(n));
	file.write((char*)arr, n * sizeof(Date));
	file.close();
	delete[] arr;
	return;
}

Date LoadDate_NewestDate() {
	fstream file;
	file.open("input.bin", ios::in | ios::binary);
	int n; file.read((char*)&n, sizeof(n));
	Date* arr = new Date[n];
	file.read((char*)arr, n * sizeof(Date));
	Date newest = arr[0];
	for (int i = 1; i < n; ++i) if (DatetoId(&arr[i]) > DatetoId(&newest)) {
		newest = arr[i];
	}
	return newest;
}

int main() {
	cout << "Option : \n";
	cout << "1 : Enters an array of dates. The program will save the array to input.bin\n";
	cout << "2 : The program will load an array of dates from input.bin, then find and output the newest date to console\n";
	cout << "What is your option : "; int t; cin >> t;
	if (t == 1) {
		SaveDate();
	}
	else {
		Date d = LoadDate_NewestDate();
		d.OutputConsole();
	}
	return 0;
}