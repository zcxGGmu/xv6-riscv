/*
    insert payload_bin
*/

/** fw_payload settings */
    .section 

    .section .payload, "ax", %progbits
    .align 4
    .global payload_bin
payload_bin:
    .incbin X_SBI_PAYLOAD_PATH
