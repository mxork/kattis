#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

int N;
int M;

typedef struct tile {
	bool water;
	bool sea;
} tile;

tile C[1002][1002]; // N, M <= 1000, wrap the map in water

void floodfill(int i, int j) {
	if (i < 0 || i > N+1)
		return;

	if (j < 0 || j > M+1)
		return;

	// mmm. salty land
	if (!C[i][j].water)
		return;

	// already visited
	if (C[i][j].sea)
		return;

	// this is salty
	C[i][j].sea = true;

	floodfill(i+1, j);
	floodfill(i-1, j);
	floodfill(i, j+1);
	floodfill(i, j-1);
}

void production() {
	scanf("%d %d", &N, &M);

	// stupid init
	for (int i=0; i<N+2; i++)
		for (int j=0; j<M+2; j++)
			C[i][j].water = true;

	// read in the map
	for (int i=1; i<=N; i++)
		for (int j=1; j<=M; j++) {
			char here;
			scanf(" %c", &here); // space == skip leading whitespace
			C[i][j].water = (here == '1') ? false : true;
		}

	// flood fill from top
	// left hand corner (guaranteed to reach)
	floodfill(0,0);	
	
	// count the salty nbhrs of land
	long sum = 0;
	for (int i=1; i<=N; i++)
		for (int j=1; j<=M; j++)
			if (!C[i][j].water) {
				sum += C[i+1][j].sea ? 1 : 0;
				sum += C[i-1][j].sea ? 1 : 0;

				sum += C[i][j+1].sea ? 1 : 0;
				sum += C[i][j-1].sea ? 1 : 0;
			}

	printf("%ld\n", sum);
}

int main() {
	production();
	return 0;
}
