/*
    X-SBI Layout
*/
    /* 0x8000 0000 */
    . =  X_SBI_TEXT_START
    PROVIDE(_x_sbi_start = .);

    . = ALIGN(0x1000);

    /* Beginning of the code section */
    .text :
    {
        PROVIDE(_text_start = .);
        *(.entry)
        *(.text)
        . = ALIGN(8);
        PROVIDE(_text_end = .);
    }
    /* End of the code sections */

    . = ALIGN(0x1000);

    /* Beginning of the read-only data sections */
    .rodata :
    {
        PROVIDE(_rodata_start = .);
        *(.rodata)
        *(.rodata.*)
        . = ALIGN(8);
        PROVIDE(_rodata_end = .);
    }
    /* End of the read-only data sections */

    . = ALIGN(0x1000);

    /* Beginning of the read-write data sections */
    .data :
    {
        PROVIDE(_data_start = .);
        *(.data)
        *(.data.*)
        . = ALIGN(8);
        PROVIDE(_data_end = .);
    }

    . = ALIGN(0x1000);

    .bss :
    {
        PROVIDE(_bss_start = .);
        *(.sbss)
        *(.sbss.*)
        *(.bss)
        *(.bss.*)
        . = ALIGN(8);
        PROVIDE(_bss_end = .);
    }
    /* End of the read-write data sections */

    . ALIGN(0x1000);

    PROVIDE(_x_sbi_end = .);
