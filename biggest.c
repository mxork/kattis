#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

long PIs = 360*60*60/2;
long PI2s = 360*60*60;

bool C[360*60*60];

inline double area(double r, long arc) {
  return  3.14159265359 * r*r * ((double) arc / (double) PI2s);
}

// urgh. linear time solution in N, very naive.
void production() {
  int M;
  scanf("%d", &M); // M<=200

  for (int mi=0; mi<M; mi++) {
    double R; long N;
    int deg; int min; int sec;
    scanf("%lf %ld %d %d %d", &R, &N, &deg, &min, &sec);

    long H = 60*60*deg + 60*min + sec;

    for (long i=0; i<PI2s; i++)
      C[i] = false; 

    // there's actually a better bound
    N = N > PI2s ? PI2s : N;

    long j=0;
    for (long i=0; i<N; i++)
      C[i*H % PI2s] = true; 

    long arc = 1;
    long last = 0;
    for (long i=1; i<PI2s; i++)
      if (C[i]==true) {
        if (i - last > arc)
          arc = i-last;

        last = i;
      }

    if (PI2s - last > arc)
      arc = PI2s-last;

    printf("%lf\n", area(R, arc) );
  }
}

int main() {
  production();
  return 0;
}
