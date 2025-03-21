#include <stdio.h>

void rec(int n) {
		printf("n = %d\n", n);
		rec(n + 1);
}


int main() {
		int n = 5;
		rec(n);
		return 0;
}
