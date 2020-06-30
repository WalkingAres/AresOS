CC = x86_64-elf-gcc
LD = x86_64-elf-ld

INCLUDE = -I include/ -I mm/
KernLib = -I kernel/ -I kernel/lib/ -I kernel/interrupt -I kernel/drive -I lib/

CFLAGS 	= -m32 -march=i386 -mpreferred-stack-boundary=2 -ffreestanding -fno-builtin -c
#CFLAGS 	= -m32 -fno-builtin -c
LDFLAGS =  -m elf_i386 -Ttext 0x30400 -s
#LDFLAGS =   -Ttext 0x30400 -s
KernInc = -I $(INCLUDE) kernel/

kernobj = run/kernel1.o run/kernel2.o run/init.o  run/string.o run/kernlib1.o run/kernlib2.o \
		run/int.o run/pm.o run/video.o \
		run/clock.o run/keyboard.o run/global.o run/time.o run/hd.o run/syscall.o \
		run/shell.o run/proc.o run/stdio.o run/malloc.o
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
run/kernlib1.o : kernel/lib/kernlib.asm
	nasm -f elf $(OUT)
run/kernlib2.o : kernel/lib/kernlib.c
	$(CC) $(CFLAGS) $(INCLUDE) $(KernLib) $(OUT)
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
run/hd.o : kernel/drive/hd.c
	$(CC) $(CFLAGS) $(INCLUDE) $(KernLib) $(OUT)
run/syscall.o : kernel/interrupt/syscall.c
	$(CC) $(CFLAGS) $(INCLUDE) $(KernLib) $(OUT)
run/shell.o : kernel/shell.c
	$(CC) $(CFLAGS) $(INCLUDE) $(KernLib) $(OUT)
run/proc.o : include/proc.c
	$(CC) $(CFLAGS) $(INCLUDE) $(KernLib) $(OUT)
run/stdio.o : include/stdio.c
	$(CC) $(CFLAGS) $(INCLUDE) $(KernLib) $(OUT)
run/malloc.o : mm/malloc.c
	$(CC) $(CFLAGS) $(INCLUDE) $(KernLib) $(OUT)


copy : run/kernel.bin run/a.bin run/b.bin  run/c.bin  run/d.bin 

	cp run/kernel.bin  /Volumes/ARESOS/
run/a.bin : user/a.asm
	nasm $(OUT)
	dd if=run/a.bin of=run/diskb.img conv=notrunc
	dd if=run/a.bin of=run/diska.vhd conv=notrunc
run/b.bin : user/b.asm
	nasm $(OUT)
	dd if=run/b.bin of=run/diskb.img seek=2 bs=512 conv=notrunc
	dd if=run/b.bin of=run/diska.vhd seek=2 bs=512 conv=notrunc
run/c.bin : user/c.asm
	nasm $(OUT)
	dd if=run/c.bin of=run/diskb.img seek=4 bs=512 conv=notrunc
	dd if=run/c.bin of=run/diska.vhd seek=4 bs=512 conv=notrunc

run/d.bin : user/d.asm
	nasm $(OUT)
	dd if=run/d.bin of=run/diskb.img seek=6 bs=512 conv=notrunc
	dd if=run/d.bin of=run/diska.vhd seek=6 bs=512 conv=notrunc

start:
	bochs -f run/bochsrc

clean:
		rm -r -f run/*.bin run/*.o
