#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define SIZE 140

int moveGuard(int x, int y, int **tab, int dx, int dy) {
	tab[x][y] = 2;
	// lets combine prime numbers
	// 2, 3, 17, 7 (up, down, left, right)

	/*if (dx == -1 && dy == 0) {*/
		/*tab[x][y] = 2;*/
	/*} else if (dx == 1 && dy == 0) {*/
		/*tab[x][y] = 3;*/
	/*} else if (dx == 0 && dy == -1) {*/
		/*tab[x][y] = 17;*/
	/*} else if (dx == 0 && dy == 1) {*/
		/*tab[x][y] = 7;*/
	/*}*/

	if (x + dx >= SIZE || y + dy >= SIZE || x+ dx < 0 || y+ dy < 0 || tab[x+dx][y+dy] == -1) {
		return 1;
	}
	if (tab[x + dx][y + dy] == 1) { // obst
		// rotate 90deg
		int tmp = dx;
		dx = dy;
		dy = -tmp;
	}
	x += dx;
	y += dy;
	return 1 + moveGuard(x, y, tab, dx, dy);
}
int moveGuardNotRec(int x, int y, int **tab, int dx, int dy) {
	int moves = 0;
	
	while (!(x + dx >= SIZE || y + dy >= SIZE || x + dx < 0 || y+ dy < 0 || tab[x+dx][y+dy] == -1 || x >= SIZE || y >= SIZE || x < 0 || y < 0) && moves < SIZE * SIZE * SIZE) {
		if (tab[x + dx][y + dy] == 1 || tab[x+dx][y+dy] == 5) { // obst
			// rotate 90deg
			int tmp = dx;
			dx = dy;
			dy = -tmp;
		}
		x += dx;
		y += dy;
		moves++;
	}
	if (moves >= SIZE * SIZE * 3) {
		return 1;
	} else {
		return 0;
	}
}

int moveGuardO(int x, int y, int **tab, int dx, int dy, int moves) {
	/*tab[x][y] = 2;*/
	if (moves > SIZE * SIZE * 10) {
		return 1;
	}
	if (x + dx >= SIZE || y + dy >= SIZE || x + dx < 0 || y+ dy < 0 || tab[x+dx][y+dy] == -1 || x >= SIZE || y >= SIZE || x < 0 || y < 0) {
		return 0;
	}
	if (tab[x + dx][y + dy] == 1 || tab[x + dx][y + dy] == 5) { // obst
		if (tab[x][y] == dx*10 + dy*100 + 8) {
			return 1; // successfully inde
		}

		if (tab[x + dx][y + dy] == 5) {
			tab[x][y] = dx*10 + dy*100 + 8; // We rotated here. Important to notice.
		}
		// rotate 90deg
		int tmp = dx;
		dx = dy;
		dy = -tmp;

	}
	x += dx;
	y += dy;
	return moveGuardO(x, y, tab, dx, dy, moves + 1);
}

int **copy(int **tab) {
	int **newTab = malloc(sizeof(int*) * SIZE);
	for (int a = 0; a < SIZE; a++) {
		newTab[a] = malloc(sizeof(int) * SIZE);
		for (int b = 0; b < SIZE; b++) {
			newTab[a][b] = tab[a][b];
		}
	}
	return newTab;
}

void freeT(int **tab) {
	for (int a = 0; a < SIZE; a++) {
		free(tab[a]);
	}
	free(tab);
}

