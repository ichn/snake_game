#include <cstdio>
#include <cstdlib>
#include <ctime>
struct random {
	random() {
		srand((int)time(NULL));
	}
	int rnd() {
		return rand();
	}
	int rnd(int a) {
		return rnd() % a + 1;
	}
	int rnd(int a, int b) {
		return rnd() % (b - a) + a;
	}
};
