#include "stdlib.h"
#include "stdio.h"
#include "stdbool.h"
#include "string.h"
#include "assert.h"

void encrypt(char* T, char* S, int* K, int n) {
  while (*S) {
    for (int i=0; i<n; i++)
      T[i] = S[K[i]-1];

    T+=n; S+=n;
  }
  *T = *S;
  assert(*T == '\0');
}

void test() {
  char* A[] = {"applesauce", "dog", "hill", "happy", "hilarious",
               "yassine", "keyboard", "pictures", "actors", "unit",
               "bootstrap", "Pochhammer", "Ramanujan"}; 
}

void production() {
  int n;
  int K[21];
  char* S = malloc(2<<26);
  char* T = malloc(2<<26);

  while (scanf("%d", &n) > 0 && n > 0) {
    //read in key
    for (int i=0; i<n; i++)
      scanf("%d", &K[i]);

    fgets(S, 8, stdin); // consume past newline
    fgets(S, 2<<26, stdin);

    // chomp
    int m = strlen(S);
    S[m-1] = '\0';
    m = strlen(S);

    //pad things out
    if (m%n > 0) {
      int defect = n-(m%n);
      for (int i=m; i< m+defect; i++)
        S[i] = ' ';
      S[m+defect] = '\0';
    }

    assert(strlen(S)%n == 0);

    //encrypt
    encrypt(T, S, K, n);
    printf("'%s'\n", T);
  }

  free(S); free(T);
}

int main() {
  production();
  /* test(); */
  return 0;
}
