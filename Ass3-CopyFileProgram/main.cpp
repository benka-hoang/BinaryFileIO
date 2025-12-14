#include<iostream>
#include<fstream>
#include<string>

using namespace std;

pair<bool, pair<string, string>> Check_Format_GiveAddress(string s) {
	string arr[5];
	for (int i = 0; i < 5; ++i) arr[i] = "";
	int n = 0, id = 0;
	for (int i = 0; i < s.size(); ++i) if (s[i] != ' ') {
		if (id == 5)
			return { false, {"", ""} };
		while (i < s.size() && s[i] != ' ') {
			arr[id].push_back(s[i]);
			++i;
		}
		++id;
	}
	if (arr[0] != "MYCOPYFILE") return { false, {"", ""} };
	if (arr[1] != "-s") return { false, {"", ""} };
	if (arr[3] != "-d") return { false, {"", ""} };
	//delete
	return { true, {arr[2], arr[4]} };
}

string name_of_file(string address) {
	string s = "";
	int pos = 0; 
	for (int i = 0; i < address.size(); ++i) if(address[i] == '/' || address[i] == '\\'){
		pos = i;
	}
	s = address.substr(pos, address.size() - pos);
	return s;
}

// This is a simulation of Command Prompt :
// Only Function : Copy File
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
		pair<bool, pair<string, string>> info;
		info = Check_Format_GiveAddress(read);
		if (info.first == false) {
			cout << "There no such command\n";
		}
		ifstream source_file(info.second.first);
		if (!source_file.is_open()) {
			cout << "Wrong file input\n";
			return 0;
		}
		ofstream des_file(info.second.second + name_of_file(info.second.first));
		cout << info.second.second + name_of_file(info.second.first) << "\n";
		if (!des_file.is_open()) {
			cout << "Wrong file output\n";
			return 0;
		}
		char ch;
		while (source_file.get(ch)) {
			des_file << ch;
		}
		cout << "Copy-Completed\n";
		
		source_file.close(); des_file.close();
	}
	return 0;
}