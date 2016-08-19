/*
TODO : board can be prettified
TODO : multi-player
TODO : reflect and more barriers
 
 */
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include "game.h"
#include "list.h"
#include "random.h"

const int W = 20;
const int H = 20;

int level, T;

const int dx[] = {0, 0, 1, -1};
const int dy[] = {1, -1, 0, 0};
#define LEFT 1
#define RIGHT 0
#define UP 3
#define DOWN 2
struct Point {
	int x, y;
	Point() {}
	Point(int x, int y):x(x), y(y) {
	}
};

char barrier = '*';
char gem = '@';
char body = '+';
char blank = ' ';
char head[] = {'>', '<', 'v', '^'};
struct gameBoard {

	char bd[H+2][W+2];
	random *rd;
	int d;
	list<Point> que;

	void setGem() {
		int gx = rd->rnd(1, H);
		int gy = rd->rnd(1, W);
		while (bd[gx][gy] != blank) {
			gx = rd->rnd(1, H);
			gy = rd->rnd(1, W);
		}
		bd[gx][gy] = gem;
	}

	gameBoard() {
		rd = new random();
		memset(bd, ' ', sizeof bd);
		for (int i = 0; i < W+2; ++i) {
			bd[0][i] = barrier;
			bd[H+1][i] = barrier;
		}
		for (int i = 0; i < H+2; ++i) {
			bd[i][0] = barrier;
			bd[i][W+1] = barrier;
		}
		que.push_back(Point(1, 1));
		d = 0;
		bd[1][1] = head[d];
		setGem();
	}

	bool move() {
		Point hd = que.get_front();
		Point newHd = Point(hd.x + dx[d], hd.y + dy[d]);
		que.push_front(newHd);
		bd[hd.x][hd.y] = body;
		if (bd[newHd.x][newHd.y] == gem) {
			setGem();
			return true;
		}

		if (bd[newHd.x][newHd.y] == blank) {
			bd[newHd.x][newHd.y] = head[d];
			Point rr = que.get_back();
			bd[rr.x][rr.y] = blank;
			que.pop_back();
			return true;
		}
		return false;
	}

	bool changeD(int newD) {
		if (d == LEFT && newD == RIGHT) return false;
		if (d == RIGHT && newD == LEFT) return false;
		if (d == UP && newD == DOWN) return false;
		if (d == DOWN && newD == UP) return false;
		d = newD;
		return true;
	}

	void print() {
		cls();
		for (int i = 0; i < H+2; ++i) {
			for (int j = 0; j < W+2; ++j)
				putchar(bd[i][j]);
			puts("");
		}
	}

};

gameBoard *game;
bool PAUSE;

void key() {
	if (kbhit()) {
		char key = getch();
		switch (key) {
			case 'p':
				PAUSE = true;
				break;
			case 's':
				PAUSE = false;
				break;

			case 'h':
				game->changeD(LEFT);
				break;
			case 'l':
				game->changeD(RIGHT);
				break;
			case 'k':
				game->changeD(UP);
				break;
			case 'j':
				game->changeD(DOWN);
				break;

			case '4':
				game->changeD(LEFT);
				break;
			case '6':
				game->changeD(RIGHT);
				break;
			case '8':
				game->changeD(UP);
				break;
			case '5':
				game->changeD(DOWN);
				break;
			default:
				rewind(stdin);
				break;
		}
	}
}

bool gaming() {
	PAUSE = false;
	game = new gameBoard();

	game->print();
	while (true) {
		
		key();
		if (PAUSE) {
			continue;
		}
		if (!game->move()) {
			return false;
		}
		game->print();
		Sleep(T);
	}

	return false;
}

int main() {

	hideCursor();
	printf("please select the level(1~6)\n");
	
	level = 1;
	scanf("%d", &level);
	switch (level) {
		case 1:
			T = 200;
			break;
		case 2:
			T = 180;
			break;
		case 3:
			T = 160;
			break;
		case 4:
			T = 140;
			break;
		case 5:
			T = 120;
			break;
		case 6:
			T = 100;
			break;
	}
	while (gaming());

	return 0;
}
