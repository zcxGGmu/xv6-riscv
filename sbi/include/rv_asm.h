#ifndef __RV_ASM_H__
#define __RV_ASM_H__

#ifdef __ASSEMBLER__
#define __ASM_STR(x)	x
#else
#define __ASM_STR(x)	#x
#endif

#if __riscv_xlen == 64
#define __REG_SEL(a, b) __ASM_STR(a)
#elif __riscv_xlen == 32
#define __REG_SEL(a, b) __ASM_STR(b)
#else
#error "unexpected __riscv_xlen"
#endif

#define REG_L 	__REG_SEL(ld, lw)
#define REG_S 	__REG_SEL(sd, sw)

#ifndef __ASSEMBLER__

#define csr_read(csr)                                           \
	({                                                      \
		register unsigned long __v;                     \
		__asm__ __volatile__("csrr %0, " __ASM_STR(csr) \
				     : "=r"(__v)                \
				     :                          \
				     : "memory");               \
		__v;                                            \
	})

#endif /* !__ASSEMBLER__ */

#endif