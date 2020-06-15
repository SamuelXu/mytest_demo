#include <stdio.h>
#include <stdlib.h>

#define MEM_SIZE_ALIGN(x) (((x) & (sizeof(long) - 1)) ? (((x) + sizeof(long)) & ~(sizeof(long) - 1)) : (x))
#include "jemalloc/jemalloc.h"

class Base {
public:
  int x_;
  virtual ~Base() = default;
protected:
  Base() {};
};

class Derived : public Base {
public:
  Derived(int x) {x_ = x;}
  int getx() { return x_; }
};

int main(int argc, char* argv[])
{
  Derived d(20);
//  printf("%d\n", d.getx());

  int s = MEM_SIZE_ALIGN(atoi(argv[1]));
  printf("%d %d\n", sizeof(long), s);

  void* ptr = je_malloc(12);
  printf("%d\n", je_malloc_usable_size(ptr));

  uint64_t epoch = 1;
  size_t sz;
  size_t allocated , resident , active;
  allocated = resident = active = 0;
  /* Update the statistics cached by mallctl. */
  sz = sizeof(epoch);
  je_mallctl("epoch", &epoch, &sz, &epoch, sz);
  sz = sizeof(size_t);
  /* Unlike RSS, this does not include RSS from shared libraries and other non
   ** heap mappings. */
  je_mallctl("stats.resident", &resident, &sz, NULL, 0);
  printf("%d\n", resident);
  /* Unlike resident, this doesn't not include the pages jemalloc reserves
   ** for re-use (purge will clean that). */
  je_mallctl("stats.active", &active, &sz, NULL, 0);
  printf("%d\n", active);
  /* Unlike zmalloc_used_memory, this matches the stats.resident by taking
   ** into account all allocations done by this process (not only zmalloc). */
  je_mallctl("stats.allocated", &allocated, &sz, NULL, 0);
  printf("%d\n", allocated);

  return 0;
}
