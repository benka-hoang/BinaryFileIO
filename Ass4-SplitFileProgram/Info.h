#pragma once
#include<string>

using namespace std;

struct Info {
	bool is_format;
	string source, desti;
	int type, x;
	// -1 : Wrong
	// 0 : -numapart
	// 1 : -sizeapart

	void Init();
};