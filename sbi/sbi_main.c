#include "sbi_scratch.h"
#include "sbi_hart.h"
#include "rv_asm.h"
#include "rv_encoding.h"

#include "x_bitops.h"

/**
 *  SBI Extension Initialize
 *  
 */
static void
x_sbi_init_entry(struct sbi_scratch *scratch, u32 hartid)
{
    int ret;

    ret = sbi_heap_init(scratch);
    if (ret)
        sbi_hart_hang();

    /** TODO */
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
}

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
    unsigned long next_arg1, next_addr, next_mode;
    unsigned long val;
    u32 hartid = current_hartid();

    x_sbi_init_entry(scratch, hartid);

    /** Current Hart need to switch mode */
    next_arg1 = 0;
    next_addr = scratch->next_addr;
    next_mode = scratch->next_mode;

    val = csr_read(CSR_MSTATUS);
    val = INSERT_FIELD(val, MSTATUS_MPP, next_mode);
    val = INSERT_FIELD(val, MSTATUS_MPIE, 0);

    csr_write(CSR_MSTATUS, val);
    csr_write(CSR_MEPC, next_addr);

    if (next_mode == PRV_S) {
        csr_write(CSR_STVEC, next_addr);
        csr_write(CSR_SSCRATCH, 0);
        csr_write(CSR_SIE, 0);
        csr_write(CSR_SATP, 0);
    }

    register unsigned long a0 asm("a0") = scratch;
    register unsigned long a1 asm("a1") = hartid;

    __asm__ __volatile__("mret" : : "r"(a0), "r"(a1));
    __builtin_unreachable();
}
