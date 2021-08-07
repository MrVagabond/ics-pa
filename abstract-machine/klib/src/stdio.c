#include <am.h>
#include <klib.h>
#include <klib-macros.h>
#include <stdarg.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

// printf() write output to stdout, the standard output stream;
// sprintf(), snprintf(), vsprintf() and vsnprintf() write to the character string str.
static char buffer[2048];

int puts(const char *str) {
  for(int i = 0; str[i]; i ++) putch(str[i]);
  return 0;
}

int printf(const char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  int ret = sprintf(buffer, fmt, ap);
  va_end(ap);
  puts(buffer);
  return ret;
}

int vsprintf(char *out, const char *fmt, va_list ap) {
  return 0;
}

int sprintf(char *out, const char *fmt, ...) {
  buffer[0] = '\0';
  va_list ap;
  va_start(ap, fmt);

  // 一些flags
  int i = 0; // 始终指向下一个未读取的字符 
  int j = 0; // 始终指向下一个输出的位置
  int total = 0;
  int f_norm = 1; // 普通模式，在该模式下直接输出读取的字符
  int get_num = 0; // 是否在参数模式下获取接下来的所有数字

  // 一些临时变量
  int v;
  unsigned int u;
  char *str;
  
  while(fmt[i]) {
    /*puts("i j fmt[i] buffer is ");
    puts(itoa(i));
    puts(", ");
    puts(itoa(j));
    puts(", '");
    putch(fmt[i]);
    puts("', ");
    puts(buffer);
    puts("\n");
    */
    if(f_norm && fmt[i] == '%') f_norm = 0;
    if(f_norm) {
      buffer[j] = fmt[i];
      i ++, j ++, buffer[j] = '\0';
    } else {
      while(!f_norm) {
        switch(fmt[i]) {
          case '%': i ++; break;
          case 'd':
            v = va_arg(ap, int);
            strcat(buffer, itoa(v));
            f_norm = 1, total ++, i ++, j += strlen(itoa(v)); // 设置标志
            break;
          case 's':
            str = va_arg(ap, char *);
            strcat(buffer, str);
            f_norm = 1, total ++, i ++, j += strlen(str); // 设置标志
            break;
          case 'x':
            u = va_arg(ap, unsigned int);
            strcat(buffer, hextoa(u));
            f_norm = 1, total ++, i ++, j += strlen(hextoa(u)); // 设置标志
            break;
          case '0': // 填充u个0
            get_num = 1;
            u = 0;
            i ++;
            while(get_num) {
              if(isdigit(fmt[i])) {
                u = u * 10 + (fmt[i] - '0');
              } else {
                get_num = 0;
              }
              putch('n');
            }
            while(u) {
              buffer[j] = '0';
              j ++;
              u --;
              putch('u');
            }
            i ++; // 设置标志
            break;
          default: puts("in klib sprintf, not implement '"); putch(fmt[i]); puts("': "); assert(0);
        }
      }
    }
  }
  strcpy(out, buffer);

  return total;
}

int snprintf(char *out, size_t n, const char *fmt, ...) {
  return 0;
}

int vsnprintf(char *out, size_t n, const char *fmt, va_list ap) {
  return 0;
}

#endif
