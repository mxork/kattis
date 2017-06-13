#include <stdlib.h>
#include <stdio.h>

int intcmp(const void* ap, const void* bp) {
	int a = *(int*)ap;
	int b = *(int*)bp;

	if (a==b)
		return 0;

	if (a<b)
		return -1;

	return 1;
}

int N;
int C[15 + 1];

void production() {
	scanf("%d", &N);

	for (int i=0; i<N; i++)
		scanf("%d", &C[i]);

	// make life a little easier
	qsort(C, N, sizeof(int), intcmp);

	// go!
	int cost=0;
	int a = C[0];
	int b = C[1];
	int M = N;
	for (; M>3;) {
		int optA = a + 2*b + C[M-1];
		int optB = 2*a + C[M-1] + C[M-2];
		cost += optA < optB ? optA : optB;
		M -= 2;
	}

	if (M==3) {
		cost += C[2] + a + b;
	} else {
		cost += b;
	}

	printf("%d\n", cost);
}

int main() {
	production();
	return 0;
}
