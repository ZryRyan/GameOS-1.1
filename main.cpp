#include "plane.h"
#include "box.h"
#include <iostream>
#include <cstdio>
#include <conio.h>
#include <Windows.h>
using namespace std;

void print(string s) {
	cout << s << endl;
}

int main() {
	while (true) {
		print("");
		print("");
		print("");
		print("");
		print("");
		print("                 GameOS 1.0��ӭ��������");
		print("");
		print("");
		print("");
		print("��ѡ����Ϸ��");
		print("1���ɻ���ս    2��������    #���˳���Ϸ");
		char x = _getch();
		system("cls");
		if (x == '1') {
			Plane();
		}
		else if (x == '2') {
			Box();
		}
		else {
			break;
		}
	}
	return 0;
}
