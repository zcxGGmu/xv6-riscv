#ifndef __SBI_SCRATCH_H__
#define __SBI_SCRATCH_H__

#include "rv_asm.h"
#include "util/x_types.h"

/** Offset of various member in sbi_scratch */
#define SBI_SCRATCH_FW_START_OFFSET     (0 * __SIZEOF_POINTER__)
#define SBI_SCRATCH_FW_SIZE_OFFSTET      (1 * __SIZEOF_POINTER__)
#define SBI_SCRATCH_HEAP_OFFSET         (2 * __SIZEOF_POINTER__)
#define SBI_SCRATCH_HEAP_SIZE_OFFSET    (3 * __SIZEOF_POINTER__)
#define SBI_SCRATCH_NEXT_ADDR_OFFSET    (4 * __SIZEOF_POINTER__)
#define SBI_SCRATCH_NEXT_MODE_OFFSET    (5 * __SIZEOF_POINTER__)
#define SBI_SCRATCH_TRAP_CONTEXT_OFFSET (6 * __SIZEOF_POINTER__)
#define SBI_SCRATCH_SIZE                (0x1000)

struct sbi_scratch {
    unsigned long fw_start;
    unsigned long fw_size;

    /* Offset (in bytes) of the heap area */
    unsigned long heap_offset;
    /* Size (in bytes) of the heap area */
    unsigned long heap_size;
    /* Address of next booting stage for this HART */
    unsigned long next_addr;
    /* Privilege mode of next booting stage for this HART */
    unsigned long next_mode;

    /* Address of current trap context */
    unsigned long trap_context;    
};

/**
 * Prevent modification of struct sbi_scratch from affecting
 * SBI_SCRATCH_xxx_OFFSET
 */
_Static_assert(
    offsetof(struct sbi_scratch, fw_start)
        == SBI_SCRATCH_FW_START_OFFSET,
    "struct sbi_scratch definition has changed, please redefine "
    "SBI_SCRATCH_FW_START_OFFSET");
_Static_assert(
	offsetof(struct sbi_scratch, fw_size)
		== SBI_SCRATCH_FW_SIZE_OFFSTET,
	"struct sbi_scratch definition has changed, please redefine "
	"SBI_SCRATCH_FW_SIZE_OFFSET");
_Static_assert(
	offsetof(struct sbi_scratch, next_addr)
		== SBI_SCRATCH_NEXT_ADDR_OFFSET,
	"struct sbi_scratch definition has changed, please redefine "
	"SBI_SCRATCH_NEXT_ADDR_OFFSET");
_Static_assert(
	offsetof(struct sbi_scratch, next_mode)
		== SBI_SCRATCH_NEXT_MODE_OFFSET,
	"struct sbi_scratch definition has changed, please redefine "
	"SBI_SCRATCH_NEXT_MODE_OFFSET");
_Static_assert(
	offsetof(struct sbi_scratch, trap_context)
		== SBI_SCRATCH_TRAP_CONTEXT_OFFSET,
	"struct sbi_scratch definition has changed, please redefine "
	"SBI_SCRATCH_TRAP_CONTEXT_OFFSET");

/* Get pointer to sbi_scratch for current HART */
#define sbi_sratch_current_hart_ptr() \
    ((struct sbi_scratch *)csr_read(CSR_MSCRATCH))

/* Initialize scratch table and allocator */
int sbi_scratch_init(struct sbi_scratch *scratch);

#endif
