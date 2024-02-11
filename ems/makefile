PROG_NAME=ems

PROG_CSRCS = main.c
PROG_SSRCS= isv.s

PROG_COBJS= $(patsubst %.c,%.o,$(PROG_CSRCS))
PROG_SOBJS= $(patsubst %.s,%.o,$(PROG_SSRCS))

SIM_CSRCS = main.c
SIM_SSRCS= 

SIM_COBJCS= $(patsubst %.c,%.o,$(SIM_CSRCS))
SIM_SOBJS= $(patsubst %.s,%.o,$(SIM_SSRCS))

CC=m68k-elf-gcc
CCFLAGS=-Wall -nostdlib -nodefaultlibs -m68000
AS=m68k-elf-as
ASFLAGS=
LD=m68k-elf-ld
#LD_OPTS=--defsym=_start=main -Ttext=0x2000 -Tdata=0x3000 -Tbss=0x4000 --section-start=.rodata=0x5000
LDFLAGS=-T ems.ld
OBJCOPY=m68k-elf-objcopy

all: $(PROG_COBJS) $(PROG_SOBJS)
	$(LD) $(LDFLAGS) $(PROG_COBJS) $(PROG_SOBJS) -o $(PROG_NAME).out
	$(OBJCOPY) -I elf32-m68k -O srec $(PROG_NAME).out $(PROG_NAME).srec

simall: $(SIM_SRCS) $(PROG_SOBJS)
	$(LD) $(LDFLAGS) $(PROG_COBJS) $(PROG_SOBJS) -o $(PROG_NAME).out
	$(OBJCOPY) -I elf32-m68k -O srec $(PROG_NAME).out $(PROG_NAME).srec

$(PROG_COBJS): %.o: %.c
	$(CC) $(CCFLAGS) -c $< -o $@

$(PROG_SOBJS): %.o: %.s
	$(AS) $(ASFLAGS) -o $@ $<

$(SIM_COBJS): %.o: %.c
	$(CC) $(CCFLAGS) -c $< -o $@

$(SIM_SOBJS): %.o: %.s
	$(AS) $(ASFLAGS) -o $@ $<

# generate assembly source for c file
%.s: %.c
	$(CC) $(CCFLAGS) -S $*.c -o $*.c.s

clean:
	rm -rf *.o *.out
