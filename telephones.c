#include "stdlib.h"
#include "stdio.h"
#include "stdbool.h"
#include "string.h"

typedef struct interval {
	long start;
	long end;
} interval;

int N;
int M;
interval I[10000]; // N<10000
interval J[100];   // M<100

int main() {
	while (scanf("%d %d", &N, &M), N && M) {
		int crap; int crap2; int start; int dur;

		// read in all calls
		for (int i=0; i<N; i++) {
			scanf("%d %d %d %d", &crap, &crap2, &start, &dur);
			I[i].start=start; 
			I[i].end=start+dur;
		}

		// read in all surveils
		for (int i=0; i<M; i++) {
			scanf("%d %d", &start, &dur);
			J[i].start=start; 
			J[i].end=start+dur;
		}

		// build interval tree
		// ... or not. Gonna try naive impl.
		
		for (int j=0; j<M; j++) {
			int cnt=0;

			for (int i=0; i<N; i++)
				if ( J[j].start < I[i].end && J[j].end > I[i].start)
					cnt++;

			printf("%d\n", cnt);
		}
	}
	return 0;
}
