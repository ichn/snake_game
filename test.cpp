#include <cstdio>
#include <cstring>
#include "game.h"

int main() {
	cls();
	for (int i = 0; i <= 10; ++i) {
		gotoxy(i, i);
		putchar('c');
	}
	puts("");
	return 0;
}
