static inline def_EHelper(ld) { // 天生的无符号字节加载
  rtl_lm(s, ddest, dsrc1, id_src2->imm, s->width);

  print_Dop(id_src1->str, OP_STR_SIZE, "%d(%s)", id_src2->imm, reg_name(id_src1->reg));
  switch (s->width) {
    case 4: print_asm_template2(lw); break;
    case 2: print_asm_template2(lhu); break;
    case 1: print_asm_template2(lbu); break;
    default: assert(0);
  }
}

static inline def_EHelper(st) {
  rtl_sm(s, dsrc1, id_src2->imm, ddest, s->width);

  print_Dop(id_src1->str, OP_STR_SIZE, "%d(%s)", id_src2->imm, reg_name(id_src1->reg));
  switch (s->width) {
    case 4: print_asm_template2(sw); break;
    case 2: print_asm_template2(sh); break;
    case 1: print_asm_template2(sb); break;
    default: assert(0);
  }
}


static inline def_EHelper(sextld) { // 符号扩展的加载
  rtl_lm(s, ddest, dsrc1, id_src2->imm, s->width);
  switch(s->width) {
    case 2: 
      if(zj_bitcut(15, 15, *ddest) == 1) *ddest = *ddest | 0xffff0000;
      break;
    case 1: 
      if(zj_bitcut(7, 7, *ddest) == 1) *ddest = *ddest | 0xffffff00;
      break;
    default: assert(0);
  }
  switch (s->width) {
    case 2: print_asm_template2(lh); break;
    case 1: print_asm_template2(lb); break;
    default: assert(0);
  }
}