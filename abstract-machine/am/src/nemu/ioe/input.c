#include <am.h>
#include <nemu.h>

#define KEYDOWN_MASK 0x8000

#include <klib.h>

void __am_input_keybrd(AM_INPUT_KEYBRD_T *kbd) {
  kbd->keycode = inl(KBD_ADDR);
  if((uint16_t)(kbd->keycode) & KEYDOWN_MASK) {
    kbd->keydown = true;
  } else {
    kbd->keydown = false;
  }
}
