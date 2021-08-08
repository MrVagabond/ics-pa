#include <am.h>
#include <nemu.h>

#define KEYDOWN_MASK 0x8000

#include <klib.h>

void __am_input_keybrd(AM_INPUT_KEYBRD_T *kbd) {
  // kbd->keycode = inl(KBD_ADDR);
  // if(kbd->keycode & KEYDOWN_MASK) {
  //   kbd->keydown = true;
  // } else {
  //   kbd->keydown = false;
  // }
  int k = inl(KBD_ADDR);
  kbd->keydown = (k & KEYDOWN_MASK ? true : false);
  kbd->keycode = k & ~KEYDOWN_MASK;
}
