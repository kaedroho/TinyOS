#include <kernel.h>
#include <io.h>

struct keyboard_key
{
	char value;
	char shiftvalue;
	int pressed;
} keyboard_keys[128];


void keyboard_handler(struct regs *r)
{
//Get scancode
	unsigned char scancode;
	scancode = inportb(0x60);

//Check if the key has been pressed or released
	if (scancode & 0x80)
		keyboard_keys[scancode & 0x7F].pressed = 0;
	else
		keyboard_keys[scancode].pressed = 1;
}


void keyboard_setup()
{
//Set handler
	irq_set_handler(1, keyboard_handler);
}
