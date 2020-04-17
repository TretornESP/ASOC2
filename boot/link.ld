OUTPUT_FORMAT("binary");
ENTRY(boot);
SECTIONS
{
    . = 0x7C00;
    .text : {
        *(.boot);
        *(.text);
    }

    .rodata : SUBALIGN(4) {
        *(.rodata);
    }

    .data : SUBALIGN(4) {
        *(.data);
    }

    .stack : SUBALIGN(4) {
      *(.stack);
    }

    .bss : SUBALIGN(4) {
        *(.bss)
    }

    /DISCARD/ : {
        *(.eh_frame);
        *(.comment);
        *(.note.gnu.build-id);
    }
}
