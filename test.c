#include <stdio.h>
#include <stdlib.h>

int longcmp(const void* ap, const void* bp) {
  long diff = *(long*)ap - *(long*)bp;
	return  diff < 0 ? -1 :
    diff > 0 ?  1 :
    0;
}

long N;
long C[1000000];

int main() {
  scanf("%ld", &N);
  for (long i=0; i<N; i++)
    scanf("%ld", &C[i]);

  qsort(C, N, sizeof(long), longcmp);
  return 0;
}
