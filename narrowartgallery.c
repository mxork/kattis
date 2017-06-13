#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

int gogo(int, int, int);
int gogo_raw(int, int, int);

int N;
int K;

// rooms - using interleaved scheme
int R[402] = {0};

int min(int a, int b) {
	return a < b ? a : b;
}

#define ONE_MILLION 100000
#define NOTDONE -1
#define LEFT 0
#define NEITHER 1
#define RIGHT 2

int memo[201][3][201] = {NOTDONE};
int gogo(int row, int prev, int k) {
	assert( 0 <= row && row <= N);
	assert( k >= 0  && k <= K);

	if (memo[row][prev][k] != NOTDONE)
		return memo[row][prev][k];
	else
		return memo[row][prev][k] = gogo_raw(row, prev, k);
}

int gogo_raw(int row, int prev, int k) {
	if (k==0) return 0;
	if (k>N-row) return ONE_MILLION;

	int neither_min = gogo(row+1, NEITHER, k);

	// can't choose left if last was right
	int left_min = 
		(prev == RIGHT) ? ONE_MILLION : R[2*row] + gogo(row+1, LEFT, k-1);

	// can't choose right if last was left
	int right_min = 
		(prev == LEFT) ? ONE_MILLION : R[2*row+1] + gogo(row+1, RIGHT, k-1);

	int inf = min(left_min, right_min);
	inf = min(inf, neither_min);

	assert(inf>=0);
	return inf;
}

void production () {
	for (int i=0; i<201; i++)
		for (int j=0; j<3; j++)
			for (int k=0; k<201; k++)
				memo[i][j][k] = NOTDONE;

	scanf("%d %d\n", &N, &K);
	int total_value=0;
	for (int i=0; i<2*N; i+=2) {
		scanf("%d %d", &R[i], &R[i+1]);
		total_value += R[i]+R[i+1];
	}

	// total value is cuz I tracked min instead of max
	int ans = total_value- gogo(0, NEITHER, K);
	assert(ans >= 0);
	printf("%d\n", ans );
}

int main() {
	production();
	return 0;
}
