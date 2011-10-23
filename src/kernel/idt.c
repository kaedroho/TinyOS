#include <kernel.h>
#include <lib.h>


struct idt_entry
{
	unsigned short base_low;
	unsigned short selector;
	unsigned char always0;
	unsigned char flags;
	unsigned short base_high;
} __attribute__((packed));

struct idt_ptr
{
	unsigned short limit;
	unsigned int base;
} __attribute__((packed));

struct idt_entry idt_table[256];
struct idt_ptr idt_pointer;

extern void idt_load(); //Defined in idt.s


void idt_set_gate(unsigned char num, unsigned long base, unsigned short selector, unsigned char flags)
{
//Set base address
	idt_table[num].base_low = (base & 0xFFFF);
	idt_table[num].base_high = (base >> 16) & 0xFFFF;

//Set other values
	idt_table[num].selector = selector;
	idt_table[num].always0 = 0;
	idt_table[num].flags = flags;
}


void idt_setup()
{
//Setup the IDT pointer and limit
	idt_pointer.limit = (sizeof (struct idt_entry) * 256) - 1;
	idt_pointer.base = &idt_table;

//Clear IDT
	memset(&idt_table, 0, sizeof(struct idt_entry) * 256);

//Points the processor's internal register to the new IDT
	idt_load();
}
