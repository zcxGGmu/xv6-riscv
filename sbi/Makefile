# kernel/{include/src}
# usr/{include/src/scripts} 

# X_SBI_TEXT_START
# X_SBI_PAYLOAD_PATH 0x8000 0000
# KERNEL_TEXT_START 0x8020 0000

# Some settings
BUILD_ROOT= build
BUILD_DIR = $(BUILD_ROOT)/x-sbi
SRC_DIR = .
LIB_DIR = lib
BUILD_LIB_DIR = $(BUILD_ROOT)/lib

# Try to infer the correct TOOLPREFIX if not set
ifndef TOOLPREFIX
TOOLPREFIX := $(shell if riscv64-unknown-elf-objdump -i 2>&1 | grep 'elf64-big' >/dev/null 2>&1; \
							then echo 'riscv64-unknown-elf-'; \
				elif riscv64-linux-gnu-objdump -i 2>&1 | grep 'elf64-big' >/dev/null 2>&1; \
							then echo 'riscv64-linux-gnu-'; \
				elif riscv64-unknown-linux-gnu-objdump -i 2>&1 | grep 'elf64-big' >/dev/null 2>&1; \
							then echo 'riscv64-unknown-linux-gnu-'; \
				else echo "***" 1>&2; \
				echo "*** Error: Couldn't find a riscv64 version of GCC/binutils." 1>&2; \
				echo "*** To turn off this error, run 'gmake TOOLPREFIX= ...'." 1>&2; \
				echo "***" 1>&2; exit 1; fi)
endif

# Compiile Configurations
CC = $(TOOLPREFIX)gcc
AS = $(TOOLPREFIX)gas
LD = $(TOOLPREFIX)ld
OBJCOPY=$(TOOLPREFIX)objcopy
OBJDUMP=$(TOOLPREFIX)objdump

CFLAGS = -Wall -Werror -O -fno-omit-frame-pointer -ggdb -gdwarf-2
CFLAGS += -MD
CFLAGS += -mcmodel=medany
CFLAGS += -ffreestanding -fno-common -nostdlib -mno-relax
CFLAGS += $(shell $(CC) -fno-stack-protector -E -x c /dev/null >/dev/null 2>&1 && echo -fno-stack-protector)

LDFLAGS = -z max-page-size=4096


# Build x-SBI
SBI_BUILD_DIR = $(BUILD_ROOT)/sbi
SBI_SRC_DIR = sbi
$(SBI_BUILD_DIR)/%_c.o: $(SBI_SRC_DIR)/%.c
	$(CMD_PREFIX)mkdir -p $(SBI_BUILD_DIR); echo " CC   $@" ; $(GNU)-gcc $(COPS) -c $< -o $@

$(SBI_BUILD_DIR)/%_s.o: $(SBI_SRC_DIR)/%.S
	$(CMD_PREFIX)mkdir -p $(SBI_BUILD_DIR); echo " AS   $@"; $(GNU)-gcc $(COPS) -c $< -o $@

SBI_C_FILES = $(wildcard $(SBI_SRC_DIR)/*.c)
SBI_ASM_FILES = $(wildcard $(SBI_SRC_DIR)/*.S)
SBI_OBJ_FILES = $(SBI_C_FILES:$(SBI_SRC_DIR)/%.c=$(SBI_BUILD_DIR)/%_c.o)
SBI_OBJ_FILES += $(SBI_ASM_FILES:$(SBI_SRC_DIR)/%.S=$(SBI_BUILD_DIR)/%_s.o) 
SBI_OBJ_FILES += $(LIB_FILES:$(LIB_DIR)/%.c=$(BUILD_LIB_DIR)/%_c.o)

# DEP_FILES = $(SBI_OBJ_FILES:%.o=%.d)
# -include $(DEP_FILES)

mysbi.bin: $(SBI_SRC_DIR)/sbi_linker.ld $(SBI_OBJ_FILES) 
	$(CMD_PREFIX)$(GNU)-ld -T $(SBI_SRC_DIR)/sbi_linker.ld -o $(SBI_BUILD_DIR)/mysbi.elf  $(SBI_OBJ_FILES) -Map mysbi.map; echo " LD $(SBI_BUILD_DIR)/mysbi.elf"
	$(CMD_PREFIX)$(GNU)-objcopy $(SBI_BUILD_DIR)/mysbi.elf -O binary mysbi.bin; echo " OBJCOPY mysbi.bin"
	$(CMD_PREFIX)cp $(SBI_BUILD_DIR)/mysbi.elf mysbi.elf





# Qemu Configurations
QEMUOPTS = -M virt -m 256M -nographic -bios ./x-sbi.elf

# qemu run
run: ./x-sbi.elf
	$QEMU/qemu-system-riscv64 $(QEMUOPTS)







