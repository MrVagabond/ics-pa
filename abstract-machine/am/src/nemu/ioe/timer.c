#include <am.h>
#include <nemu.h>

#include <klib.h>

static uint64_t __am_timer_init_usecs; 

void __am_timer_init() {
  __am_timer_init_usecs = (uint64_t)inl(RTC_ADDR + 4) * 1000000 + (uint64_t)inl(RTC_ADDR);
}

void __am_timer_uptime(AM_TIMER_UPTIME_T *uptime) {
  uptime->us = (uint64_t)inl(RTC_ADDR + 4) * 1000000 + (uint64_t)inl(RTC_ADDR) - __am_timer_init_usecs;
  printf("__am_timer_uptime us = %d\n", uptime->us);
}

void __am_timer_rtc(AM_TIMER_RTC_T *rtc) {
  rtc->second = 0;
  rtc->minute = 0;
  rtc->hour   = 0;
  rtc->day    = 0;
  rtc->month  = 0;
  rtc->year   = 1900;
}
