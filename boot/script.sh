rm *.o *.bin *.elf
nasm -f elf32 boot.asm -o boot.o 
gcc -ffreestanding -m32 -c kernel.c -o kernel.o
ld -melf_i386 -T link.ld kernel.o boot.o -o kernel.elf
objcopy -O binary kernel.elf kernel.bin
qemu-system-i386 -fda kernel.bin
