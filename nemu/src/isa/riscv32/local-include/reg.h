#ifndef __RISCV32_REG_H__
#define __RISCV32_REG_H__

#include <common.h>

static inline int check_reg_index(int index) {
  assert(index >= 0 && index < 32);
  return index;
}

static inline word_t zj_bitcut(int h, int l, word_t w) {
  assert(h >= l);
  word_t ans = (1 << (h - l + 1)) - 1;
  return ans & (w >> l);
}

static inline void zj_print_opcode(word_t instr) {
  for(int i = 6; i >= 0; i --) {
    printf("\033[40;44m%d\033[0m", (instr >> i) & 1 ? 1 : 0);
  }
  word_t opcode = instr & 0b1111111;
  switch (opcode) {
    case 0b0110111 : printf(", lui, x[%d] <- 0x%x", zj_bitcut(11, 7, instr), zj_bitcut(31, 12, instr) << 12); break;
    case 0b0100011 : printf(", s");
      switch (zj_bitcut(14, 12, instr)) {
        case 0b000 : printf("b, M[x[%d] + sext(0x%x)] <- x[%d][7:0]", zj_bitcut(19, 15, instr), (zj_bitcut(31, 25, instr) << 5) | zj_bitcut(11, 7, instr), zj_bitcut(24, 20, instr)); break;
        case 0b001 : printf("h, M[x[%d] + sext(0x%x)] <- x[%d][15:0]", zj_bitcut(19, 15, instr), (zj_bitcut(31, 25, instr) << 5) | zj_bitcut(11, 7, instr), zj_bitcut(24, 20, instr)); break;
        case 0b010 : printf("w, M[x[%d] + sext(0x%x)] <- x[%d][31:0]", zj_bitcut(19, 15, instr), (zj_bitcut(31, 25, instr) << 5) | zj_bitcut(11, 7, instr), zj_bitcut(24, 20, instr)); break;
      }
      break;
    case 0b0000011 : printf(", l");
      switch (zj_bitcut(14, 12, instr)) {
        case 0b000 : printf("b"); break;
        case 0b001 : printf("h"); break;
        case 0b010 : printf("w, x[%d] <- M[x[%d] + sext(0x%x)][31:0]", zj_bitcut(11, 7, instr), zj_bitcut(19, 15, instr), zj_bitcut(31, 20, instr)); break;
        case 0b100 : printf("bu"); break;
        case 0b101 : printf("hu"); break;
      }
      break;
    case 0b1101011 : printf(", nemu_trap"); break;
    case 0b0010011 : printf(", ");
      switch(zj_bitcut(14, 12, instr)) {
        case 0b000 : printf("addi"); break;
        case 0b010 : printf("slti"); break;
        case 0b011 : printf("sltiu"); break;
        case 0b100 : printf("xori"); break;
        case 0b110 : printf("ori"); break;
        case 0b111 : printf("andi"); break;
        case 0b001 : printf("slli"); break;
        case 0b101 : printf("srli/srai"); break;
      }
      break;
  }
}

#define reg_l(index) (cpu.gpr[check_reg_index(index)]._32)

static inline const char* reg_name(int index) {
  extern const char* regs[];
  assert(index >= 0 && index < 32);
  return regs[index];
}

#endif
