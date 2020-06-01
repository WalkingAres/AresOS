CC = x86_64-elf-gcc
LD = x86_64-elf-ld

INCLUDE = -I include/
KernLib = -I kernel/ -I kernel/lib/ -I kernel/interrupt

CFLAGS 	= -m32 -march=i386 -mpreferred-stack-boundary=2 -ffreestanding -fno-builtin -c
#CFLAGS 	= -m32 -fno-builtin -c
LDFLAGS =  -m elf_i386 -Ttext 0x30400 -s
#LDFLAGS =   -Ttext 0x30400 -s
KernInc = -I $(INCLUDE) kernel/

kernobj = run/kernel1.o run/kernel2.o run/init.o  run/string.o run/kernlib.o run/int.o run/pm.o run/video.o \
		run/clock.o run/keyboard.o run/global.o run/time.o
kerntarget = run/kernel.bin
OUT = -o $@ $<

.PONY : all kernel.bin copy 

all : kernel.bin copy

kernel.bin:
$(kerntarget) : $(kernobj)
	$(LD) $(LDFLAGS) $(kernobj) -o $(kerntarget)
run/kernel2.o : kernel/kernel.c
	$(CC) $(CFLAGS)  $(INCLUDE) $(KernLib) $(OUT)
run/kernel1.o : kernel/kernel.asm
	nasm -f elf $(OUT)
run/init.o : kernel/init.c
	$(CC) $(CFLAGS) $(INCLUDE) $(KernLib) $(OUT)
run/kernlib.o : kernel/lib/kernlib.asm
	nasm -f elf $(OUT)
run/int.o : kernel/interrupt/int.c
	$(CC) $(CFLAGS) $(INCLUDE) $(KernLib) $(OUT)
run/pm.o : kernel/pm.c
	$(CC) $(CFLAGS) $(INCLUDE) $(KernLib) $(OUT)
run/string.o : lib/string.asm 
	nasm -f elf -I lib/ $(OUT)
run/video.o : kernel/lib/video.asm
	nasm -f elf $(OUT)
run/clock.o : kernel/interrupt/clock.c
	$(CC) $(CFLAGS) $(INCLUDE) $(KernLib) $(OUT)
run/keyboard.o : kernel/interrupt/keyboard.c
	$(CC) $(CFLAGS) $(INCLUDE) $(KernLib) $(OUT)
run/global.o : kernel/global.c
	$(CC) $(CFLAGS) $(INCLUDE) $(KernLib) $(OUT)
run/time.o : kernel/interrupt/time.c
	$(CC) $(CFLAGS) $(INCLUDE) $(KernLib) $(OUT)

copy : run/kernel.bin

	cp run/kernel.bin  /Volumes/ARESOS/

start:
	bochs -f run/bochsrc

clean:
		rm -r -f run/*.bin run/*.o
