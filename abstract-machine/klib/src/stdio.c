#include <am.h>
#include <klib.h>
#include <klib-macros.h>
#include <stdarg.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

// printf() write output to stdout, the standard output stream;
// sprintf(), snprintf(), vsprintf() and vsnprintf() write to the character string str.

static char sprintf_buffer[2048]; // 除了sprintf其他均不能使用
static char printf_buf[2048]; // 除了printf其他均不能使用

int puts(const char *str) {
  for(int i = 0; str[i]; i ++) putch(str[i]);
  return 0;
}

int printf(const char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  int ret = sprintf(printf_buf, fmt, ap);
  va_end(ap);
  puts(printf_buf);
  return ret;
}

int vsprintf(char *out, const char *fmt, va_list ap) {
  return 0;
}

int sprintf(char *out, const char *fmt, ...) {
  sprintf_buffer[0] = '\0';
  va_list ap;
  va_start(ap, fmt);

  // 一些flags
  int i = 0; // 始终指向下一个未读取的字符 
  int j = 0; // 始终指向下一个输出的位置
  int total = 0;
  int f_norm = 1; // 普通模式，在该模式下直接输出读取的字符
  // int get_num = 0; // 是否在参数模式下获取接下来的所有数字

  // 一些临时变量
  int v;
  unsigned int u;
  char *str;
  
  while(fmt[i]) {
    /*puts("i j fmt[i] sprintf_buffer is ");
    puts(itoa(i));
    puts(", ");
    puts(itoa(j));
    puts(", '");
    putch(fmt[i]);
    puts("', ");
    puts(sprintf_buffer);
    puts("\n");
    */
    if(f_norm && fmt[i] == '%') f_norm = 0;
    if(f_norm) {
      sprintf_buffer[j] = fmt[i];
      i ++, j ++, sprintf_buffer[j] = '\0';
    } else {
      while(!f_norm) {
        switch(fmt[i]) {
          case '%': i ++; break;
          case 'd':
            v = va_arg(ap, int);
            strcat(sprintf_buffer, itoa(v));
            f_norm = 1, total ++, i ++, j += strlen(itoa(v)); // 设置标志
            break;
          case 's':
            str = va_arg(ap, char *);
            strcat(sprintf_buffer, str);
            f_norm = 1, total ++, i ++, j += strlen(str); // 设置标志
            break;
          case 'x':
            u = va_arg(ap, unsigned int);
            strcat(sprintf_buffer, hextoa(u));
            f_norm = 1, total ++, i ++, j += strlen(hextoa(u)); // 设置标志
            break;
          case 'u':
            u = va_arg(ap, unsigned int);
            strcat(sprintf_buffer, utoa(u));
            f_norm = 1, total ++, i ++, j += strlen(utoa(u)); // 设置标志
            break;
          /*case '0': // 填充u个0
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
              sprintf_buffer[j] = '0';
              j ++;
              u --;
              putch('u');
            }
            i ++; // 设置标志
            break; */
          default: puts("in klib sprintf, not implement '"); putch(fmt[i]); puts("': "); assert(0);
        }
      }
    }
  }
  strcpy(out, sprintf_buffer);

  return total;
}

int snprintf(char *out, size_t n, const char *fmt, ...) {
  return 0;
}

int vsnprintf(char *out, size_t n, const char *fmt, va_list ap) {
  return 0;
}

#endif
