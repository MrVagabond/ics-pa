#include <am.h>
#include <nemu.h>

#include <klib.h>

void __am_timer_init() {
}

void __am_timer_uptime(AM_TIMER_UPTIME_T *uptime) {
  printf("in __am_timer_uptime\n");
  uint32_t lo = inl(RTC_ADDR);
  printf("lo is %d\n", lo);
  uint32_t hi = inl(RTC_ADDR + 4);
  printf("hi is %d\n", hi);
  uptime->us = ((uint64_t)hi << 32) | (uint64_t)lo;
}

void __am_timer_rtc(AM_TIMER_RTC_T *rtc) {
  rtc->second = 0;
  rtc->minute = 0;
  rtc->hour   = 0;
  rtc->day    = 0;
  rtc->month  = 0;
  rtc->year   = 1900;
}
