#include <kernel.h>


struct gdt_entry
{
	unsigned short limit_low;
	unsigned short base_low;
	unsigned char base_middle;
	unsigned char access;
	unsigned char granularity;
	unsigned char base_high;
} __attribute__((packed));

struct gdt_ptr
{
	unsigned short limit;
	unsigned int base;
} __attribute__((packed));


#define GDT_ENTRY_COUNT 3

struct gdt_entry gdt_table[GDT_ENTRY_COUNT];
struct gdt_ptr gdt_pointer;

extern void gdt_load(); //Defined in gdt.s


void gdt_set_descriptor(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran)
{
//Setup the descriptor base address
	gdt_table[num].base_low = (base & 0xFFFF);
	gdt_table[num].base_middle = (base >> 16) & 0xFF;
	gdt_table[num].base_high = (base >> 24) & 0xFF;

 //Setup the descriptor limits
	gdt_table[num].limit_low = (limit & 0xFFFF);
	gdt_table[num].granularity = ((limit >> 16) & 0x0F);

 //Finally, set up the granularity and access flags
	gdt_table[num].granularity |= (gran & 0xF0);
	gdt_table[num].access = access;
}


void gdt_setup()
{
//Setup the GDT pointer and limit
	gdt_pointer.limit = (sizeof(struct gdt_entry) * GDT_ENTRY_COUNT) - 1;
	gdt_pointer.base = &gdt_table;

//NULL descriptor
	gdt_set_descriptor(0, 0, 0, 0, 0);

//Code segment
	gdt_set_descriptor(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);

//Data Segment
	gdt_set_descriptor(2, 0, 0xFFFFFFFF, 0x92, 0xCF);

//Load the new GDT
	gdt_load();
}
