#include <am.h>
#include <nemu.h>

#include <klib.h>

static uint32_t __am_timer_init_usecs; 
static uint32_t __am_timer_init_secs;

void __am_timer_init() {
  __am_timer_init_usecs = inl(RTC_ADDR);
  __am_timer_init_secs = inl(RTC_ADDR + 4);
  printf("initial time %u secs and %u usecs\n", __am_timer_init_secs, __am_timer_init_usecs);
}

void __am_timer_uptime(AM_TIMER_UPTIME_T *uptime) {
  //uint32_t current_usecs = inl(RTC_ADDR);
  //uint32_t current_secs = inl(RTC_ADDR + 4);
  //uptime->us = (current_secs - __am_timer_init_secs) * 1000000 - __am_timer_init_usecs + current_usecs;
  //uptime->us = 100;
  //printf("__am_timer_uptime us = %u\n", uptime->us);
}

void __am_timer_rtc(AM_TIMER_RTC_T *rtc) {
  rtc->second = 0;
  rtc->minute = 0;
  rtc->hour   = 0;
  rtc->day    = 0;
  rtc->month  = 0;
  rtc->year   = 1900;
}
