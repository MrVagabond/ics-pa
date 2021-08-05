static inline def_EHelper(lui) {
  rtl_li(s, ddest, id_src1->imm + 1);
  print_asm_template2(lui);
}
