rm obj/*.o bin/*.bin
nasm -f elf64 boot.asm -o obj/boot.o
nasm -f elf64 cpu/int.s -o obj/int.o
nasm -f elf64 cpu/cpu.s -o obj/cpu.o
gcc -ffreestanding -nostdlib -mno-red-zone -fno-exceptions -m64 kernel.c cpu/*.c mem/*.c lib/*.c obj/*.o -o bin/kernel.bin -T link.ld
