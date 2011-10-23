#include <kernel.h>
#include <video.h>


char* panic_exception_messages[] = {
	"Division By Zero",
	"Debug",
	"Non Maskable Interrupt",
	"Breakpoint",
	"Into Detected Overflow",
	"Out of Bounds",
	"Invalid Opcode",
	"No Coprocessor",
	"Double Fault",
	"Coprocessor Segment Overrun",
	"Bad TSS",
	"Segment Not Present",
	"Stack Fault",
	"General Protection Fault",
	"Page Fault",
	"Unknown Interrupt",
	"Coprocessor Fault",
	"Alignment Check",
	"Machine Check",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown"
};

void panic(struct regs* r)
{
//Force video device back into text mode
	video_fallback();

//Set colour to white on red
	video_text_setcolour(0x4F);

//Clear screen
	video_text_cls();

//Position cursor to beginning
	video_text_setcursorposition(0, 0);

//Print error
	video_text_puttext("An exception has occurred.\nException: (");
	video_text_putuint(r->int_no, 10);
	video_text_puttext(") - ");
	video_text_puttext(panic_exception_messages[r->int_no]);
	video_text_puttext("\n\nSystem Halted.\n\n");

//Print error code
	video_text_puttext("Technical Information:\n\nError Code:  ");
	video_text_putuint(r->err_code, 16);

//Print registers
	video_text_puttext("\nRegisters:   EAX: "); video_text_putuintf(r->eax, 16, 8, ' ');
	video_text_puttext("\n             EBX: "); video_text_putuintf(r->ebx, 16, 8, ' ');
	video_text_puttext("\n             ECX: "); video_text_putuintf(r->ecx, 16, 8, ' ');
	video_text_puttext("\n             EDX: "); video_text_putuintf(r->edx, 16, 8, ' ');
	video_text_puttext("\n             ESI: "); video_text_putuintf(r->esi, 16, 8, ' ');
	video_text_puttext("\n             EDI: "); video_text_putuintf(r->edi, 16, 8, ' ');
	video_text_puttext("\n             ESP: "); video_text_putuintf(r->esp, 16, 8, ' ');
	video_text_puttext("\n             EBP: "); video_text_putuintf(r->ebp, 16, 8, ' ');
	video_text_puttext("\n              CS: "); video_text_putuintf(r->cs, 16, 8, ' ');
	video_text_puttext("\n              DS: "); video_text_putuintf(r->ds, 16, 8, ' ');
	video_text_puttext("\n              ES: "); video_text_putuintf(r->es, 16, 8, ' ');
	video_text_puttext("\n              FS: "); video_text_putuintf(r->fs, 16, 8, ' ');
	video_text_puttext("\n              GS: "); video_text_putuintf(r->gs, 16, 8, ' ');
	video_text_puttext("\n              SS: "); video_text_putuintf(r->ss, 16, 8, ' ');
	video_text_puttext("\n             EIP: "); video_text_putuintf(r->eip, 16, 8, ' ');

//Endless loop
	for (;;)
		__asm__ __volatile__ ("hlt");
}
