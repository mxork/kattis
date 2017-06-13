#include <stdio.h>

int main() {
  int N; int P;
  int A[100000];

  //input
  scanf("%d %d\n", &N, &P);

  for (int i=0; i<N; i++)
    scanf("%d", &A[i]);

  // adjust
  for (int i=0; i<N; i++)
    A[i] -= P;

  // Kadane's
  int cur=0; int max=0;
  for (int i=0; i<N; i++) {
    cur = 0 > cur+A[i] ? 0 : cur+A[i];
    max = cur > max ? cur : max;
  }

  // answer
  printf("%d\n", max);

  return 0;
}
