#include <cstdio>
#include <cstring>

char C[2000000];

void production() {
	while (scanf("%s", C) > 0) {
		if (C[0]=='.')
			break;

		long n = 1;
		long N = strlen(C);
		long M = N;
		long largest = 1;

		while (n<=N) {
			n++;
			if (N % n != 0)
				continue;

			long m = N/n;

			for (long i=1; i<n; i++) 
				for (long j=0; j<m; j++) 
					if (C[j] != C[i*m + j]) 
						goto skip;
					
			// otherwise
			N /= n;
			largest *= n;
			n = 1;

			skip:
			int x =0; // null op
		}

		printf("%ld\n", largest);
	}
}

int main() {
	production();
	return 0;	
}
