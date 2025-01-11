#include "cache_ro.h"

#ifndef AC_OUTPUT
#define AC_OUTPUT "PASS\n"
#endif

int main() {
  int W, R, N;
  scanf("%d%d%d\n", &W, &R, &N);
  cache_init(W, R);
  char buffer[4096] = {0};
  int num_read = 0;
  while (!feof(stdin)) {
    if (!fgets(buffer, sizeof(buffer), stdin)) {
      break;
    }
    if (buffer[0] == '\n' && buffer[1] == '\0') {
      continue;
    }
    if (buffer[0] == 'R') {
      num_read++;
      uint32_t addr = 0;
      sscanf(buffer, "R%x", &addr);
      uint32_t result = cache_read(addr);
      if (!fgets(buffer, sizeof(buffer), stdin)) {
        printf("FAIL %s\n", buffer);
        return 0;
      }
      if (buffer[0] == 'C') {
        uint32_t expected;
        sscanf(buffer, "CR%x", &expected);
        if (expected != result) {
          printf("FAIL %s\n", buffer);
          return 0;
        }
      } else {
        printf("FAIL %s\n", buffer);
        return 0;
      }
    } else {
      printf("FAIL %s\n", buffer);
      return 0;
    }
  }
  if (num_read != N) {
    printf("FAIL %s\n", buffer);
    return 0;
  }
  printf("%s", AC_OUTPUT);
  return 0;
}

uint32_t memory_read(uint32_t addr) {
  char buffer[4096] = {0};
  if (!fgets(buffer, sizeof(buffer), stdin)) {
    printf("FAIL %s\n", buffer);
    exit(0);
  }
  if (buffer[0] == 'M') {
    uint32_t expected = 0, data = 0;
    sscanf(buffer, "MR%x%x", &expected, &data);
    if (expected != addr) {
      printf("FAIL %s\n", buffer);
      exit(0);
    }
    return data;
  } else {
    printf("FAIL %s\n", buffer);
    exit(0);
  }
}
