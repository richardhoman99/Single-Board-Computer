PROG_NAME=ems

PROG_CSRCS = main.c isr.c convert.c lsrec.c mem.c
PROG_SSRCS= isv.s
PROG_COBJS= $(patsubst %.c,%.o,$(PROG_CSRCS))
PROG_SOBJS= $(patsubst %.s,%.o,$(PROG_SSRCS))
PROG_LDSRPT= ems.ld

SIM_CSRCS = main.c serial-sim.c convert.c lsrec.c mem.c
SIM_SSRCS= 
SIM_COBJS= $(patsubst %.c,%.sim.o,$(SIM_CSRCS))
SIM_SOBJS= $(patsubst %.s,%.sim.o,$(SIM_SSRCS))
SIM_LDSRPT= ems-sim.ld

CC=m68k-elf-gcc
CCFLAGS=-Wall -nostdlib -nodefaultlibs -m68000
AS=m68k-elf-as
ASFLAGS=
LD=m68k-elf-ld
#LD_OPTS=--defsym=_start=main -Ttext=0x2000 -Tdata=0x3000 -Tbss=0x4000 --section-start=.rodata=0x5000
LDFLAGS=
OBJCOPY=m68k-elf-objcopy
OBJCOPYFLAGS=-I elf32-m68k -O srec --srec-len=16

all: $(PROG_COBJS) $(PROG_SOBJS)
	$(LD) $(LDFLAGS) -T ${PROG_LDSRPT} $(PROG_COBJS) $(PROG_SOBJS) -o $(PROG_NAME).out
	$(OBJCOPY) $(OBJCOPYFLAGS) $(PROG_NAME).out $(PROG_NAME).srec

sim: $(SIM_COBJS) $(SIM_SOBJS)
	$(LD) $(LDFLAGS) -T ${SIM_LDSRPT} $(SIM_COBJS) $(SIM_SOBJS) -o $(PROG_NAME).sim.out
	$(OBJCOPY) $(OBJCOPYFLAGS) $(PROG_NAME).sim.out $(PROG_NAME).sim.S68

$(PROG_COBJS): %.o: %.c
	$(CC) $(CCFLAGS) -c $< -o $@

$(PROG_SOBJS): %.o: %.s
	$(AS) $(ASFLAGS) -o $@ $<

$(SIM_COBJS): %.sim.o: %.c
	$(CC) $(CCFLAGS) -c $< -o $@

$(SIM_SOBJS): %.sim.o: %.s
	$(AS) $(ASFLAGS) -o $@ $<

# generate assembly source for c file
%.s: %.c
	$(CC) $(CCFLAGS) -S $*.c -o $*.c.s

clean:
	rm -rf *.o *.out
