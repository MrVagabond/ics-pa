#include <am.h>
#include <nemu.h>

#include <klib.h>

void __am_timer_init() {
}

void __am_timer_uptime(AM_TIMER_UPTIME_T *uptime) {
  // uptime->us = (uint64_t)inl(RTC_ADDR + 4);
  printf("__am_timer_uptime init val: hi=%d, lo=%d\n", (int32_t)(uptime->us >> 32), (int32_t)(uptime->us));
}

void __am_timer_rtc(AM_TIMER_RTC_T *rtc) {
  rtc->second = 0;
  rtc->minute = 0;
  rtc->hour   = 0;
  rtc->day    = 0;
  rtc->month  = 0;
  rtc->year   = 1900;
}
