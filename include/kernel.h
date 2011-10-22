#ifndef _KAOS_KERNEL_H
#define _KAOS_KERNEL_H

//Global Descriptor Table (GDT)
void gdt_setup();


//Interrupt Descriptor Table (IDT)
void idt_set_gate(unsigned char num, unsigned long base, unsigned short selector, unsigned char flags);
void idt_setup();

struct regs
{
    unsigned int gs, fs, es, ds;      /* pushed the segs last */
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;  /* pushed by 'pusha' */
    unsigned int int_no, err_code;    /* our 'push byte #' and ecodes do this */
    unsigned int eip, cs, eflags, useresp, ss;   /* pushed by the processor automatically */ 
};


//Interrupt service routines (ISR)
void isr_setup();

#endif
