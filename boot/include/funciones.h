/* This defines what the stack looks like after an ISR was running */
#ifndef __FUNCIONES_H
#define __FUNCIONES_H

typedef int size_t;

struct regs
{
    unsigned int gs, fs, es, ds;
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;
    unsigned int int_no, err_code;
    unsigned int eip, cs, eflags, useresp, ss;    
};

/* KERNEL.C */
void memset(unsigned char * dst, const unsigned char val, size_t size);
size_t strlen(unsigned char * string);
void putc(unsigned char chr, unsigned char color);
void puts(unsigned char * str);

/* IDT.C */
extern void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags);
extern void idt_install();

/* ISRS.C */
extern void isrs_install();

/* IRQ.C */
extern void irq_install_handler(int irq, void (*handler)(struct regs *r));
extern void irq_uninstall_handler(int irq);
extern void irq_install();

#endif
