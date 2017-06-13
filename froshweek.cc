#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

long N;
long C[1000000]; // N<= 1e6 
long D[1000000]; // N<= 1e6

long mergecount(long *Astart, long *Aend, long *Bstart, long *Bend, long* dst) {
  long* A = Astart;
  long* B = Bstart;
  long nswaps = 0;
  long nB = 0;

  while (A < Aend && B < Bend) {
    if (*A <= *B) {
      *(dst++) = *(A++);
      nswaps += nB;
    }
    else {
      *(dst++) = *(B++);
      nB++;
    }
  }

  // change to memcpy
  memcpy(dst, A, (Aend-A)*sizeof(long));
  nswaps += (Aend-A)*nB; 
  dst += Aend-A;

  memcpy(dst, B, (Bend-B)*sizeof(long));

  return nswaps;
}

void production() {
  scanf("%ld", &N);

  // C = (long int*) malloc(N*sizeof(long));
  // D = (long int*) malloc(N*sizeof(long));

  // unroll
  long k=3;
  for (; k<N; k+=4)
    scanf(" %ld\n%ld\n%ld\n%ld", &C[k-3], &C[k-2], &C[k-1], &C[k]);

  k = N - (N % 4);
  for (; k<N; k++)
    scanf("%ld", &C[k]);

  long nswaps = 0;

  // do first iteration without call to mergecount 
  for (long i=1; i<N; i+=2) {
    if (C[i] < C[i-1]) {
      swap(C[i], C[i-1]);
      nswaps++;
    }
  }

  long chunk = 2;

  long* src = C; 
  long* dst = D; 

  while (chunk < N) {
    for (long i=0; i<N; i += 2*chunk)
      nswaps += mergecount(src+i,               src+min(i+chunk, N),
                           src+min(i+chunk, N), src+min(i+2*chunk, N),
                           dst+i);

    chunk *= 2;
    swap(src, dst);
  }

  cout << nswaps << endl;
}

int main() {
  production();
  return 0;
}
