#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

// customary values
#define IMP -1
#define AMB -2

// globals
int N;
int C[104];
int M;
int S[1004];
int memo[30004];

// returns index of next item in order for total s
// ibid, but without memo
int next_item(int);
int next_item_raw(int);

int next_item(int s) {
     if (memo[s] || s==0)
          return memo[s];
     else
          return memo[s] = next_item_raw(s);
}

int next_item_raw(int s) {
     assert(s>0);

     // try packing in other orders
     int ret = 0;
     for (int i=1; i<N; i++) {
          int cost = C[i];
          int nxt_s = s-C[i];

          // doesn't fit
          if (nxt_s < 0)
               break;

          // fits just right 
          if (nxt_s == 0)
               goto SOLN;

          // recur
          int nxt = next_item(nxt_s);

          if (nxt == IMP)
               continue;

          if (nxt == AMB)
               return AMB;

          assert(nxt>0);

          // permutation check; if the next pointed to
          // index is less than our current one, then
          // we will have already attempted an equiv. perm.
          // note == to is just fine, since we allow repeats.
          if (nxt < i)
               continue;

     SOLN: if (ret)
               return AMB;
          else
               ret=i;
     }

     return ret ? ret : IMP;
}

void production() {
     // menu
     scanf("%d\n", &N);
     N++;
     for (int i=1; i<N; i++)
          scanf("%d", &C[i]);

     // orders
     scanf("%d\n", &M);
     for (int i=0; i<M; i++)
          scanf("%d", &S[i]);

     // GO!
     for (int i=0; i<M; i++) {
          int cost = S[i];

          switch ( next_item(cost) ) {
          case IMP:
               printf("Impossible");
               break;
          case AMB:
               printf("Ambiguous");
               break;
          default:
               while (cost) {
                    int it = next_item(cost);
                    assert(it>0);
                    assert( it<=next_item(cost-C[it]) || (cost-C[it] == 0) );

                    printf("%d ", it);
                    cost -= C[it];
                    assert(cost>=0);
               }
          }

          printf("\n");
     }

}
int main() {
     production();
     return 0;
}
