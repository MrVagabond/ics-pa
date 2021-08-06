#include <klib.h>
#include <stdint.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

size_t strlen(const char *s) {
  size_t res = 0;
  while(s[res] != '\0') res ++;
  return res;
}

char *strcpy(char* dst,const char* src) {
  // The  strcpy()  function  copies  the string pointed to by src, including the terminating null byte ('\0'), to the buffer pointed to by dest.
  int i;
  for(i = 0; src[i]; i ++) {
    dst[i] = src[i];
  }
  dst[i] = '\0';
  return dst;
}

char* strncpy(char* dst, const char* src, size_t n) {
  // The strncpy() function is similar, except that at most n bytes of src are copied.  
  // Warning: If there is no null byte among the first n bytes of src, the string placed in dest will not be null-terminated.
  int i;
  for(i = 0; src[i] && i < n; i ++) {
    dst[i] = src[i];
  }
  if(i < n) {
    dst[i] = '\0';
  } else {
    assert(i == n);
  }
  return dst;
}

char* strcat(char* dst, const char* src) {
  // The  strcat() function appends the src string to the dest string, 
  // overwriting the terminating null byte ('\0') at the end of dest, and then adds a terminating null byte.
  
  int i = 0;
  // while(dst[i ++]); 错误写法，这种写法会让i停在'\0'后一个位置上
  while(dst[i] != '\0') i ++;
  strcpy(dst + i, src);
  return dst;
}

int strcmp(const char* s1, const char* s2) {
  // The strcmp() function compares the two strings s1 and s2. 
  // The locale is not taken into account (for a locale-aware comparison, see strcoll(3)).  
  // It returns an integer less than, equal to, or greater than zero if s1 is found, respectively, to be less than, to match, or be greater than s2.
  int i = 0;
  while(s1[i] && s2[i] && s1[i] == s2[i]) i ++;
  if(s1[i] == s2[i]) return 0;
  else if(s1[i] == '\0') return -1;
  else if(s2[i] == '\0') return 1;
  else return (s1[i] < s2[i] ? -1 : 1);
}

int strncmp(const char* s1, const char* s2, size_t n) {
  // The strncmp() function is similar, except it compares only the first (at most) n bytes of s1 and s2.
  int i = 0;
  while(i < n - 1 && s1[i] && s2[i] && s1[i] == s2[i]) i ++;
  if(s1[i] == s2[i]) return 0;
  else if(s1[i] == '\0') return -1;
  else if(s2[i] == '\0') return 1;
  else return (s1[i] < s2[i] ? -1 : 1);
}

void* memset(void* v,int c,size_t n) {
  // The memset() function fills the first n bytes of the memory area pointed to by v with the constant byte c.
  int i;
  for(i = 0; i < n; i ++) {
    *((uint8_t *)v + i) = (uint8_t)c;
  }
  return v;
}

void* memmove(void* dst,const void* src,size_t n) {
  // The memmove() function copies n bytes from memory area src to memory area dest.
  int i;
  for(i = 0; i < n; i ++) {
    *((uint8_t *)dst + i) = *((uint8_t *)src + i);
  }
  return dst;
}

void* memcpy(void* out, const void* in, size_t n) {
  // The memcpy() function copies n bytes from memory area src to memory area dest.
  return memmove(out, in, n);
}

int memcmp(const void* s1, const void* s2, size_t n) {
  // The memcmp() function compares the first n bytes (each interpreted as unsigned char) of the memory areas s1 and s2.
  // The  memcmp() function returns an integer less than, equal to, or greater than zero
  // if the first n bytes of s1 is found, respectively, to be less than, to match, or be greater than the first n bytes of s2.
  int i;
  uint8_t *ts1 = (uint8_t *)s1;
  uint8_t *ts2 = (uint8_t *)s2;
  for(i = 0; i < n; i ++) {
    if(ts1[i] != ts2[i]) return (ts1[i] < ts2[i] ? -1 : 1);
  }
  return 0;
}

#endif
