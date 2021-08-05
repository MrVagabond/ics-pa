#include <isa.h>
#include "local-include/reg.h"

#include <memory/vaddr.h>

const char *regs[] = {
  "$0", "ra", "sp", "gp", "tp", "t0", "t1", "t2",
  "s0", "s1", "a0", "a1", "a2", "a3", "a4", "a5",
  "a6", "a7", "s2", "s3", "s4", "s5", "s6", "s7",
  "s8", "s9", "s10", "s11", "t3", "t4", "t5", "t6"
};




void isa_reg_display() {
  printf("+++++\033[40;44mpc = 0x%x\033[0m, next instruction is \033[40;44m%x\033[0m(", cpu.pc, vaddr_read(cpu.pc, 4));
  zj_print_opcode(vaddr_read(cpu.pc, 4));
  printf(")\n");

  int index = 0;
  for(int i = 0; i < 4; i ++) {
    for(int j = 0; j < 8; j ++) {
      printf("\033[47;30m(x%d)%s\033[0m:\033[4m0x%x\033[0m ", index, regs[index], cpu.gpr[index]._32);
      index ++;
    }
    printf("\n");
  }
  printf("-----\n");
}

word_t isa_reg_str2val(const char *s, bool *success) {
  return 0;
}
