#include <cpu/exec.h>
#include "../local-include/decode.h"
#include "all-instr.h"

static inline void set_width(DecodeExecState *s, int width) {
  if (width != 0) s->width = width;
}

static inline def_EHelper(load) {
  switch (s->isa.instr.i.funct3) {
    EXW  (2, ld, 4)
    default: exec_inv(s);
  }
}

static inline def_EHelper(store) {
  switch (s->isa.instr.s.funct3) {
    EXW  (2, st, 4)
    default: exec_inv(s);
  }
}

static inline def_EHelper(grp_00100) {
  switch (s->isa.instr.s.funct3) {
    EXW (0b000, addi, 4)
    EXW (0b010, slti, 4)
    EXW (0b011, sltiu, 4)
    default: exec_inv(s);
  }
}

static inline def_EHelper(grp_01100) {
  switch (s->isa.instr.r.funct3) {
    case 0b000:
      switch(s->isa.instr.r.funct7) {
        EXW (0b0000000, add, 4)
        EXW (0b0100000, sub, 4)
      }
      break;
    case 0b001: 
    case 0b010:
    EXW (0b011, sltu, 4)
    case 0b100:
    case 0b101:
    case 0b110:
    case 0b111: exec_inv(s); break;
  }
}

static inline def_EHelper(grp_11000) {
  switch(s->isa.instr.b.funct3) {
    EXW(0b000, beq, 4)
    EXW(0b001, bne, 4)
    default: exec_inv(s);
  }
}

static inline void fetch_decode_exec(DecodeExecState *s) {
  s->isa.instr.val = instr_fetch(&s->seq_pc, 4);
  Assert(s->isa.instr.i.opcode1_0 == 0x3, "Invalid instruction");
  switch (s->isa.instr.i.opcode6_2) {
    IDEX (0b00000, I, load)
    IDEX (0b00100, I, grp_00100) //
    IDEXW (0b00101, U, auipc, 4) //
    IDEX (0b01000, S, store)
    IDEX (0b01100, R, grp_01100) //
    IDEX (0b01101, U, lui)
    IDEX (0b11000, B, grp_11000) //
    IDEXW (0b11001, I, jalr, 4) //
    EX   (0b11010, nemu_trap)
    IDEXW (0b11011, J, jal, 4) //
    default: exec_inv(s);
  }
}

static inline void reset_zero() {
  reg_l(0) = 0;
}

vaddr_t isa_exec_once() {
  DecodeExecState s;
  s.is_jmp = 0;
  s.seq_pc = cpu.pc;

  fetch_decode_exec(&s);
  update_pc(&s);

  reset_zero();

  return s.seq_pc;
}
