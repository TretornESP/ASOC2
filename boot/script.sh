rm *.o *.bin *.elf
nasm -f elf64 boot.asm -o boot.o

gcc -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./include  -c -o idt.o idt.c

gcc -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./include  -c -o isrs.o isrs.c

gcc -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./include  -c -o irq.o irq.c

#gcc -ffreestanding -nostdlib -mno-red-zone -fno-exceptions -m64 kernel.c idt.c boot.o -o kernel.bin -T link.ld
gcc -ffreestanding -nostdlib -mno-red-zone -fno-exceptions -m64 kernel.c boot.o idt.o isrs.o irq.o -o kernel.bin -T link.ld
qemu-system-x86_64 -fda kernel.bin -cpu qemu64 -d page
