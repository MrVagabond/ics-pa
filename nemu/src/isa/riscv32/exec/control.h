static inline def_EHelper(jal) {
    rtl_addi(s, ddest, &cpu.pc, 4);
    // rtlreg_t tmp = cpu.pc;
    rtl_addi(s, s0, &cpu.pc, id_src1->simm);
    printf("\033[43;34ms0 is %d\033[0m\n", *s0);
    rtl_jr(s, s0);
    // printf("\033[43;34mold pc is 0x%x, simm is 0x%x, new pc is 0x%x\033[0m\n", tmp, id_src1->simm, cpu.pc);
}