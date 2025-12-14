#include<iostream>
#include<fstream>
#include<string>
#include<algorithm>
#include"Info.h"

using namespace std;

int String_to_Int(string s, int type);
Info Check_Format_GiveAddress(string s);
string name_of_file(string address);
string Int_to_String(int x);
void MergeFile(string source, ofstream& desti);

// This is a simulation of Command Prompt :
// Only Function : Merge file
int main() {
	cout << "MY_CMD Program (Enter 0 to Exit) : \n";
	while (true) {
		cout << '>';
		string read;
		getline(cin, read);
		if (read == "0") {
			cout << "MY_CMD stop!\n";
			return 0;
		}
		Info info = Check_Format_GiveAddress(read);
		if (info.is_format == false) {
			cout << "There no such command\n";
			continue;
		}
		ifstream source_file(info.source + ".part01");
		if (!source_file.is_open()) {
			cout << "Wrong file input\n";
			continue;
		}
		ofstream des_file(info.desti + name_of_file(info.source));
		if (!des_file.is_open()) {
			cout << "Wrong file output\n";
			continue;
		}
		MergeFile(info.source, des_file);
		cout << "Merge-Completed\n";
		source_file.close(); des_file.close();
	}
	return 0;
}

int String_to_Int(string s, int type) {
	const int limit_0 = 100, limit_1 = 1000000;
	for (int i = 0; i < s.size(); ++i) if (!('0' <= s[i] && s[i] <= '9')) {
		return -1;
	}
	int n = 0;
	for (int i = 0; i < s.size(); ++i) {
		n = n * 10 + int(s[i]) - int('0');
		if (type == 0 && n > limit_0) return -1;
		if (type == 1 && n > limit_1) return -1;
	}
	return n;
}

Info Check_Format_GiveAddress(string s) {
	Info info; info.Init();
	const int max_string = 5;
	string arr[max_string];
	for (int i = 0; i < max_string; ++i) arr[i] = "";
	int n = 0, id = 0;
	for (int i = 0; i < s.size(); ++i) if (s[i] != ' ') {
		if (id == max_string)
			return info;
		while (i < s.size() && s[i] != ' ') {
			arr[id].push_back(s[i]);
			++i;
		}
		++id;
	}
	if (arr[0] != "MYMERGEFILE") return info;
	if (arr[1] != "-s") return info;
	if (arr[3] != "-d") return info;
	if (arr[2].size() < 7) return info;
	if (arr[2].substr(arr[2].size() - 7, 7) != ".part01") return info;
	info.is_format = true;
	arr[2].resize(arr[2].size() - 7);
	info.source = arr[2]; info.desti = arr[4];
	return info;
}

string name_of_file(string address) {
	string s = "";
	int pos = 0;
	for (int i = 0; i < address.size(); ++i) if (address[i] == '/' || address[i] == '\\') {
		pos = i;
	}
	s = address.substr(pos, address.size() - pos);
	return s;
}

string Int_to_String(int x) {
	string s = "";
	while (x > 0) {
		int c = x % 10;
		s = char(c + int('0')) + s;
		x = x / 10;
	}
	if (s.size() == 1)
		s = '0' + s;
	return s;
}

void MergeFile(string source, ofstream& desti) {
	ifstream inp(source + ".part01");
	int id = 1;
	while (inp.is_open()) {
		char ch;
		while (inp.get(ch)) {
			desti << ch;
		}
		inp.close(); inp.clear();
		++id;
		inp.open(source + ".part" + Int_to_String(id));
	}
	return;
}