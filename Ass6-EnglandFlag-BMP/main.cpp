#include<iostream>
#include<fstream>
#include"FlagInfo.h"

using namespace std;

void CreateFlag(FlagInfo info);
void WriteInt(ofstream& f, int val, int bytes);

int main() {
	FlagInfo info;
	info.Init();

	cout << "Input Width and Height: ";
	cin >> info.width >> info.height;

	if (info.width <= 0 || info.height <= 0) {
		cout << "Invalid size!\n";
		return 0;
	}

	CreateFlag(info);

	cout << "Done! File saved as " << info.filename << endl;
	return 0;
}

// Ham ho tro ghi so nguyen duoi dang Little Endian (bat buoc cho BMP)
void WriteInt(ofstream& f, int val, int bytes) {
	for (int i = 0; i < bytes; ++i) {
		f.put((val >> (i * 8)) & 0xFF);
	}
}

void CreateFlag(FlagInfo info) {
	ofstream f(info.filename, ios::binary);
	if (!f.is_open()) return;

	int w = info.width;
	int h = info.height;

	int padding = (4 - (w * 3) % 4) % 4;
	int rowSize = w * 3 + padding;
	int dataSize = rowSize * h;
	int fileSize = 54 + dataSize;

	f.put('B'); f.put('M');
	WriteInt(f, fileSize, 4);
	WriteInt(f, 0, 4);
	WriteInt(f, 54, 4);

	WriteInt(f, 40, 4);
	WriteInt(f, w, 4);
	WriteInt(f, h, 4);
	WriteInt(f, 1, 2); 
	WriteInt(f, 24, 2);
	WriteInt(f, 0, 4); 
	WriteInt(f, dataSize, 4);
	WriteInt(f, 2835, 4);
	WriteInt(f, 2835, 4);
	WriteInt(f, 0, 4);
	WriteInt(f, 0, 4);

	int thickness = h / 5;
	int centerX = w / 2;
	int centerY = h / 2;

	for (int y = 0; y < h; ++y) {
		for (int x = 0; x < w; ++x) {
			bool isRed = false;

			if (x >= centerX - thickness / 2 && x <= centerX + thickness / 2)
				isRed = true;
			if (y >= centerY - thickness / 2 && y <= centerY + thickness / 2)
				isRed = true;

			if (isRed) {
				f.put(0); f.put(0); f.put((char)255);
			}
			else {
				f.put((char)255); f.put((char)255); f.put((char)255);
			}
		}
		for (int k = 0; k < padding; ++k) f.put(0);
	}

	f.close();
}