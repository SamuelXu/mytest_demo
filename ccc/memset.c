#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void* mymemset(void* b, int c, size_t len)
{
  uint64_t mem = c|c<<8;
  mem |= mem<<16;
  mem |= mem<<32;

  size_t pad = len % 8;
  for(int i=0;i<pad;i++) {
    *(char*)(b+i) = c;
  }
  uint64_t* tmp = b+pad;
  size_t times = (len-pad) / 8;
  if(times == 0) return b;
  switch(times % 8) {
    do {
      default:
        *tmp = mem;tmp++;
        times--;
      case 7:
        *tmp = mem;tmp++;
        times--;
      case 6:
        *tmp = mem;tmp++;
        times--;
      case 5:
        *tmp = mem;tmp++;
        times--;
      case 4:
        *tmp = mem;tmp++;
        times--;
      case 3:
        *tmp = mem;tmp++;
        times--;
      case 2:
        *tmp = mem;tmp++;
        times--;
      case 1:
        *tmp = mem;tmp++;
        times--;
    } while (times != 0);
  }
  return b;
}
#include <string.h>
int main() {
  char* a = (char*)malloc(16);
  *(a+16) = 0;
  mymemset(a, 'F', 15);
  printf("%s\n", a);
  return 0;
}
