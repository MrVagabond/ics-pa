#include <isa.h>
#include "local-include/reg.h"

#include <memory/paddr.h>

const char *regs[] = {
  "$0", "ra", "sp", "gp", "tp", "t0", "t1", "t2",
  "s0", "s1", "a0", "a1", "a2", "a3", "a4", "a5",
  "a6", "a7", "s2", "s3", "s4", "s5", "s6", "s7",
  "s8", "s9", "s10", "s11", "t3", "t4", "t5", "t6"
};

static word_t zj_bitcut(int h, int l, word_t w) {
  assert(h >= l);
  word_t ans = (1 << (h - l + 1)) - 1;
  return ans & (w >> l);
}

static void zj_print_opcode(word_t instr) {
  for(int i = 6; i >= 0; i --) {
    printf("\033[40;44m%d\033[0m", (instr >> i) & 1 ? 1 : 0);
  }
  word_t opcode = instr & 0b1111111;
  switch (opcode) {
    case 0b0110111 : printf(", lui, x[%d] <- %d", zj_bitcut(11, 7, instr), zj_bitcut(31, 12, instr) << 12); break;
  }
}

void isa_reg_display() {
  printf("+++++\033[40;44mpc = 0x%x\033[0m, next instruction is \033[40;44m%x\033[0m(", cpu.pc, paddr_read(cpu.pc, 4));
  zj_print_opcode(paddr_read(cpu.pc, 4));
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