int countObst(int **tab, int x, int y, int dx, int dy) {
	int c = 0;
	int **newTab = copy(tab);
	int ch = 0;
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			if (tab[i][j] != 0) {
				if (tab[i][j] == 2) {
					ch++;
					tab[i][j] = 5; // set obst
					assert(tab != NULL);
					int a = moveGuardNotRec(x,y,tab,dx,dy);
					c += a;
					freeT(tab);
					tab = copy(newTab);
				}
				/*if (tab[i][j] % 3 == 0) {*/
					/*ch++;*/
					/*tab[i][j] = 5; // set obst*/
					/*assert(tab != NULL);*/
					/*int a = moveGuardO(i,j,tab,1,0, 0);*/
					/*printf("Testing: %d %d\n", i,j);*/
					/*if (a != 0) {*/
							/*printf("X: %d; Y: %d\n", i,j);*/
					/*}*/
					/*c += a;*/
					/*freeT(tab);*/
					/*tab = copy(newTab);*/
				/*}*/
				/*if (tab[i][j] % 17 == 0) {*/
					/*ch++;*/
					/*tab[i][j] = 5; // set obst*/
					/*assert(tab != NULL);*/
					/*int a = moveGuardO(i,j,tab,0,-1, 0);*/
					/*printf("Testing: %d %d\n", i,j);*/
					/*if (a != 0) {*/
							/*printf("X: %d; Y: %d\n", i,j);*/
					/*}*/
					/*c += a;*/
					/*freeT(tab);*/
					/*tab = copy(newTab);*/
				/*}*/
				/*if (tab[i][j] % 7 == 0) {*/
					/*ch++;*/
					/*tab[i][j] = 5; // set obst*/
					/*assert(tab != NULL);*/
					/*int a = moveGuardO(i,j,tab,0,1, 0);*/
					/*printf("Testing: %d %d\n", i,j);*/
					/*if (a != 0) {*/
							/*printf("X: %d; Y: %d\n", i,j);*/
					/*}*/
					/*c += a;*/
					/*freeT(tab);*/
					/*tab = copy(newTab);*/
				/*}*/

			}
		}
	}
	return c;
}

int countAll(int **tab, int w, int h) {
	int countOfMoves = 0;
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			if (tab[i][j] == 2) {
				countOfMoves++;
			}
			/*printf("%d ", tab[i][j]);*/
		}
		/*printf("\n");*/
	}
	return countOfMoves;
}

int main() {
	FILE *f = fopen("input1.txt", "r");


	int guardX, guardY;
	// UP
	int dx = -1;
	int dy = 0;
	int **tab = malloc(sizeof(int*) * SIZE);
	for (int a = 0; a < SIZE; a++) {
		tab[a] = malloc(sizeof(int) * SIZE);
		for (int b = 0; b < SIZE; b++) {
			tab[a][b] = -1;
		}
	}

	char line[SIZE];

	int i = 0;
	while (fgets(line, SIZE, f) != NULL) {
		for (int j = 0; j < SIZE; j++) {
			/*tab[i][j] = line[j] == '#' ? 1 : 0;*/
			if (line[j] == '#') {
				tab[i][j] = 1;
			} else if (line[j] == '.') {
				tab[i][j] = 0;
			}
			if (line[j] == '^') {
				guardX = i;
				guardY = j;
			}
		}
		i++;
	}
	fclose(f);

	printf("guard pos: %d, %d \n", guardX, guardY);

	int movesC = moveGuard(guardX, guardY, tab, dx, dy);

	/*int count = countAll(tab, 11, 11);*/
	for (int n = 0; n < SIZE; n++) {
		for (int m = 0; m < SIZE; m++) {
			if (tab[n][m] == 0) {
				printf(".");
			} else if (tab[n][m] % 2 == 0 || tab[n][m] % 3 == 0 || tab[n][m] % 17 == 0 || tab[n][m] % 7 == 0) {
				printf("X");
			} else if (tab[n][m] == 0) {
				printf(".");
			} else if (tab[n][m] == 1) {
				printf("#");
			} else if (tab[n][m] == -1) {
				printf(" ");
			} else {
				printf("%d", tab[n][m]);
			}
		}
		printf("\n");
	}

	int countObstA = countObst(tab, guardX, guardY, dx, dy);

	/*printf("Count: %d\n", count);*/

	printf("Count of obst: %d\n", countObstA);
	return 0;
}
