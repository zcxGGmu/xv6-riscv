#ifndef __RV_ENCODING_H__
#define __RV_ENCODING_H__

#include "sbi_const.h"

/* ===== Machine-level CSRs ===== */
/* Machine Information Registers */
#define CSR_MVENDORID       0xf11
#define CSR_MARCHID         0xf12
#define CSR_MIMPID          0xf13
#define CSR_MHARTID         0xf14
#define CSR_MCONFIGPTR      0xf15

/* Machine Trap Setup */
#define CSR_MSTATUS			0x300
#define CSR_MISA			0x301
#define CSR_MEDELEG			0x302
#define CSR_MIDELEG			0x303
#define CSR_MIE				0x304
#define CSR_MTVEC			0x305
#define CSR_MCOUNTEREN		0x306
#define CSR_MSTATUSH		0x310

/* Machine Configuration */
#define CSR_MENVCFG			0x30a
#define CSR_MENVCFGH		0x31a

/* Machine Trap Handling */
#define CSR_MSCRATCH        0x340
#define CSR_MEPC			0x341
#define CSR_MCAUSE			0x342
#define CSR_MTVAL			0x343
#define CSR_MIP				0x344
#define CSR_MTINST			0x34a
#define CSR_MTVAL2			0x34b

#define PRV_U           _UL(0)
#define PRV_S           _UL(1)
#define PRV_M           _UL(2)

/* ===== Supervisor-level CSRs ===== */
#define CSR_SSTATUS         0x100
#define CSR_SIE             0x104
#define CSR_STVEC           0x105
#define CSR_SCOUNTEREN      0x106

/* Supervisor Trap Setup */
#define CSR_SENVCFG         0x10a

/* Supervisor Counter Inhibit */
#define CSR_SCOUNTINHIBIT   0x120

/* Supervisor Trap Handling */
#define CSR_SSCRATCH        0x140
#define CSR_SEPC            0x141
#define CSR_SCAUSE          0x142
#define CSR_STVAL           0x143
#define CSR_SIP             0x144

/* Supervisor Protection and Translation */
#define CSR_SATP			0x180

/* ===== MSTATUS bits settings for RV64 ===== */
#define MSTATUS_SIE             _UL(0x00000002)
#define MSTATUS_MIE             _UL(0x00000008)
#define MSTATUS_SPIE_SHIFT      5
#define MSTATUS_SPIE            (_UL(1) << MSTATUS_SPIE_SHIFT)
#define MSTATUS_UBE			    _UL(0x00000040)
#define MSTATUS_MPIE			_UL(0x00000080)
#define MSTATUS_SPP_SHIFT		8
#define MSTATUS_SPP			    (_UL(1) << MSTATUS_SPP_SHIFT)
#define MSTATUS_MPP_SHIFT		11
#define MSTATUS_MPP			    (_UL(3) << MSTATUS_MPP_SHIFT)
#define MSTATUS_FS			    _UL(0x00006000)
#define MSTATUS_XS			    _UL(0x00018000)
#define MSTATUS_VS			    _UL(0x00000600)
#define MSTATUS_MPRV			_UL(0x00020000)
#define MSTATUS_SUM			_UL(0x00040000)
#define MSTATUS_MXR			_UL(0x00080000)
#define MSTATUS_TVM			_UL(0x00100000)
#define MSTATUS_TW			_UL(0x00200000)
#define MSTATUS_TSR			_UL(0x00400000)
#define MSTATUS32_SD		_UL(0x80000000)
#define MSTATUS_UXL			    _ULL(0x0000000300000000)
#define MSTATUS_SXL			    _ULL(0x0000000C00000000)
#define MSTATUS_SBE			    _ULL(0x0000001000000000)
#define MSTATUS_MBE			    _ULL(0x0000002000000000)
#define MSTATUS_GVA			    _ULL(0x0000004000000000)
#define MSTATUS_GVA_SHIFT	    38
#define MSTATUS_MPV			    _ULL(0x0000008000000000)

#endif