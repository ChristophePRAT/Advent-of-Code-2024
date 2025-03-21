#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

bool IsBitSet(uint64_t num, int bit)
{
    return 1 == ( (num >> bit) & 1);
}

int toBase3(int a) {
	int res = 0;
	int i = 0;
	while (a > 0) {
		res += (a % 3) * (1 << i);
		a /= 3;
		i++;
	}
	return res;
}

int getNthDigit(int number, int digit) {
	for (int place = 0; place < digit; place++) number = number / 10;
	return number % 10;
}

void increment(int *tries, int size) {
	tries[0]++;
	for (int i = 0; i < size; i++) {
		if (tries[i] == 3) {
			tries[i] = 0;
			tries[i + 1]++;
		}
	}
}

bool backtrackCorrect(long int res, long int nums[30], int size) {
	uint64_t trial = 0;
	uint64_t max = pow(3, size + 10);
	int *tries = malloc(sizeof(int) * (size + 1));
	for (int i = 0; i < size + 1; i++) {
		tries[i] = 0;
	}

	while (tries[size] == 0) {
		uint64_t total = nums[0];

		for (int i = 1; i < size; i++) {
			if (tries[i] == 0) {
				total += nums[i];
			} else if (tries[i] == 1) {
				total *= nums[i];
			} else {
				total = total * pow(10, (1 + (floor(log(nums[i])/log(10))))) + nums[i];
			}

			if (total > res) {
				/*return backtrackCorrect(res, nums, size, trial + 1);*/
				increment(tries, size);
				break;
			}
		}
		if (total != res) {
			increment(tries, size);
		} else {
			return true;
		}
	}
	return false;
}

int main() {
	FILE *f = fopen("input.txt", "r");

	long int count = 0;

	long int res = 0;
	long int nums[30];

	char line[2000];
	char l2[2000];
	char *pch;
	char *pch2;
	while (fgets(line, 2000, f) != NULL) {
		strcpy(l2, line);

		pch = strtok(l2, ":");
		if (pch != NULL) {
			res = strtol(pch, NULL, 10);
			printf("res: %llu\n", res);
		}

		pch2 = strtok(line, ": ");

		pch2 = strtok(NULL, " ");

		int i = 0;
		while (pch2 != NULL) {
			nums[i] = strtol(pch2, NULL, 10);
			pch2 = strtok(NULL, " ");
			i++;
		}
		if (backtrackCorrect(res, nums, i)) {
			count += res;
		}
	}

	printf("count: %llu\n", count);
	
	return 0;
}
