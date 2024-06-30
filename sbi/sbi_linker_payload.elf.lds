/*
    The x-SBI firmware and the next stage payload (kernel binary)
    constitute the complete memory layout."
 */

OUTPUT_ARCH(riscv)
ENTRY(_start)

SECTIONS
{
    #include "sbi_base.lds"

    . = KERNEL_TEXT_START;

    .payload :
    {
        PROVIDE(_payload_start = .);
        *(.payload)
        . = ALIGN(8);
        *(_payload_end = .);
    }
}
