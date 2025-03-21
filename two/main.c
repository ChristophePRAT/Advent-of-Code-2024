#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool isValid(int tab[8], int size, int removeIndex) {
	bool decr;
	decr = tab[0] > tab[1];

	if (removeIndex == 0) {
		decr = tab[1] > tab[2];
	} else if (removeIndex == 1) {
		decr = tab[0] > tab[2];
	}

	if (removeIndex == size - 1) {
		size -= 1;
		removeIndex = -1;
	}

	for (int i = 0; i < size - 1; i++) {
		if (removeIndex != i && removeIndex != i+1) {
			if ((decr && tab[i] < tab[i+1]) || (!decr && tab[i] > tab[i+1]) || (abs(tab[i] - tab[i+1]) > 3) || (abs(tab[i] - tab[i+1]) < 1)) {
				return false;
			}
		} else if (removeIndex == i) {
			continue;
		} else if (removeIndex == i+1) {
			if ((decr && tab[i] < tab[i+2]) || (!decr && tab[i] > tab[i+2]) || (abs(tab[i] - tab[i+2]) > 3) || (abs(tab[i] - tab[i+2]) < 1)) {
				return false;
			}
		}
	}
	return true;
}

int abs(int a) {
	if (a > 0) {
		return a;
	} else {
		return -a;
	}
}

int main() {

	FILE *f = fopen("input.txt", "r");

	int tab[8];
	int safeCount = 0;
	int s = 0;
	int index = 0;

	char line[100];

	/*while (fscanf(f, "%d %d %d %d %d %d %d %d\n", &tab[0], &tab[1], &tab[2], &tab[3], &tab[4], &tab[5], &tab[6], &tab[7]) != EOF) {*/
	while (fgets(line, 100, f) != NULL) {
		/*printf("Line: %s\n", line);*/
		int levelNumber = 0;

		char *token = strtok(line, " ");

		while (token != NULL) {
			tab[levelNumber] = atoi(token);
			levelNumber++;
			token = strtok(NULL, " ");
		}

		bool decr = tab[0] > tab[1];
		bool safe = false;
		/*
		for (int i = 0; i < levelNumber - 1; i++) {
			printf("%d ", tab[i+1]);
			if ((decr && tab[i] < tab[i+1]) || (!decr && tab[i] > tab[i+1]) || (abs(tab[i] - tab[i+1]) > 3) || (abs(tab[i] - tab[i+1]) < 1)) {
				printf("____");
				safe = false;
			}
		}
		*/
		
		for (int i = 0; i < levelNumber; i++) {
			safe = safe || isValid(tab, levelNumber, i);
		}

		index++;

		if (safe) {
			printf("SAFE\n");
			safeCount += 1;
		} else {
			printf("NOT SAFE\n");
		}
	}
	printf("Index: %d \n", index);
	printf("%d\n", safeCount);
	fclose(f);
	return 0;
}
