#include<iostream>
#include<fstream>

using namespace std;

void Save() {
	int n; cin >> n;
	int* arr; arr = new int[n];
	for (int i = 0; i < n; ++i) cin >> arr[i];
	fstream fout;
	fout.open("input.bin", ios::out | ios::binary);
	fout.write((char*)&n, sizeof(n));
	for (int i = 0; i < n; ++i)
		fout.write((char*)(arr + i), sizeof(arr[0]));
	fout.close();
	return;
}

void Load() {
	int n;
	fstream fin;
	fin.open("input.bin", ios::in | ios::binary);
	fin.read((char*)&n, sizeof(n));
	int* arr; arr = new int[n];
	for (int i = 0; i < n; ++i)
		fin.read((char*)(arr + i), sizeof(arr[0]));
	for (int i = 0; i < n; ++i) {
		for (int j = i + 1; j < n; ++j) if (arr[i] > arr[j])
			swap(arr[i], arr[j]);
	}
	cout << arr[n / 2] << "\n";
	return;
}

int main() {
	cout << "Option : \n";
	cout << "1 : Enters an array of integers. The program will save the array to input.bin\n";
	cout << "2 : The program will load an array of integers from input.bin and output the median value to console\n";
	cout << "What is your option : "; int t; cin >> t;
	while (t != 1 && t != 2) {
		cout << "Please re-enter your option : "; cin >> t;
	}
	if (t == 1) {
		Save();
	}
	else
		Load();
	return 0;
}