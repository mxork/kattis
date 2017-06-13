#include "stdio.h"

int sumdigits(int x) {
    int sum = 0;
    while (x>0) {
      sum += x % 10;
      x /= 10;
    }
   
   return sum;
}

int findmin(int x) {
    for (int p=11; p<100000; p++)
        if (sumdigits(x) == sumdigits(x*p))
            return p;
}

int main() {
    int x;

    while (scanf("%d", &x) >= 0) {
        printf("%d\n", sumdigits(x));
        printf("%d\n", findmin(x));
    }
    
    return 0;
}
