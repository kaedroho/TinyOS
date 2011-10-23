#ifndef _KAOS_KERNEL_H
#define _KAOS_KERNEL_H

//System (SYS)
unsigned char inportb (unsigned short _port);
void outportb (unsigned short _port, unsigned char _data);

//Global Descriptor Table (GDT)
void gdt_setup();


//Interrupt Descriptor Table (IDT)
void idt_set_gate(unsigned char num, unsigned long base, unsigned short selector, unsigned char flags);
void idt_setup();

struct regs
{
    unsigned int gs, fs, es, ds;
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;
    unsigned int int_no, err_code;
    unsigned int eip, cs, eflags, useresp, ss;
};


//Interrupt service routines (ISR)
void isr_setup();


//Interrupt requests (IRQ)
void irq_set_handler(int irq, void (*handler)(struct regs* r));
void irq_unset_handler(int irq);
void irq_setup();


//Timer
void timer_setup();

//Panic
void panic(struct regs* r);

#endif
