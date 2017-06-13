#include <stdio.h>
#include <stdlib.h>

void production() {
	int H;

	scanf("%d ", &H);

	char c;
	int l = 1;

	while(c = getc(stdin), c == 'L' || c == 'R') {
		l <<= 1;
		if (c=='R')
			l += 1;
	}

	printf("%d\n", (1<<(H+1)) - l);
}

int main() {
	production();
	return 0;
}
