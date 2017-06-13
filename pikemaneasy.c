#include "stdlib.h"
#include "stdio.h"

int intcmp(const void* ap, const void* bp) {
	long long a = *(long long*)ap;
	long long b = *(long long*)bp;

	if (a==b)
		return 0;

	if (a<b)
		return -1;

	return 1;
}

int N;
long long Tot;

long A;
long B;
long C;
long long T[10000]; // N <= 10^4

int production() {
	scanf("%d %lld", &N, &Tot);
	scanf("%ld %ld %ld %lld", &A, &B, &C, &T[0] );
	
	for (int i=1; i<N; i++) {
		T[i] = (( A*T[i-1] + B ) % C ) + 1;
	}

//	for (int i=0; i<N; i++)
//		printf("%d ", T[i]);
//	printf("\n");

	// SHBORTING TIME
	qsort(T, N, sizeof(long long), intcmp);

	int cnt = 0;
	long long total_penalty = 0;
	long long total_time = 0;

	for (; cnt<N; cnt++) {
		long long new_time = total_time + T[cnt];
		long long new_penalty = (total_penalty + new_time) % 1000000007;

		if (new_time > Tot) {
			break;
		}

		total_time = new_time;
		total_penalty= new_penalty;
	}

//	for (int i=0; i<N; i++)
//		printf("%d ", T[i]);
//	printf("\n");

	printf("%d %lld\n", cnt, total_penalty);
	return 0;
}

int main() {
	return production();
}

