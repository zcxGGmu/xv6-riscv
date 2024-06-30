OUTPUT_ARCH(riscv)
ENTRY(_start)

SECTIONS
{
    #include "sbi_base.lds"
}
