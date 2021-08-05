static inline def_EHelper(jal) {
    rtl_addi(s, ddest, &cpu.pc, 4);
    rtl_addi(s, &cpu.pc, &cpu.pc, id_src1->simm);
}