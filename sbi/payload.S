/** fw_payload settings */
    .section .entry, "ax", %progbits
    .align 3
    .global x_sbi_next_addr
    /*
	 * We can only use a0, a1, and a2 registers here.
	 * The next address should be returned in 'a0'.
	 */
x_sbi_next_addr:
    lla a0, payload_bin
    ret

    .section .entry, "ax", %progbits
    .align 3
    .global x_sbi_next_mode
    /*
	 * We can only use a0, a1, and a2 registers here.
	 * The next address should be returned in 'a0'.
	 */
x_sbi_next_mode:
    li  a0, PRV_S
    ret

/** insert payload_bin */
    .section .payload, "ax", %progbits
    .align 4
    .global payload_bin
payload_bin:
    .incbin X_SBI_PAYLOAD_PATH
