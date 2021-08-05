#include <isa.h>
#include <monitor/difftest.h>
#include "../local-include/reg.h"
#include "difftest.h"

bool isa_difftest_checkregs(CPU_state *ref_r, vaddr_t pc) {
  for(int i = 0; i < 31; i ++) {
    printf("0x%x\n", ref_r->gpr[i]._32);
  }
  printf("pc: 0x%x", ref_r->pc);
  return false;
}

void isa_difftest_attach() {
}
