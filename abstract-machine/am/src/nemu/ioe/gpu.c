#include <am.h>
#include <nemu.h>
#include <klib.h>

#define SYNC_ADDR (VGACTL_ADDR + 4)

void __am_gpu_init() {
  int i;
  int w = inw(VGACTL_ADDR + 2);
  int h = inw(VGACTL_ADDR);
  uint32_t *fb = (uint32_t *)(uintptr_t)FB_ADDR;
  for(i = 0; i < w * h; i ++) fb[i] = i;
  outl(SYNC_ADDR, 1);
}

void __am_gpu_config(AM_GPU_CONFIG_T *cfg) {
  *cfg = (AM_GPU_CONFIG_T) {
    .present = true, .has_accel = false,
    .width = inw(VGACTL_ADDR + 2), .height = inw(VGACTL_ADDR),
    .vmemsz = inw(VGACTL_ADDR + 2) * inw(VGACTL_ADDR)
  };
}

#define min(a,b) ((a)<(b)?(a):(b))

void __am_gpu_fbdraw(AM_GPU_FBDRAW_T *ctl) {
    // 在(x,y)坐标处画一个w*h的矩形，像素按行优先存储在pixels中，每个像素用32位整数00RRGGBB的方式描述颜色
    // int x = ctl->x, y = ctl->y;
    // void *pixels = ctl->pixels;
    // int w = ctl->w, h = ctl->h;

    // assert(0 <= x && x + h < inw(VGACTL_ADDR)); // 矩形的行坐标应该在高度的范围内
    // assert(0 <= y && y + w < inw(VGACTL_ADDR + 2)); // 矩形的列坐标应该在宽度的范围内
    
    // uint32_t *fb = (uint32_t *)(uintptr_t)FB_ADDR;
    // int i = 0;
    // for(int row = x; row < x + h; row ++) {
    //   for(int col = y; col < y + w; col ++) {
    //     *(fb + row * inw(VGACTL_ADDR + 2) + col) = ((uint32_t *)pixels)[i];
    //     i ++;
    //   }
    // }
    // assert(i == w * h);
    // if(ctl->sync) {
    //   outl(SYNC_ADDR, 1);
    // }
    uint32_t *fb = (uint32_t*)(uintptr_t)FB_ADDR;
    int x = ctl->x, y = ctl->y, w = ctl->w, h = ctl->h;
    uint32_t *pixels = ctl->pixels;
    uint16_t max_h = inl(VGACTL_ADDR);
    uint16_t max_w = inl(VGACTL_ADDR + 2);
    int cp_bytes = sizeof(uint32_t) * min(w, max_w - x);
    // Copy the bytes to fb in row first.
    for (int i = 0; i < h && i + y < max_h; i ++) {
      memcpy(&fb[(y + i) * max_w + x], pixels, cp_bytes);
      // for (int j )
      pixels += w;
    }

    if (ctl->sync) {
      outl(SYNC_ADDR, 1);
    }
}

void __am_gpu_status(AM_GPU_STATUS_T *status) {
  status->ready = true;
}
