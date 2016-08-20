/*
TODO : multi-player
TODO : reflect and more barriers
 
 */
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include "list.h"
#include "gameBoard.h"

struct Game {
	bool PAUSE;
	bool RAND_TIME;
	int T, d;
	gameBoard *gb;
	random *rd;
	Point g;
	list<Point> que;

	bool setGem() {
		if (!gb->hasBlank())
			return false;
        g = gb->getBlank();
		gb->setPix(g, gem);
		return true;
	}

	Game() {
		rd = new random();
		gb = new gameBoard();
		PAUSE = false;
		RAND_TIME = false;

		que.push_back(Point(1, 1));
		d = 0;
        gb->setPix(que.get_front(), head[d]);
		setGem();
	}

	bool move() {
		Point hd = que.get_front();
		Point newHd = Point(hd.x + dx[d], hd.y + dy[d]);
		que.push_front(newHd);
		gb->setPix(hd, body);
		if (gb->getPix(newHd) == gem) {
			setGem();
			return true;
		}

		if (gb->getPix(newHd) == blank) {
			gb->setPix(newHd, head[d]);
			Point rr = que.get_back();
			gb->setPix(rr, blank);
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
		return changeD(RIGHT);
	}

	bool turnUp() {
		return changeD(UP);
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
					changeD(LEFT);
					break;
				case 'l':
					changeD(RIGHT);
					break;
				case 'k':
					changeD(UP);
					break;
				case 'j':
					changeD(DOWN);
					break;

				case '4':
					changeD(LEFT);
					break;
				case '6':
					changeD(RIGHT);
					break;
				case '8':
					changeD(UP);
					break;
				case '5':
					changeD(DOWN);
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
			if (!move()) {
				break;
			}
			if (RAND_TIME) {
				T = 5 + rd->rnd(0, 100);
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

	int level = 1;
	scanf("%d", &level);

	game = new Game();
	game->setLevel(level);
	while (game->gaming());

	cls();
	printf("Game Over!\n");
	printf("Your score : %d\n", game->que.getNum());
    getch();

	return 0;
}
