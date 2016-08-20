#include <windows.h>
#include "conio.h"

inline void gotoxy(int x, int y) {
	COORD coord;
	coord.X = y;
	coord.Y = x;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void hideCursor(int k=0) {
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci;
	GetConsoleCursorInfo(hOut, &cci);
	cci.bVisible=k;
	SetConsoleCursorInfo(hOut, &cci);
}

void cls() {
	system("cls");
}
void cls(int k) {
	for (int i = 0; i < k; ++i)
		putchar('\b');
}

inline bool keyHit() {
	return kbhit();
}

