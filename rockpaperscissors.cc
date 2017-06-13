#include <iostream>
#include <algorithm>
#include <cstdio>

int W[100]; // N<=100
int L[100]; // N<=100

void production() {
	int N; int K;
	int first_time = 1;

	while (scanf("%d %d", &N, &K) == 2) {
		if (!first_time) {
			printf("\n");
		}

		first_time = 0;

		// init nonsense
		for (int i=0; i<100; i++)
			W[i] = L[i] = 0;
			
		// input
		for (int i=0; i<K*N*(N-1)/2; i++) {
			int p1; int p2; 
			char m1[10]; char m2[10];

			scanf("%d %s %d %s", &p1, &m1, &p2, &m2);

			char m1d = m1[0]; // r, p, s
			char m2d = m2[0];

			// off by one from input
			p1--;
			p2--;

			// no win
			if (m1d == m2d) continue;

			// messy bullshit
			switch (m1d) {
			case 'r':
				if (m2d == 's') {
					W[p1]++;
					L[p2]++;
				} else {
					L[p1]++;
					W[p2]++;
				}
				break;
			case 'p':
				if (m2d == 'r') {
					W[p1]++;
					L[p2]++;
				} else {
					L[p1]++;
					W[p2]++;
				}
				break;
			case 's':
				if (m2d == 'p') {
					W[p1]++;
					L[p2]++;
				} else {
					L[p1]++;
					W[p2]++;
				}
				break;
			}
		}

		for (int i=0; i<N; i++) {
			if (W[i] + L[i] == 0) {
				printf("-\n");
				continue;
			}
			printf("%.3f\n", ((double) W[i]) / ((double) (W[i] + L[i])));
		}
	}
}

int main() {
	production();
	return 0;
}
