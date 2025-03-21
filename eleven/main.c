#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>

void print(uint64_t **tab, int size) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			printf("%ld ", tab[i][j]);
		}
		printf("\n");
	}
}
void lift(int **tab, int size, int step, int until) {
	for (int i = size - 1; i >= until; i--) {
		tab[i+1][step] = tab[i][step];
	}
}


void operate(uint64_t *tab, uint64_t* size, int step) {
	uint64_t stop = *size;
	for (int i = 0; i < stop; i++) {
		/*printf("Step: %d, i: %d, size: %d\n", step, i, *size);*/
		if (tab[i] == 0) {
			/*printf("Zero\n");*/
			tab[i] = 1; // First rule
		} else {
			int numDigits = floor(log10(tab[i]) + 1);

			if (numDigits % 2 == 0) {

				uint64_t leftHalf = floor(tab[i] / pow(10, floor((1+log10(tab[i])) / 2)));
				uint64_t rightHalf = tab[i] - leftHalf * pow(10, floor((1+log10(tab[i])) / 2));

				tab[i] = leftHalf;
				tab[*size] = rightHalf; // Second rule

				*size = *size + 1;
			} else {
				/*printf("Odd\n");*/
				tab[i] = tab[i] * 2024; // Third rule
			}
		}
	}
}

void print_line(uint64_t *tab, int size) {
	for (int i = 0; i < size; i++) {
		printf("%ld ", tab[i]);
	}
	printf("\n");
}

void ops(uint64_t *tab, int s, int m) {
	uint64_t size = s;

	for (int j = 0; j < m; j++) {
		operate(tab, &size, j);
		if (size > pow(10, 7)) {
			printf("Overflow soon, splitting\n");
			uint64_t *t1 = malloc(size * sizeof(uint64_t *));
			uint64_t *t2 = malloc(size * sizeof(uint64_t *));
		}
	}
	printf("Size: %ld\n", size);
}

int main() {

	char line[1000];
	int i = 0;
	int SIZE = 33554432;
	uint64_t *tab = malloc(SIZE * sizeof(uint64_t *));
	uint64_t *tab2 = malloc(SIZE * sizeof(uint64_t *));
	uint64_t *tab3 = malloc(SIZE * sizeof(uint64_t *));
	uint64_t *tab4 = malloc(SIZE * sizeof(uint64_t *));
	uint64_t *tab5 = malloc(SIZE * sizeof(uint64_t *));
	uint64_t *tab6 = malloc(SIZE * sizeof(uint64_t *));
	uint64_t *tab7 = malloc(SIZE * sizeof(uint64_t *));
	uint64_t *tab8 = malloc(SIZE * sizeof(uint64_t *));


	for (int i = 0; i < SIZE; i++) {
		tab[i] = -1;
		tab2[i] = -1;
		tab3[i] = -1;
		tab4[i] = -1;
		tab5[i] = -1;
		tab6[i] = -1;
		tab7[i] = -1;
		tab8[i] = -1;
	}


	tab[0] = 4022724;
	tab2[0] = 951333;
	tab3[0] = 0;
	tab4[0] = 21633;
	tab5[0] = 5857;
	tab6[0] = 97;
	tab7[0] = 702;
	tab8[0] = 6;
	ops(tab, 1, 75);
	ops(tab2, 1, 75);
	ops(tab3, 1, 75);
	ops(tab4, 1, 75);
	ops(tab5, 1, 75);
	ops(tab6, 1, 75);
	ops(tab7, 1, 75);
	ops(tab8, 1, 75);
}
