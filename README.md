# ASOC2 Bootloader

Coordinador: Nico Alonso

Prefacio:
	Contamos con un sistema pensado para arquitecturas de 64 bits acorde al manual
	de ensamblador de Intel que ya conoceis.

Preguntas:
	1. Describe el proceso que sigue tu máquina hasta que ejecuta la primera linea de
	tu boot.asm.

	2. Que información pone la bios a nuestra disposición cuando empezamos a ejecutar
	el bootloader?

	3. Describe el proceso que seguiremos para avanzar de los 16 a 32 bits y de 32 a 64
	
-----

4. Vais a usar BIOS o UEFI?

Appendix: https://www.amd.com/system/files/TechDocs/24593.pdf 
Es bastante mas simple que el manual de Intel
https://blog.ghaiklor.com/2017/11/02/how-to-implement-a-second-stage-boot-loader/


Lugares donde sacamos lo de la IDT:

Load IDT: http://www.osdever.net/bkerndev/Docs/idt.htm
ISRS: http://www.osdever.net/bkerndev/Docs/isrs.htm
IRQ: http://www.osdever.net/bkerndev/Docs/irqs.htm
