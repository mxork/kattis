#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int N;
long A[202];
long* B;

long X[202];
long* Y;

int best() {
  // clone!
  memcpy(X, A, sizeof(long)*202);
    
  // floor and ceiling
  int f = 1;
  int c = 100;
  int sup = 0;

  // reduce
  while (f <= 100 && c >= 1) {
    if (A[f]==0) {
      f++;
      continue;
    } 
    if (B[c]==0) {
      c--;
      continue;
    }

    // neither zero
    sup = sup > f+c ? sup : f+c;

    // kerchunk
    if (X[f] < Y[c]) {
      Y[c] -= X[f++];
    } else
    if (X[f] > Y[c]) {
      X[f] -= Y[c--];
    } else  {
      f++; c--;
    }

  } 

  return sup;
}

void production() {
  B = &A[101];
  Y = &X[101];

  scanf("%d", &N);

  int a; int b;
  for (int i=0; i<N; i++) {
    scanf("%d %d", &a, &b);
    A[a]++;
    B[b]++;
    printf("%d\n", best());
  }

}

int main() {
  production();
  return 0;
}
