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
		video_text_currentx++;

	//Wrap cursor
		if (video_text_currentx >= video_text_framebuffer.xsize)
			video_text_newline();
	}
}

void video_text_newline()
{
//Zero x
	video_text_currentx = 0;

//Increment y
	video_text_currenty++;
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
