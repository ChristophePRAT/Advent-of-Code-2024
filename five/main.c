#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


int verifyForPrint(int p[30], int size, int rules[1175*2]) {
	/*printf("p0: %d\n", p[0]);*/
	for (int i = 0; i < 1175; i++) {
		// for each rule
		bool secApp = false;
		bool legit = true;
		for (int j = 0; j < size; j++) {
			// for each # in print
			if (p[j] == rules[2*i]) {
				if (secApp) {
					legit = false;
				}
			} else if (p[j] == rules[2*i+1]) {
				secApp = true;
			}
		}
		if (!legit) {
			return 0;
		}
	}
	printf("Added %d\n", p[(size - 1)/2]);
	return p[(size - 1)/2];
}

int verif(int *p, int s, int rules[1175*2]) {
	int c = verifyForPrint(p, s, rules);
	
	if (c != 0) {
		return 0;
	}

	for (int i = 0; i < 1175; i++) {
		// for each rule
		int secApp = -1;
		bool legit = true;
		for (int j = 0; j < s; j++) {
			// for each # in print
			if (p[j] == rules[2*i]) {
				if (secApp != -1) {
					int temp = p[j];
					p[j] = p[secApp];
					p[secApp] = temp;

					/*legit = false;*/
					int newC = verifyForPrint(p, s, rules);
					if (newC != 0) {
						return newC;
					} else {
						return verif(p, s, rules);
					}
				}
			} else if (p[j] == rules[2*i+1]) {
				secApp = j;
			}
		}
	}
	/*printf("Added %d\n", p[(s- 1)/2]);*/
	return c;
}
int main() {
	FILE *f = fopen("rules.txt", "r");

	if (f == NULL) {
		printf("Error opening file\n");
		exit(1);
	}

	int rules[1176*2];
	int i = 0;
	int a, b;
	while (fscanf(f, "%d|%d", &a, &b) != -1) {
		rules[2*i] = a;
		rules[2*i+1] = b;
		printf("Rules: %d %d \n", rules[2*i], rules[2*i+1]);
		i++;
	}
	fclose(f);

	FILE *f2 = fopen("prints.txt", "r");

	if (f2 == NULL) {
		printf("Error opening file\n");
		exit(1);
	}
	char line[400];
	char *pch;

	int count = 0;
	while (fgets(line, 400, f2) != NULL) {
		/*printf("Line: %s\n", line);*/
		pch = strtok(line,",");
		int p[30];
		int j = 0;
		while (pch != NULL) {
			p[j] = atoi(pch);
			/*printf("%d ", p[j]);*/
			pch = strtok(NULL, ",");
			j++;
		}
		count += verif(p, j, rules);
		printf(".\n");
	}

	printf("COUNT: %d\n", count);

	return 0;
}
