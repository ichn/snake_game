//
// Created by 胡志峰 on 2016/8/20.
//

#ifndef SNAKE_GAME_GAMEBOARD_H
#define SNAKE_GAME_GAMEBOARD_H

#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;
#include "random.h"
#include "game.h"

const int W = 15;
const int H = 10;

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


char gem = '@';
char body = '+';
char blank = ' ';
char head[] = {'>', '<', 'v', '^'};
struct gameBoard {

private:
	char bd[H+2][W+2];
	void print() {
		cls();
		for (int i = 0; i < H+2; ++i) {
			for (int j = 0; j < W+2; ++j)
				putchar(bd[i][j]);
			puts("");
		}
	}

public:

    bool inBoard(Point p) {
		return 1 <= p.x && p.x <= H && 1 <= p.y && p.y <= W;
	}

    void setPix(Point p, char c) {

        if (!inBoard(p)) {
			// ERROR handle
			return ;
		}

		bd[p.x][p.y] = c;
		gotoxy(p.x, p.y);
		putchar(c);
	}

	gameBoard() {
		memset(bd, ' ', sizeof bd);
		for (int i = 0; i < W+2; ++i) {
			bd[0][i] = '-';
			bd[H+1][i] = '-';
		}
		for (int i = 0; i < H+2; ++i) {
			bd[i][0] = '|';
			bd[i][W+1] = '|';
		}
		bd[H+1][0] = '+';
		bd[H+1][W+1] = '+';
		bd[0][W+1] = '+';
		bd[0][0] = '+';
		print();
	}

	bool chkBlank(Point p) {
		return bd[p.x][p.y] == blank;
	}

	bool hasBlank() {
        for (int i = 1; i <= H; ++i)
			for (int j = 1; j <= W; ++j)
				if (bd[i][j] == blank)
					return true;
		return false;
	}

    Point getBlank() {
		if (!hasBlank()) {
			// ERROR handle
			return Point(0, 0);
		}
        vector<Point> pt;
		pt.clear();
		for (int i = 1; i <= H; ++i)
			for (int j = 1; j <= W; ++j)
				if (bd[i][j] == blank)
					pt.push_back(Point(i, j));
        random_shuffle(pt.begin(), pt.end());
		return pt[0];
	}

	char getPix(Point p) {
		return bd[p.x][p.y];
	}

	void setBlank(Point p) {
		if (!inBoard(p)) {
            // ERROR handle
			return ;
		}
        setPix(p, blank);
	}

};

#endif //SNAKE_GAME_GAMEBOARD_H
