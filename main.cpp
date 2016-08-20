/*
TODO : multi-player
TODO : reflect and more barriers
 
 */
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include "game.h"
#include "list.h"
#include "random.h"
#include "gameBoard.h"

const int W = 40;
const int H = 20;

struct Game {
	gameBoard *gb;
	random *rd;
	bool PAUSE;
	bool RAND_TIME;
	Point g;
	int T;

	bool setGem() {

	}

	Game() {
		gb = new gameBoard();
		rd = new random();
	}

	list<Point> que;

	bool setGem() {
		if (!gb->hasBlank())
			return false;
        g = gb->getBlank();
		gb->setPix(g, gem);
	}

	gameBoard() {
		rd = new random();
		gb = new gameBoard();
		PAUSE = false;
		RAND_TIME = false;

		que.push_back(Point(1, 1));
		d = 0;
        gb->setPix(que.get_front(), head[d])
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

	int getDir() {
		return d;
	}

    bool turnLeft() {
		return changeD(LEFT);
	}

	bool turnRight() {
		return changeD(RIGHT)
	}

	bool turnUp() {
		return changeD(UP)
	}

	bool turnDown() {
		return changeD(DOWN);
	}

	void setLevel(int l) {
		switch (l) {
			case 1:
				T = 200;
				break;
			case 2:
				T = 100;
				break;
			case 3:
				T = 50;
				break;
			case 4:
				T = 25;
				break;
			case 5:
				T = 10;
				break;
			default:
				RAND_TIME = true;
				break;
		}
	}


	void readKey() {
		if (keyHit()) {
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

		while (true) {

			readKey();
			if (PAUSE) {
				continue;
			}
			if (!game->move()) {
				break;
			}
			game->print();
			if (RAND_TIME) {
				T = 5 + game->rd->rnd(0, 100);
			}
			Sleep(T);
		}

		return false;
	}

};

Game *game;

int main() {

	hideCursor();
	printf("please select the level(1~6)\n");

	level = 1;
	scanf("%d", &level);

	game = new Game();
	game->setLevel(level);
	while (game->gaming());

	cls();
	printf("Game Over!");
    getch();

	return 0;
}
