#include <video.h>


void main();

void boot()
{
//Initialise display and print message
	video_text_cls();
	video_text_puttext("KAOS version 1\nDeveloped by Karl Hobley.\n\nCopyleft (C) 2011 Karl Hobley.\nKAOS is released under the GPLv3 Licence.\n\nBuild date: "__DATE__"  "__TIME__);

//Call main function
	main();
}
