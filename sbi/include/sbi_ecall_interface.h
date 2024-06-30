#ifndef __SBI_ECALL_INTERFACE_H__
#define __SBI_ECALL_INTERFACE_H__

/* SBI Extension IDs */
//leagacy
#define SBI_EXT_0_1_SET_TIMER			0x0
#define SBI_EXT_0_1_CONSOLE_PUTCHAR		0x1
#define SBI_EXT_0_1_CONSOLE_GETCHAR		0x2
#define SBI_EXT_0_1_SHUTDOWN			0x8

//after sbi-v0.2
#define SBI_EXT_BASE				    0x10
#define SBI_EXT_TIME				    0x54494D45
#define SBI_EXT_DBCN				    0x4442434E
#define SBI_EXT_HSM				        0x48534D
#define SBI_EXT_SRST				    0x53525354
#define SBI_EXT_SUSP				    0x53555350

#endif
