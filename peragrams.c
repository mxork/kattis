#include <stdlib.h>
#include <stdio.h>

int min_to_gram(char* S) {
	char LC[26];
	for (int i=0; i<26; i++)
		LC[i] = 0;

	char* cur = S;
	while (*cur)
		LC[*cur++ - 'a']++;

	int sum = 0;
	for (int i=0; i<26; i++)
		sum += LC[i]%2;

	return sum ? sum-1 : sum;
}

void main() {
	char S[2<<10];	
	while (scanf("%s", S)>0)
		printf("%d\n", min_to_gram(S) );
}
