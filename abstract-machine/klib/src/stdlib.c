#include <am.h>
#include <klib.h>
#include <klib-macros.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)
static unsigned long int next = 1;

int rand(void) {
  // RAND_MAX assumed to be 32767
  next = next * 1103515245 + 12345;
  return (unsigned int)(next/65536) % 32768;
}

void srand(unsigned int seed) {
  next = seed;
}

int abs(int x) {
  return (x < 0 ? -x : x);
}

int atoi(const char* nptr) {
  int x = 0;
  while (*nptr == ' ') { nptr ++; }
  while (*nptr >= '0' && *nptr <= '9') {
    x = x * 10 + *nptr - '0';
    nptr ++;
  }
  return x;
}

static char buf1[1024];
static char buf2[1024];
char *itoa(int n) {
  if(n == 0) {
    buf1[0] = '0';
    buf1[1] = '\0';
    return buf1;
  }
  int i = 0;
  if(n < 0) {
    buf1[i] = '-';
    i ++;
  }
  n = abs(n);

  int j;
  for(j = 0; n; j ++) {
    buf2[j] = (n % 10) + '0';
    n /= 10;
  }
  j --;
  for(; j >=0; ) buf1[i] = buf2[j], i ++, j --;
  buf1[i] = '\0';
  puts("itoa output: ");
  puts(buf1);
  puts("\n");
  return buf1;
}

char *hextoa(unsigned int n) {
  if(n == 0) {
    buf1[0] = '0';
    buf1[1] = '\0';
    return buf1;
  }
  int i = 0;
  int j;
  for(j = 0; n; j ++) {
    int t = n % 16;
    buf2[j] = t < 10 ? t + '0' : t - 10 + 'a';
    n /= 16;
  }
  j --;
  for(; j >= 0; ) buf1[i] = buf2[j], i ++, j --;
  buf1[i] = '\0';
  // puts(buf1);
  return buf1;
}

int isdigit(char c) {
  return '0' <= c && c <= '9';
}

void *malloc(size_t size) {
  return NULL;
}

void free(void *ptr) {
}

#endif
