#include <am.h>
#include <nemu.h>

#define KEYDOWN_MASK 0x8000

#include <klib.h>

void __am_input_keybrd(AM_INPUT_KEYBRD_T *kbd) {
  kbd->keycode = inl(KBD_ADDR);
  printf("keycode is %d\n", kbd->keycode);
  if((uint8_t)(kbd->keycode) >> 7) {
    kbd->keydown = true;
  } else {
    kbd->keydown = false;
  }
}
