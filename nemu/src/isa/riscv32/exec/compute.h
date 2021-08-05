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



// 纯寄存器操作的指令
static inline def_EHelper(add) {
  rtl_add(s, ddest, dsrc1, dsrc2);
  print_asm_template3(add);
}

static inline def_EHelper(sub) {
  rtl_sub(s, ddest, dsrc1, dsrc2);
  print_asm_template2(sub);
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

static inline def_EHelper(sltu) {
  if(*(word_t *)dsrc1 < *(word_t *)dsrc2) {
    *ddest = 1;
  } else {
    *ddest = 0;
  }
  print_asm_template3(sltu);
}