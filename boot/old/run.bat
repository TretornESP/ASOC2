@echo off
if %1 == -64 (
	echo boot64
	"C:\Program Files\qemu\qemu-system-x86_64" -s -S %2
) else (
	echo boot32
	"C:\Program Files\qemu\qemu-system-i386.exe" %1
)