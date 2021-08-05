#include <isa.h>
#include <monitor/difftest.h>
#include "../local-include/reg.h"
#include "difftest.h"

bool isa_difftest_checkregs(CPU_state *ref_r, vaddr_t pc) { // 传入的是qemu的状态和nemu的新pc
  // 之所以ref_r的类型是nemu中的CPU_state，是因为获取qemu状态的函数参数为void *，后来被强转为CPU_state
  for(int i = 0; i < 31; i ++) {
    assert(ref_r->gpr[i]._32 == cpu.gpr[i]._32);
  }
  assert(ref_r->pc == cpu.pc);
  return true;
}

void isa_difftest_attach() {
}
