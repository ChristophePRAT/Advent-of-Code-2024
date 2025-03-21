#include <stdio.h>
#include "assert.h"
#include <stdlib.h>

void swap(int i, int j, int* list) {
    int temp = list[i];
    list[i] = list[j];
    list[j] = temp;
}

void bubbleSort(int* list, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (list[j] > list[j + 1]) {
                swap(j, j + 1, list);
            }
        }
    }
    for (int i = 0; i < size - 1; i++) {
        assert(list[i] <= list[i + 1]);
    }
}

int max(int a, int b) {
	if (a > b) {
		return a;
	}
	return b;
}

int abs(int i) { 
	if (i < 0) { 
		return -i;
	}
	return i;
}
void printList(int *list, int size) {
	for (int i = 0; i < size; i++) {
		printf("%d ", list[i]);
	}
}

int checkNumber(int num, int* list, int size) {
	int count = 0;

	int index = 0;

	while (list[index] <= num) {
		if (list[index] == num) {
			count += num;
		}
		index++;
	}
	return count;
}

void sbs(int *list1, int *list2, int size) {
	int countDiff = 0;
	for (int i = 0; i < size; i++) {
		int m = abs(list1[i] - list2[i]);
		countDiff += m;
		printf("%d   %d :  %d\n", list1[i], list2[i], countDiff);
	}
}
int main() {
	
	FILE *fptr;
	fptr = fopen("input.txt", "r");

	int lines = 1000;

	int list1[lines] = {};
	int list2[lines] = {};

	int i1;
	int i2;

	int index = 0;
	if (fptr == NULL) {
		printf("ERROR\n");
		printf("file is null\n");
	}

	while (fscanf(fptr, "%d %d\n", &i1, &i2) != -1) {
		list1[index] = i1;
		list2[index] = i2;
		index++;
	}

	
	bubbleSort(list1, lines);
	bubbleSort(list2, lines);
	sbs(list1, list2, lines);

	int sim = 0;

	for (int i = 0; i < lines; i++) {
		sim += checkNumber(list1[i], list2, lines);
	}

	printf("SIM: %d \n", sim);
	fclose(fptr);
	return 0;
}
