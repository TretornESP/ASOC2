rm *.o *.bin *.elf
nasm -f elf64 boot2.asm -o boot.o 
gcc -ffreestanding -nostdlib -mno-red-zone -fno-exceptions -m64 kernel.c boot.o -o kernel.bin -T link.ld
qemu-system-x86_64 -fda kernel.bin -cpu qemu64 -d page
