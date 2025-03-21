#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

void printTab(int **tab) {
	for (int i = 0; i < 142; i++) {
		for (int j = 0; j < 142; j++) {
			printf("%d", tab[i][j]);
		}
		printf("\n");
	}
}


void initProp(int **propagation, char arr[142][142]) {
	for (int i = 0; i < 142; i++) {
		for (int j = 0; j < 142; j++) {
			if (arr[i][j] == 'X') {
				propagation[i][j] = 1;
			}
		}
	}
}

bool propSingleDir(int **propagation, char arr[142][142], char nextC, int dx, int dy, int x, int y) {
	bool chan = false;
	if (x + dx >= 142 || x + dx < 0 || y + dy < 0 || y + dy >= 142) {
		printf("Out of bounds: %d, %d\n", x + dx, y + dy);

		return chan;
	}
	if (arr[x + dx][y + dy] == nextC) {
		propagation[x+ dx][y + dy] = propagation[x + dx][y+dy] + propagation[x][y];
		chan = true;
	}
	return chan;
}

void propagate(int **propagation, char arr[142][142], char c, char nextC) {
	printf("Propagating %c to %c\n", c, nextC);
	for (int i = 0; i < 142; i++) {
		for (int j = 0; j < 142; j++) {
			if (arr[i][j] == c && propagation[i][j] > 0) {
				// Haut, bas, gauche, droite, haut droite, haut gauche, bas haut, bas droite
				propSingleDir(propagation, arr, nextC, 1, 0, i, j);
                propSingleDir(propagation, arr, nextC, -1, 0, i, j);
                propSingleDir(propagation, arr, nextC, 0, 1, i, j);
                propSingleDir(propagation, arr, nextC, 0, -1, i, j);
                propSingleDir(propagation, arr, nextC, 1, 1, i, j);
                propSingleDir(propagation, arr, nextC, -1, 1, i, j);
                propSingleDir(propagation, arr, nextC, 1, -1, i, j);
                propSingleDir(propagation, arr, nextC, -1, -1, i, j);
			}
		}
	}
}

int countS(int **p, char arr[142][142]) {
	int c = 0;
	for (int i = 0; i < 142; i++) {
		for (int j = 0; j < 142; j++) {
			if (arr[i][j] == 'S') {
				c += p[i][j];
			}
		}
	}
	return c;
}

int p4(char arr[142][142], int x, int y, int dx, int dy) {
	if ((x + 3 * dx > 141) || (x + 3 * dx < 0) || (y + 3 * dy > 141) || (y + 3 * dy < 0)) {
		return 0;
	}
	char xmas[] = "XMAS";

	for (int i = 0; i < 4; i++) {
		if (arr[x + i*dx][y + i*dy] != xmas[i]) {
			return 0;
		}
	}
	return 1;
}

int findCross(char arr[142][142], int x, int y) {
	int c = 0;
	if ((x + 2 < 142) && (y + 2 < 142) && (arr[x][y] == 'M') && (arr[x+1][y+1] == 'A') && (arr[x+2][y+2] == 'S') && (arr[x][y + 2] == 'S') &&	(arr[x + 2][y] == 'M')) {
		// M.S
		// .A.
		// M.S
		c += 1;
	} 
	if ((x - 2 >= 0) && (y - 2 >= 0) && (arr[x][y] == 'M') && (arr[x-1][y-1] == 'A') && (arr[x-2][y-2] == 'S') && (arr[x][y - 2] == 'S') &&	(arr[x - 2][y] == 'M')) {
		// S.M
		// .A.
		// S.M
		c += 1;
	} 
	if ((x - 2 >= 0) && (y - 2 >= 0) && (arr[x][y] == 'M') && (arr[x-1][y-1] == 'A') && (arr[x-2][y-2] == 'S') && (arr[x][y - 2] == 'M') &&	(arr[x - 2][y] == 'S')) {
		// S.S
		// .A.
		// M.M
		c += 1;
	}
	if ((x + 2 < 142) && (y + 2 < 142) && (arr[x][y] == 'M') && (arr[x+1][y+1] == 'A') && (arr[x+2][y+2] == 'S') && (arr[x][y + 2] == 'M') &&	(arr[x + 2][y] == 'S')) {
		// M.M
		// .A.
		// S.S
		c += 1;
	} 
	return c;
}

int countAllCrosses(char arr[142][142]) {
	int count = 0;

	for (int i = 0; i < 142; i++) {
		for (int j = 0; j < 142; j++) {
			int c = findCross(arr, i, j);
			if (c > 0) {
				count += c;
			}
		}
	}
	return count;
}
int countAll(char arr[142][142]) {
	int count = 0;

	for (int i = 0; i < 142; i++) {
		for (int j = 0; j < 142; j++) {
			if (arr[i][j] == 'X') {
				int c = 0;
				c += p4(arr, i, j, 1, 0);
				c+= p4(arr, i, j, 0, 1);
				c += p4(arr, i, j, 1, 1); 
				c += p4(arr, i, j, 1, -1);
				c += p4(arr, i, j, -1, 1);
				c += p4(arr, i, j, -1, -1);
				c += p4(arr, i, j, -1, 0);
				c += p4(arr, i, j, 0, -1);

				count += c;
			}
		}
	}
	return count;
}

int main() {
	FILE *f = fopen("input.txt", "r");

	if (f == NULL) {
		printf("Error opening file\n");
		exit(1);
	}

	char arr[142][142];

	int i = 0;
	while (i < 142 && fgets(arr[i], 142, f) != NULL) {
		printf("%s", arr[i]);
		i++;
	}

	int** propagation = (int**)malloc(142 * sizeof(int*));
	assert(propagation != NULL);

	for (int i = 0; i < 142; i++) {
		propagation[i] = (int*)malloc(142 * sizeof(int));
		assert(propagation[i] != NULL);
		for (int j = 0; j < 142; j++) {
			propagation[i][j] = 0;
		}
	}

	int c =	countAll(arr);
	int cc = countAllCrosses(arr);
	
	printf("Number of XMAS: %d\n", c);
	printf("NumberOfCrosses: %d\n", cc);

	return 0;
}
