# Makefile for for ARM925EJ-S Core by layright

CC = arm-none-eabi-gcc
AS = arm-none-eabi-as
LD = arm-none-eabi-gcc

CCFLAGS = -g -c -Wall -std=c99 -pedantic -O0 -mcpu=arm926ej-s
ASFLAGS = -EL -mcpu=arm926ej-s -as -W -gstabs
LDFLAGS = -specs=nosys.specs -nostartfiles -fno-builtin -static -T link.ld 

SRC_C = main.o
SRC_ASM = start.o
BUILD_IMAGE = $(SRC_C) $(SRC_ASM)
FINAL_OUTPUT = final_image.elf

# Generation Rules
all: $(SRC_ASM) $(SRC_C) $(FINAL_OUTPUT)

main.o : main.c
	$(CC) $(CCFLAGS) $< -o $@

start.o : start.s
	$(AS) $(ASFLAGS) $< -o $@

$(FINAL_OUTPUT) : $(BUILD_IMAGE)
	$(LD) $(LDFLAGS) $(BUILD_IMAGE) -o $@ -Wl,-Map,final_image.txt

clean:
	@rm -v -f *.elf *.o *.txt *~
