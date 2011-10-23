#include <kernel.h>


static int timer_ticks = 0;

void timer_handler(struct regs *r)
{
//Increment ticks
	timer_ticks++;
}


void timer_setup()
{
//Set phase to 100hz
	int divisor = 1193180 / 100;
	outportb(0x43, 0x36);
	outportb(0x40, divisor & 0xFF);
	outportb(0x40, divisor >> 8);

//Set handler
	irq_set_handler(0, timer_handler);
}
