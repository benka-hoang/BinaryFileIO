#include<iostream>
#include<fstream>
#include<string>
#include<algorithm>
#include"Info.h"

using namespace std;

int String_to_Int(string s, int type);
Info Check_Format_GiveAddress(string s);
string name_of_file(string address);
void Split_by_num_part(ifstream& source, string des, int x);
void Split_by_bytes(ifstream& source, string des, int x);
string Int_to_String(int x);

// This is a simulation of Command Prompt :
// Only Function : Split file
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
		cout << info.source << "\n";
		ifstream source_file(info.source);
		if (!source_file.is_open()) {
			cout << "Wrong file input\n";
			continue;
		}
		ofstream des_file(info.desti + name_of_file(info.source) + ".part01");
		if (!des_file.is_open()) {
			cout << "Wrong file output\n";
			continue;
		}
		if (info.type == 0) {
			Split_by_num_part(source_file, info.desti + name_of_file(info.source), info.x);
		}
		else {
			Split_by_bytes(source_file, info.desti + name_of_file(info.source), info.x);
		}
		cout << "Split-Completed\n";

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
	const int max_string = 7;
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
	if (arr[0] != "MYSPLITFILE") return info;
	if (arr[1] != "-s") return info;
	if (arr[3] != "-d") return info;
	if (arr[5] != "-numpart" && arr[5] != "-sizeapart") return info;
	if (arr[5] == "-numpart")
		info.type = 0;
	else
		info.type = 1;
	info.x = String_to_Int(arr[6], info.type);
	if (info.x == -1) return info;
	info.is_format = true;
	info.source = arr[2], info.desti = arr[4];
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

void Split_by_num_part(ifstream& source, string des, int x){
	string s = "";
	char ch;
	while (source.get(ch)) {
		s.push_back(ch);
	}
	int id = 0; int per_file = s.size() / x;
	for (int i = 1; i <= x; ++i) {
		ofstream desti(des + ".part" + Int_to_String(i));
		int limit = min(int(s.size()) - 1, id + per_file - 1);
		while (id <= limit) {
			desti << s[id];
			++id;
		}
	}
	return;
}

void Split_by_bytes(ifstream& source, string des, int x){
	string s = "";
	char ch;
	while (source.get(ch)) {
		s.push_back(ch);
	}
	int id = 0; int id_file = 0;
	while (id < s.size()) {
		++id_file;
		ofstream desti(des + ".part" + Int_to_String(id_file));
		int num = 0;
		while (id < s.size() && num < x) {
			desti << s[id];
			++id; ++num;
		}
	}
	return;
}
