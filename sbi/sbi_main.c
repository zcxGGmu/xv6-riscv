#include "sbi_scratch.h"
#include "sbi_hart.h"
#include "rv_asm.h"

/**
 * Initialize X-SBI for current HART and jump to next
 * booting stage.
 *
 * The function expects following:
 * 1. The 'mscratch' CSR is pointing to sbi_scratch of current HART
 * 2. Stack pointer (SP) is setup for current HART
 * 3. Interrupts are disabled in MSTATUS CSR
 * 4. All interrupts are disabled in MIE CSR
 *
 * @param scratch pointer to sbi_scratch of current HART
 */
void __noreturn x_sbi_main(struct sbi_scratch *scratch)
{
    int ret;
    unsigned long next_arg1, next_addr, next_mode;
    unsigned long val;
    u32 hartid = current_hartid();
    
    ret = sbi_scratch_init(scratch);
    if (ret)
        sbi_hart_hang();

    ret = sbi_heap_init(scratch);
    if (ret)
        sbi_hart_hang();

    ret = sbi_hsm_init(scratch, hartid);
    if (ret)
        sbi_hart_hang();

    ret = sbi_hart_init(scratch);
    if (ret)
        sbi_hart_hang();

    ret = sbi_console_init(scratch);
    if (ret)
        sbi_hart_hang();
    
    ret = sbi_ipi_init(scratch);
    if (ret)
        sbi_hart_hang();

    ret = sbi_timer_init();
    if (ret)
        sbi_hart_hang();
    
    /** Ecall Initialization */
    ret = sbi_ecall_init();
    if (ret)
        sbi_hart_hang();

    /** Current Hart need to switch mode */
    next_arg1 = 0;
    next_addr = scratch->next_addr;
    next_mode = scratch->next_mode;

    val = csr_read(CSR_MSTATUS);
    // TODO: make mstatus-bits

    csr_write(CSR_MSTATUS, val);
    csr_write(CSR_MEPC, next_addr);

    register unsigned long a0 asm("a0") = scratch;
    register unsigned long a1 asm("a1") = hartid;

    __asm__ __volatile__("mret" : : "r"(a0), "r"(a1));
    __builtin_unreachable();
}
