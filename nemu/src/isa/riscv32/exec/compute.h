// 含有立即数的指令
static inline def_EHelper(lui) {
  rtl_li(s, ddest, id_src1->imm);
  print_asm_template2(lui);
}


static inline def_EHelper(addi) {
  rtl_addi(s, ddest, dsrc1, id_src2->simm);
  print_asm_template3(addi);
}

static inline def_EHelper(auipc) {
  rtl_addi(s, ddest, &cpu.pc, id_src1->imm);
  print_asm_template2(auipc);
}

static inline def_EHelper(slti) {
  if(*(sword_t *)dsrc1 < id_src2->simm) {
    *ddest = 1;
  } else {
    *ddest = 0;
  }
  print_asm_template3(slti);
}

static inline def_EHelper(sltiu) {
  if(*(word_t *)dsrc1 < (word_t)(id_src2->simm)) {
    *ddest = 1;
  } else {
    *ddest = 0;
  }
  print_asm_template3(sltiu);
}

static inline def_EHelper(xori) {
  rtl_xori(s, ddest, dsrc1, id_src2->simm);
  print_asm_template3(xori);
}

static inline def_EHelper(ori) {
  rtl_ori(s, ddest, dsrc1, id_src2->simm);
  print_asm_template3(ori);
}

static inline def_EHelper(andi) {
  rtl_andi(s, ddest, dsrc1, id_src2->simm);
  print_asm_template3(andi);
}


// 纯寄存器操作的指令
static inline def_EHelper(add) {
  rtl_add(s, ddest, dsrc1, dsrc2);
  print_asm_template3(add);
}

static inline def_EHelper(sub) {
  rtl_sub(s, ddest, dsrc1, dsrc2);
  print_asm_template2(sub);
}

static inline def_EHelper(mul) {
  rtl_mul_lo(s, ddest, dsrc1, dsrc2);
  print_asm_template3(mul);
}

static inline def_EHelper(xor) {
  rtl_xor(s, ddest, dsrc1, dsrc2);
  print_asm_template3(xor);
}

static inline def_EHelper(or) {
  rtl_or(s, ddest, dsrc1, dsrc2);
  print_asm_template3(or);
}

static inline def_EHelper(and) {
  rtl_and(s, ddest, dsrc1, dsrc2);
  print_asm_template3(and);
}


// 比较类的指令

static inline def_EHelper(beq) {
  if(*dsrc1 == *dsrc2) {
    rtl_addi(s, s0, &cpu.pc, id_dest->simm);
    rtl_jr(s, s0);
  }
  print_asm_template3(beq);
}

static inline def_EHelper(bne) {
  if(*dsrc1 != *dsrc2) {
    rtl_addi(s, s0, &cpu.pc, id_dest->simm);
    rtl_jr(s, s0);
  }
  print_asm_template3(bne);
}


static inline def_EHelper(blt) {
  if((*(sword_t *)dsrc1) < (*(sword_t *)dsrc2)) {
    rtl_addi(s, s0, &cpu.pc, id_dest->simm);
    rtl_jr(s, s0);
  }
  print_asm_template3(blt);
}

static inline def_EHelper(bge) {
  if((*(sword_t *)dsrc1) >= (*(sword_t *)dsrc2)) {
    rtl_addi(s, s0, &cpu.pc, id_dest->simm);
    rtl_jr(s, s0);
  }
  print_asm_template3(bge);
}

static inline def_EHelper(bltu) {
  if((*(word_t *)dsrc1) < (*(word_t *)dsrc2)) {
    rtl_addi(s, s0, &cpu.pc, id_dest->simm);
    rtl_jr(s, s0);
  }
  print_asm_template3(bltu);
}

static inline def_EHelper(bgeu) {
  if((*(word_t *)dsrc1) >= (*(word_t *)dsrc2)) {
    rtl_addi(s, s0, &cpu.pc, id_dest->simm);
    rtl_jr(s, s0);
  }
  print_asm_template3(bgeu);
}


static inline def_EHelper(sltu) {
  if(*(word_t *)dsrc1 < *(word_t *)dsrc2) {
    *ddest = 1;
  } else {
    *ddest = 0;
  }
  print_asm_template3(sltu);
}

static inline def_EHelper(slt) {
  if(*(sword_t *)dsrc1 < *(sword_t *)dsrc2) {
    *ddest = 1;
  } else {
    *ddest = 0;
  }
  print_asm_template3(slt);
}



// 移位指令
static inline def_EHelper(sll) {
  *s0 = *dsrc2 & 0b11111;
  *ddest = (*dsrc1) << (*s0);
  print_asm_template3(sll);
}

static inline def_EHelper(srl) {
  *s0 = *dsrc2 & 0b11111;
  *ddest = (*(word_t *)dsrc1) >> (*s0);
  print_asm_template3(srl);
}

static inline def_EHelper(sra) {
  *s0 = *dsrc2 & 0b11111;
  *ddest = (*(sword_t *)dsrc1) >> (*s0);
  print_asm_template3(sll);
}

static inline def_EHelper(slli) {
  *s0 = s->isa.instr.val;
  Assert(zj_bitcut(25, 25, *s0) == 0, "not valid slli\n");
  *s0 = zj_bitcut(25, 20, *s0);
  *ddest = (*dsrc1) << (*s0);
  print_asm_template3(slli);
}

static inline def_EHelper(srli) {
  *s0 = s->isa.instr.val;
  Assert(zj_bitcut(25, 25, *s0) == 0, "not valid srli\n");
  *s0 = zj_bitcut(25, 20, *s0);
  *ddest = (*(word_t *)dsrc1) >> (*s0);
  print_asm_template3(srli);
}

static inline def_EHelper(srai) {
  *s0 = s->isa.instr.val;
  Assert(zj_bitcut(25, 25, *s0) == 0, "not valid srai\n");
  *s0 = zj_bitcut(25, 20, *s0);
  *ddest = (*(sword_t *)dsrc1) >> (*s0);
  print_asm_template3(srai);
}