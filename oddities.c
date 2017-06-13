#include "stdio.h"

int main() {
    int NOTESTS;
    int x;
    int y;
    char* paritystr;
    char* oddstr = "odd";
    char* evenstr = "even";
    
    scanf("%d", &NOTESTS);
    
    while(scanf("%d", &x) >= 0) {
        y = (x<0) ? -x : x; // cuz negative is never the mathematical definition of mod
        paritystr = (y%2) ? oddstr : evenstr;
        
        printf("%d is %s\n", x, paritystr);
    }
    return 0;
}
