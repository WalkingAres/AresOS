k:
		nasm -f elf -o run/kernel1.o kernel/kernel.asm
		x86_64-elf-gcc -m32 -m32 -march=i386 -mpreferred-stack-boundary=2 -ffreestanding -c kernel/kernel.c -o run/kernel2.o -I include/
		x86_64-elf-gcc -m32 -m32 -march=i386 -mpreferred-stack-boundary=2 -ffreestanding -c kernel/global.c -o run/global.o -I include/
loader:
		nasm -o loader.bin loader.asm

string:
		#run/string.o : lib/string.asm
		nasm -I lib/ -f elf lib/string.asm -o run/string.o
all:
		x86_64-elf-ld -m elf_i386 -Ttext 0x30400 -s run/kernel1.o run/kernel2.o run/global.o run/str.o -o run/kernel.bin

clean:
		rm -r -f run/*.bin run/*.o

CC = x86_64-elf-gcc
LD = x86_64-elf-ld

INCLUDE = include/

CFLAGS 	= -m32 -march=i386 -mpreferred-stack-boundary=2 -ffreestanding -fno-builtin -c
LDFLAGS =  -m elf_i386 -Ttext 0x30400 -s
KernInc = -I $(INCLUDE) kernel/

kernpre = run/kernel1.o run/kernel2.o run/init.o run/global.o run/string.o
kerntarget = run/kernel.bin
kern: 
	#run/kernel.bin : kernel/kernel.asm kernel/kernel.c kernel/init.c kernel/global.c
	$(CC) $(CFLAGS) -I $(INCLUDE) kernel/kernel.c -o run/kernel2.o
	nasm -f elf kernel/kernel.asm -o run/kernel1.o
	$(CC) $(CFLAGS) -I $(INCLUDE) kernel/init.c -o run/init.o
	$(CC) $(CFLAGS) -I $(INCLUDE) kernel/global.c -o run/global.o
	$(LD) $(LDFLAGS) $(kernpre) -o $(kerntarget)
