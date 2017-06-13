#include <stdlib.h>
#include <stdio.h>

int intcmp(const void* ap, const void* bp) {
	int a = *(int*)ap; int b = *(int*)bp;
	return a < b ? -1 : a > b ? 1 : 0; 	
}

int nearest(int* S, int len, int x) {
	int* L = S;
	int* R = S+len-1;

	while (R-L > 1) {
		int* C = L + (R-L)/2;

		if (*C == x)
			return x;

		if (x > *C) L = C; 
		else R = C;
	}

	if ( (*R - x) < (x - *L) )
		return *R;
	else
		return *L;
}

void main() {
	int A[1000];
	int B[25];
	int S[(1000*999)/2];
	int N;
	int M;

	for (int caseno=1; scanf("%d\n", &N) > 0; caseno++) {
		for (int i=0; i<N; i++)
			scanf("%d\n", &A[i]);

		scanf("%d", &M);
		for (int i=0; i<M; i++)
			scanf("%d\n", &B[i]);

		qsort(A, N, sizeof(int), &intcmp);

		int cnt = 0;
		for (int i=0; i<N; i++)
			for (int j=i+1; j<N; j++)
				S[cnt++] = A[i]+A[j];

		int NS = N*(N-1)/2; 
		qsort(S, NS, sizeof(int), &intcmp);

		printf("Case %d:\n", caseno);
		for (int i=0; i<M; i++)
			printf("Closest sum to %d is %d.\n", B[i], nearest(S, NS, B[i]));
	}

	return 0;
}
