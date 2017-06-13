#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct rec {
  int hash;
  void* data;
} rec;

rec makerec(char* data) {
  return (rec){*data*2000 + *(data+1), //bad hash
      data
      };
}

rec* min(rec* a,rec* b) {
  return a > b ? b : a;
}
rec* merge(rec*, rec*, rec*, rec*, rec*);

void mergeSort(rec* p, int length) {
     rec* flip = p;

     // working array
     rec* flop = (rec*) malloc(sizeof(rec)*length);

     int chunksize = 1;

     while (chunksize < length) {

       for (int i=0; i<length; i++)
         printf("%d %s\n", flip[i].hash, flip[i].data);
       printf("\n");

          rec* cur = flip;
          rec* end = flip+length;

          rec* into = flop;

          while (cur < end) {
               // TODO these min's are tacky
               into = merge(cur, min(cur+chunksize, end),
                            min(cur+chunksize, end), min(cur+2*chunksize, end),
                            into);

               cur += 2*chunksize;
          }

          chunksize *= 2;

          rec* tmp = flop;
          flop = flip;
          flip = tmp;

          // flip is now the more-sorted one
     }

     for (int i=0; i<length; i++)
       printf("%d %s\n", flip[i].hash, flip[i].data);
     printf("\n");

     // if the original array is not holding the last sorted copy
     // copy it over, and swap one more time
     if (flip != p) {
          memcpy(p, flip, length*sizeof(rec));
          rec* tmp = flop;
          flop = flip;
          flip = tmp;
     }

     free(flop);
}

// merges arrays a,b into output array into. returns pointer
// to end of into.
rec* merge(rec* a, rec* aend, rec* b, rec* bend, rec* into) {
     while (a < aend && b < bend) {
          if (a->hash < b->hash) {
               *into = *a;
               a++;
          } else {
               *into = *b;
               b++; 
          }

          into++;
     }

     // do whichever array was not emptied
     // would probably be better done with memcpy
     while (a < aend) {
          *into = *a;
          a++; into++;
     }

     while (b < bend) {
          *into = *b;
          b++; into++;
     }

     return into;
}

int main() {
  char* A[] = {"happy", "banana", "hoola hoop", "arsenic"};
  rec B[4] = {};

  for (int i=0; i<4; i++)
    B[i] = makerec(A[i]);

  for (int i=0; i<4; i++)
    printf("%d %s\n", B[i].hash, B[i].data);
  printf("\n");

  mergeSort(B, 4);

  for (int i=0; i<4; i++)
    printf("%s\n", B[i].data);

  return 0;
}
