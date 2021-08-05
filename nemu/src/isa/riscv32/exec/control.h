static inline def_EHelper(jal) {
    rtl_addi(s, ddest, &cpu.pc, 4);
    // printf("\033[43;34m old pc is 0x%x, simm is 0x%x, ", cpu.pc, id_src1->simm);
    rtl_addi(s, s0, &cpu.pc, id_src1->simm);
    // printf("\033[43;34ms0 is 0x%x\033[0m\n", *s0);
    rtl_jr(s, s0);
    print_asm_template2(jal);
}

static inline def_EHelper(jalr) {
    rtl_addi(s, s0, &cpu.pc, 4);
    rtl_addi(s, s1, dsrc1, id_src2->simm);
    *s1 = *s1 & ~1;
    rtl_jr(s, s1);
    *ddest = *s0;
    print_asm_template3(jalr);
}