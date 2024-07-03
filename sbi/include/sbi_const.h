#ifndef __SBI_CONST_H__
#define __SBI_CONST_H__

/** Platform default per-HART stack size for exception/interrupt handling */
#define SBI_PLATFORM_DEFAULT_HART_STACK_SIZE	8192

/** Platform default heap size */
#define SBI_PLATFORM_DEFAULT_HEAP_SIZE          (0x8000 + 0x800)

#endif