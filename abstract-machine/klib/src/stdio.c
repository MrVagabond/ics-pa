#include <am.h>
#include <klib.h>
#include <klib-macros.h>
#include <stdarg.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

// printf() write output to stdout, the standard output stream;
// sprintf(), snprintf(), vsprintf() and vsnprintf() write to the character string str.
static char buffer[2048];


int printf(const char *fmt, ...) {
  return 0;
}

int vsprintf(char *out, const char *fmt, va_list ap) {
  return 0;
}

int sprintf(char *out, const char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);

  int i = 0; // 始终指向下一个未读取的字符 
  int j = 0; // 始终指向下一个输出的位置
  // 一些flags
  int f_norm = 1; // 普通模式，在该模式下直接输出读取的字符

  // 一些临时变量
  int v;
  
  while(fmt[i]) {
    if(fmt[i] == '%') f_norm = 0;
    if(f_norm) {
      out[j] = fmt[i];
      i ++, j ++;
    } else {
      switch(fmt[i]) {
        case '%': i ++; break;
        case 'd':
          v = va_arg(ap, int);
          strcat(buffer, itoa(v));
          f_norm = 1;
          break;
        case 's':
          strcat(buffer, va_arg(ap, char *));
          f_norm = 1;
          break;
        default: assert(0);
      }
    }
  }

  return 0;
}

int snprintf(char *out, size_t n, const char *fmt, ...) {
  return 0;
}

int vsnprintf(char *out, size_t n, const char *fmt, va_list ap) {
  return 0;
}

#endif
