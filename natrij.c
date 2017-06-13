#include <stdlib.h>
#include <stdio.h>

void production() {
  int hr; int min; int sec;

  scanf("%d:%d:%d", &hr, &min, &sec);
  long start = 60*60 * hr + 60*min + sec;

  scanf("%d:%d:%d", &hr, &min, &sec);
  long end = 60*60 * hr + 60*min + sec;

  long diff;
  if (end > start)
    diff = end-start;
  else
    diff = (24*60*60 - start) + end;

  hr = diff/60/60;
  min = (diff % 3600) / 60;
  sec = (diff % 60);

  printf("%02d:%02d:%02d\n", hr, min, sec);
}

int main() {
  production();
  return 0;
}
