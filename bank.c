#include "stdlib.h"
#include "stdio.h"

int N;
int T;

typedef struct person {
	long c;
	int t;
} person;

person P[10000]; // N <= 10000

// dictionary order
int t_cmp(const void* ap, const void* bp) {
	person a = *(person*) ap;
	person b = *(person*) bp;

	if (a.t > b.t)
		return 1;
	if (a.t < b.t)
		return -1;

	return 0;
}

void production() {
	scanf("%d %d", &N, &T);

	for (int i=0; i<N; i++)
		scanf("%ld %d", &P[i].c, &P[i].t);

	qsort(P, N, sizeof(person), t_cmp);

	long long sum = 0;
	int top = N;

	// goin in reverse
	for (int t=T; t>=0; t--) {
		int bottom = 0;

		// find all people who are still here
		for (; bottom<top && P[bottom].t < t; bottom++);
		if (bottom == top) continue;

		// take max of those who are here
		long max = -1; 
		int maxi = -1; 
		for (int i=bottom; i<top; i++)
			if (P[i].c > max) {
				max = P[i].c;
				maxi = i;
			}

		sum += max;
		top--;

		// swap and bubble up - maintain sortedness
		P[maxi] = P[top];
		qsort(P, top, sizeof(person), t_cmp);

//		for (int i=maxi; i<top-1 && P[i].t < P[i+1].t; i++) {
//			person tmp = P[i+1];
//			P[i+1] = P[i];
//			P[i] = tmp;
//		}
	}

	printf("%lld\n", sum);
}

int main() {
	production();
	return 0;
}
