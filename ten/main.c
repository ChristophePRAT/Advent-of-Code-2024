#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_mat(int mat[1000][1000], int lim) {
	for (int i = 0; i < lim; i++) {
		for (int j = 0; j < lim; j++) {
			if (mat[i][j] == 10) {
				printf(". ");
			} else {
				printf("%d ", mat[i][j]);
			}
		}
		printf("\n");
	}
}

int propagation(int mat[1000][1000], int x, int y) {
	// init
	int new_mat[1000][1000];
	int countMap[1000][1000];
	for (int i = 0; i < 1000; i++) {
		for (int j = 0; j < 1000; j++) {
			new_mat[i][j] = mat[i][j];
			countMap[i][j] = 0;
		}
	}
	
	new_mat[x][y] = -1;
	countMap[x][y] = 1;
	int count = 0;

	for (int k = 1; k < 10; k++) {
		for (int i = 0; i < 1000; i++) {
			for (int j = 0; j < 1000; j++) {
				if (new_mat[i][j] == -k) {
					int atSameTime = 0;
					// up
					if (i - 1 >= 0 && mat[i - 1][j] == k) {
						new_mat[i-1][j] = -k-1;
						countMap[i-1][j] = countMap[i-1][j] + countMap[i][j];
						atSameTime += 1;
					}
					// down
					if (i + 1 < 1000 && mat[i + 1][j] == k) {
						new_mat[i+1][j] = -k-1;
						countMap[i+1][j] = countMap[i+1][j] + countMap[i][j];

						atSameTime += 1;
					}
					// left
					if (j - 1 >= 0 && mat[i][j - 1] == k) {
						new_mat[i][j-1] = -k-1;
						countMap[i][j-1] = countMap[i][j-1] + countMap[i][j];

						atSameTime += 1;
					}
					// right
					if (j + 1 < 1000 && mat[i][j + 1] == k) {
						new_mat[i][j+1] = -k-1;
						countMap[i][j+1] = countMap[i][j+1] + countMap[i][j];

						atSameTime += 1;
					}
				}
			}
		}
	}
	print_mat(new_mat, 8);
	print_mat(countMap, 8);
	printf("\n");
	for (int i = 0; i < 1000; i++) {
		for (int j = 0; j < 1000; j++) {
			if (new_mat[i][j] == -10) {
				count += countMap[i][j];
			}
		}
	}
	return count;
}

int doAll(int mat[1000][1000]) {
	int max = 0;
	for (int i = 0; i < 1000; i++) {
		for (int j = 0; j < 1000; j++) {
			if (mat[i][j] == 0) {
				int count = propagation(mat, i, j);
				max += count;
			}
		}
	}
	return max;
}



int main() {
	FILE *f = fopen("input.txt", "r");

	if (f == NULL) {
		printf("Error opening file\n");
		exit(1);
	}

	int mat[1000][1000];
	for (int i = 0; i < 1000; i++) {
		for (int j = 0; j < 1000; j++) {
			mat[i][j] = 10;
		}
	}

	char line[1000];
	int i = 0;

	while (fscanf(f, "%s", line) != EOF) {
		printf("%s\n", line);
		for (int j = 0; j < strlen(line); j++) {
			// get the current character
			char c = line[j];
			// if it's a number, add it to the matrix
			if (c >= '0' && c <= '9') {
				mat[i][j] = c - '0';
			}
		}
		i++;
	}
	print_mat(mat, 8);
	printf("Result: %d\n", doAll(mat));
}
