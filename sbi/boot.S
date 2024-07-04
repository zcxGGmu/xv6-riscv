/*
    x-SBI boot
*/
#include "rv_asm.h"
#include "rv_encoding.h"
#include "sbi_trap.h"
#include "sbi_scratch.h"
#include "sbi_const.h"

.macro MOV_3R __d0, __s0, __d1, __s1, __d2, __s2
    add \__d0, \__s0, zero
    add \__d1, \__s1, zero
    add \__d2, \__s2, zero
.endm

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
    
    /* Setup scratch space */
    lla tp, _x_sbi_end
    
    /* Setup heap base address - s9 */
    li  s9, SBI_PLATFORM_DEFAULT_HEAP_SIZE
    lla s10, _x_sbi_start
    sub s10, tp, s10
    add tp, tp, s9
    
    /* Keep a copy of tp - t3 */
    add t3, tp, zero

    /* Hart Count - s7 */
    li  s7, 1
    
    /* Set default hart_stack_size */
    li s8, SBI_PLATFORM_DEFAULT_HART_STACK_SIZE
/* _scratch_init */
_scratch_init:
    /*
	 * The following registers hold values that are computed before
	 * entering this block, and should remain unchanged.
	 *
	 * t3 -> the firmware end address
	 * s7 -> HART count
	 * s8 -> HART stack size
	 * s9 -> Heap Size
	 * s10 -> Heap Offset
	 */
    add tp, t3, zero
    sub tp, tp, s9
    li  a5, SBI_SCRATCH_SIZE
    sub tp, tp, a5
    /* tp = FW_END - HAEP_SIZE - SBI_SCRATCH_SIZE */
    
    /* Initialize scratch space */
    /* Store fw_{start/size} in scratch space */
    lla a4, _x_sbi_start
    sub a5, t3, a4
    REG_S   a4, SBI_SCRATCH_FW_START_OFFSET(tp)
    REG_S   a5, SBI_SCRATCH_FW_SIZE_OFFSET(tp)

    /* Store heap_{offset/size} in scratch space */
    REG_S   s10, SBI_SCRATCH_HEAP_OFFSET(tp)
    REG_S   s9, SBI_SCRATCH_HEAP_SIZE_OFFSET(tp)

    /* Store next address in sratch space */
    MOV_3R  s0, a0, s1, a1, s2, a2
    call    x_sbi_next_addr
    REG_S   a0, SBI_SCRATCH_NEXT_ADDR_OFFSET(tp)
    MOV_3R  a0, s0, a1, s1, a2, s2

    /* Store next mode in sratch space */
    MOV_3R  s0, a0, s1, a1, s2, a2
    call    x_sbi_next_mode
    REG_S   a0, SBI_SCRATCH_NEXT_MODE_OFFSET(tp)
    MOV_3R  a0, s0, a1, s1, a2, s2
    
    /* TODO: FDT releated */
    
    /* Update the mscratch */
    csrw    CSR_MSCRATCH, tp
    /* Setup stack */
    add     sp, tp, zero
    /* Setup tarp handler */
    lla     a4, _trap_handler       // _trap_handler => entry.S
    csrw    CSR_MTVEC, a4
    /* Initialize SBI runtime */
    csrr    a0, CSR_MSCRATCH
    call    x_sbi_main              // sbi_init
    /** Enter C Routine */
    
    /* We don't expect to reach here hence just hang */
    j       _start_hang

    .section .entry, "ax", %progbits
    .align 3
    .global _start_hang
_start_hang:
    wfi
    j       _start_hang
