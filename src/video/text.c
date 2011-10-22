#include <video.h>

static int video_text_currentx = 0;
static int video_text_currenty = 0;
static int video_text_currentcolour = 0x0F;

static struct video_framebuffer video_text_framebuffer = {0xB8000, 80, 25, 2};


void video_text_putchar(char character)
{
//Check if this is a newline
	if (character == '\n')
		video_text_newline();
	else {
	//Put character into cursor position
		short value = (video_text_currentcolour << 8) | character;
		video_putpixel(&video_text_framebuffer, video_text_currentx, video_text_currenty, &value);

	//Move cursor right
		int newx = video_text_currentx + 1;

	//Wrap cursor
		if (newx >= video_text_framebuffer.xsize)
			video_text_newline();
		else
			video_text_setcursorposition(newx, video_text_currenty);
	}
}

void video_text_scroll()
{

}

void video_text_newline()
{
//Find where the next line is
	int newy = video_text_currenty + 1;

//Check that cursor is still on screen
	if (newy >= video_text_framebuffer.ysize) {
		newy--;
		video_text_scroll();
	}

//Set cursor position
	video_text_setcursorposition(0, newy);
}

void video_text_setcursorposition(int x, int y)
{
//Set vars
	video_text_currentx = x;
	video_text_currenty = y;
}

void video_text_cls()
{

}

void video_text_puttext(const char* string)
{
//Loop through characters
	int i = 0;
	while (string[i] != 0) {
	//Send to putchar and inc i
		video_text_putchar(string[i]);
		i++;
	}
}
