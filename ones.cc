#include <cstdio>

int main() {
	long N;
	while (scanf("%ld", &N) > 0) {
		int cnt = 1;
		unsigned long long int c = 1;

		while(1) {
			if (c % N == 0) {
				printf("%d\n", cnt);	
				break;
			}

			cnt++;
			c = (10*c +1) % N;
		}
	}
	
	return 0;
}
