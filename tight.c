#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

int K;
int N;
// 100 for N, 9+1 for possible digit range, +2 for padding
double Y[100][9+3]={0};

void production() {
	// padding it out
	double* X[100];
	for (int i=0; i<100; i++)
		X[i] = &(Y[i][1]);

	while(scanf("%d %d", &K, &N) > 0) {
		// special case... could prob delete
		if (K==0) {
			printf("%f\n", 100.0);
			continue;
		}

		// ordinary
		for (int i=0; i<=K; i++)
			X[0][i] = 1;

		X[0][-1] = X[0][K+1] = 0;

		for (int i=1; i<N; i++) {
			for (int j=0; j<=K; j++)
				X[i][j] = X[i-1][j-1] + X[i-1][j] + X[i-1][j+1];
			X[i][-1] = X[i][K+1] = 0;
		}

		double num = 0;
		for (int i=0; i<=K; i++)
			num += X[N-1][i];

		double denom = pow(K+1, N);

		printf("%.12f\n", 100.0*num/denom);
	}
}

int main() {
	production();
	return 0;
}
