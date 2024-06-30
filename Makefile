# kernel/{include/src}
# usr/{include/src/scripts} 

# X_SBI_TEXT_START
# X_SBI_PAYLOAD_PATH 0x8000 0000
# KERNEL_TEXT_START 0x8020 0000

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

# Qemu Configurations
QEMUOPTS = -machine virt -bios none -kernel $K/kernel -m 128M -nographic
QEMUOPTS += -global virtio-mmio.force-legacy=false
QEMUOPTS += -drive file=fs.img,if=none,format=raw,id=x0
QEMUOPTS += -device virtio-blk-device,drive=x0,bus=virtio-mmio-bus.0

-M virt -m 256M -nographic -bios fw_payload.elf





