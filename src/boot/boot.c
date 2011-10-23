#include <kernel.h>
#include <video.h>


void boot()
{
//Initialise display and print message
	video_text_cls();
	video_text_puttext("KAOS version 1\nDeveloped by Karl Hobley.\n\nCopyleft (C) 2011 Karl Hobley.\nKAOS is released under the GPLv3 Licence.\n\nBuild date: "__DATE__" "__TIME__"\n\n\n\n");

//Setup kernel
	video_text_puttext("Loading GDT          ");
	gdt_setup();
	video_text_puttext("[ DONE ]\n");

	video_text_puttext("Loading IDT          ");
	idt_setup();
	video_text_puttext("[ DONE ]\n");

	video_text_puttext("Loading ISR          ");
	isr_setup();
	video_text_puttext("[ DONE ]\n");

	video_text_puttext("Loading IRQ          ");
	irq_setup();
	video_text_puttext("[ DONE ]\n");

	video_text_puttext("Enabling Interrupts  ");
	__asm__ __volatile__("sti"); 
	video_text_puttext("[ DONE ]\n");

	video_text_puttext("Loading Timer        ");
	timer_setup();
	video_text_puttext("[ DONE ]\n");

	video_text_puttext("Loading Keyboard     ");
	keyboard_setup();
	video_text_puttext("[ DONE ]\n");

//Test panic
	volatile int a = 1;
	volatile int b = 0;
	volatile int c = a / b;
}
