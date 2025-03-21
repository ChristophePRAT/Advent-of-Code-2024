#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void print_mat(int **mat, int size) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			printf("%d", mat[i][j]);
		}
		printf("\n");
	}
}

int perim(int i, int j, int **t, int size) {
	int c = 0;

	if (i <= 0 || t[i-1][j] != t[i][j]) {
		c++;
	}
	if (i >= size - 1 || t[i+1][j] != t[i][j]) {
		c++;
	}
	if (j >= size - 1 || t[i][j+1] != t[i][j]) {
		c++;
	}
	if (j <= 0 || t[i][j-1] != t[i][j]) {
		c++;
	}
	return c;
}

int **copyTab(int **t, int s) {
	int **e = malloc(sizeof(int*) * s);
	for (int i = 0; i < s; i++) {
		e[i] = malloc(s * sizeof(int));
		for (int j = 0; j < s; j++) {
			e[i][j] = t[i][j];
		}
	}
	return e;
}
typedef struct point {
	int x;
	int y;
} point;

typedef struct coup {
	int a;
	point sides[100];
	int sideCounts;
} coup;

typedef struct couple {
	int p;
	int a;
} couple;

void addSide(int x, int y, point *sides, int i) {
	for (int j = 0; j < i; j++) {
		if (sides[j].x == x || sides[j].y == y) {
			return;
		}
	}

	sides[i].x = x;
	sides[i].y = y;
}

point* getSides(int **t, int size, int x, int y, int initial) {
	point *sides = malloc(4 * sizeof(point));
	for (int i = 0; i < 4; i++) {
		sides[i] = (point){-1, -1};
	}
	int i = initial;

	if (x <= 0 || t[x-1][y] != t[x][y]) {
		addSide(x - 1, y, sides, i);
		i++;
	}
	if (x >= size - 1 || t[x+1][y] != t[x][y]) {
		addSide(x + 1, y, sides, i);
		i++;
	}
	if (y >= size - 1 || t[x][y+1] != t[x][y]) {
		addSide(x, y + 1, sides, i);
		i++;
	}
	if (y <= 0 || t[x][y-1] != t[x][y]) {
		addSide(x, y - 1, sides, i);
	}

	return sides;
}

coup explor(int **t, int **original, int size, int i, int j, int region) {
	if (i < 0 || i >= size || j < 0 || j >= size || t[i][j] != region) {
		return (coup){0, {}};
	}
	t[i][j] = -region;
	coup a1 = explor(t, original, size, i - 1, j, region);
	coup a2 = explor(t, original, size, i + 1, j, region);
	coup a3 = explor(t, original, size, i, j - 1, region);
	coup a4 = explor(t, original, size, i, j + 1, region);

	// concatenate sides
	point allSides[100];
	for (int k = 0; k < 100; k++) {
		allSides[k] = (point){-1, -1};
	}

	int sideCounts = a1.sideCounts + a2.sideCounts + a3.sideCounts + a4.sideCounts;

	for (int i = 0; i < a1.sideCounts; i++) {
		allSides[i] = a1.sides[i];
	}
	for (int i = 0; i < a2.sideCounts; i++) {
		allSides[i + a1.sideCounts] = a2.sides[i];
	}
	for (int i = 0; i < a3.sideCounts; i++) {
		allSides[i + a1.sideCounts + a2.sideCounts] = a3.sides[i];
	}
	for (int i = 0; i < a4.sideCounts; i++) {
		allSides[i + a1.sideCounts + a2.sideCounts + a3.sideCounts] = a4.sides[i];
	}
	point *sides = getSides(t, size, i, j, sideCounts);
	for (int i = 0; i < sideCounts; i++) {
		allSides[i + sideCounts] = sides[i];
	}

	coup co = {
		.a = 1 + a1.a + a2.a + a3.a + a4.a,
		 /*.sides = allSides,*/
		.sideCounts = sideCounts + 4
	};
	for (int k = 0; k < co.sideCounts; k++) {
		co.sides[k] = allSides[k];
		printf("side %d %d\n", allSides[k].x, allSides[k].y);
	}
	return co;
}

couple explore(int **t, int **original, int size, int i, int j, int region) {
	if (i < 0 || i >= size || j < 0 || j >= size || t[i][j] != region) {
		return (couple){0, 0};
	}
	t[i][j] = -region;
	int p = perim(i, j, original, size);
	couple a1 = explore(t, original, size, i - 1, j, region);
	couple a2 = explore(t, original, size, i + 1, j, region);
	couple a3 = explore(t, original, size, i, j - 1, region);
	couple a4 = explore(t, original, size, i, j + 1, region);

	return (couple) {p + a1.p + a2.p + a3.p + a4.p, 1 + a1.a + a2.a + a3.a + a4.a};
}

int getRegion(int **t, int **original, int size, int rX, int rY) {
	if (t[rX][rY] < 0) {
		return 0;
	}
	int region = t[rX][rY];
	/*int p = perim(rX, rY, original, size);*/
	/*int area = 1;*/

	/*t[rX][rY] = -t[rX][rY];*/

	couple a = explore(t, original, size, rX, rY, region);

	return a.a * a.p;
}
int star2(int **t, int **original, int size, int rX, int rY) {
	if (t[rX][rY] < 0) {
		return 0;
	}
	int region = t[rX][rY];
	/*int p = perim(rX, rY, original, size);*/
	/*int area = 1;*/

	/*t[rX][rY] = -t[rX][rY];*/

	coup a = explor(t, original, size, rX, rY, region);

	int sides = 0;
	for (int i = 0; i < a.sideCounts; i++) {
		if (a.sides[i].x >= 0 && a.sides[i].y >= 0) {
			sides++;
		}
	}
	return a.a * sides;
}
int regionsStar2(int **t, int** ori, int size) {
	int all = 0;

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (t[i][j] > 60) {
				int c = star2(t, ori, size, i, j);

				printf("Region %c: %d \n", -t[i][j], c);
				all += c;
			}
		}
	}
	return all;
}

int regions(int **t, int** ori, int size) {
	int all = 0;


	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (t[i][j] > 60) {
				int c = getRegion(t, ori, size, i, j);

				printf("Region %c: %d \n", -t[i][j], c);
				all += c;
			}
		}
	}
	return all;
}

int main() {
	FILE *f = fopen("input1.txt", "r");

	if (f == NULL) {
		printf("Error opening file\n");
		exit(1);
	}

	char line[1000];
	int **mat = (int **)malloc(1000 * sizeof(int *));

	for (int i = 0; i < 1000; i++) {
		mat[i] = (int *)malloc(1000 * sizeof(int));
		for (int j = 0; j < 1000; j++) {
			mat[i][j] = 0;
		}
	}

	int i = 0;
	while (fgets(line, sizeof(line), f)) {
		for (int j = 0; j < strlen(line); j++) {
			mat[i][j] = line[j];
		}
		i++;
	}
	int **cop = copyTab(mat, 1000);
	fclose(f);
	printf("\n\n\n");

	/*getRegion(mat, cop, 1000, 0,0);*/
	/*int l =regions(mat, cop, 1000); */
	int l = regionsStar2(mat, cop, 1000);
	printf("l = %d\n", l);
	return 0;

}
