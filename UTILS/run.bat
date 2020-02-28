@echo off
if %1 == -64 (
	echo WARNING: Remember to delete [org 0x7c00], we dont need it here!
	echo boot64
	rm -f *.bin *.tmp *.sym *.elf
	nasm %2 -f elf64 -F dwarf -g -o boot.elf
	objcopy --only-keep-debug boot.elf boot.sym
	objcopy --strip-debug boot.elf
	ld -Ttext=0x7c00 -o boot.tmp boot.elf
	objcopy -O binary -j .text boot.tmp boot.bin
	mintty.exe -e ./gdb.sh
	"C:\Program Files\qemu\qemu-system-x86_64" -s -S -fda boot.bin
) else (
	echo boot32
	nasm %1 -f bin -o boot.bin
	"C:\Program Files\qemu\qemu-system-i386.exe" -fda boot.bin
)