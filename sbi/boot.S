/*
    x-SBI boot
*/
#include "rv_asm.h"
#include "rv_encoding.h"
#include "sbi_trap.h"
#include "sbi_scratch.h"

_start:
    /* SMP Handle */
    
    
_bss_zero:
    /* Zero-out BSS */
    lla s4, _bss_start
    lla s5, _bss_end

    REG_S zero, (s4)
    add s4, s4, __SIZEOF_POINTER__
    blt s4, s5, _bss_zero

    /* Setup temporary stack */
    lla s4, _x_sbi_end
    li s5, (SBI_SCRATCH_SIZE * 2)
    add sp, s4, s5    
/* _scratch_init */
_scratch_init:
    

/* TODO: FDT releated */


/* Enter C Routine */
