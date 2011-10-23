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
//Calculate pixel
	short pixel = video_text_currentcolour << 8;

//Put the pixel into every block on the screen
	video_putpixels_repeat(&video_text_framebuffer, 0, 0, 80 * 25, &pixel);
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

void video_text_putuintf(int value, int base, int length, char fill)
{
//Check base
	if (base < 2 || base > 16)
		return;

//Characters
	char* characters = "X0123456789ABCDEF";
	characters[0] = fill;

//Allocate buffer
	unsigned int buffer[32]= {0};

//Loop through bits
	int i = 0;
	for (i = 0; i < 32; i++) {
	//Check if bit is set
		if (value & (0x1 << i)) {
		//Add bit to buffer
			buffer[0] += (0x1 << i);

		//Update length
			if (length == 0)
				length = 1;

		//Check for overflows and correct them
			int i2 = 0;
			for (i2 = 0; i2 < 31; i2++) {
			//Check if this character has overflown
				if (buffer[i2] >= base) {
				//Move extra to next character
					int newval = buffer[i2] % base;
					buffer[i2 + 1] += (buffer[i2] - newval) / base;
					buffer[i2] = newval;

				//Update length
					if (length < i2 + 2)
						length = i2 + 2;
				}else
					break;
			}
		}
	}

//Print buffer
	int shift = 0;
	for (i = 0; i < length; i++) {
		if (buffer[length - i - 1] > 0)
			shift = 1;
		video_text_putchar(characters[buffer[length - i - 1] + (shift || i == (length - 1))]);
	}
}

void video_text_putuint(int value, int base)
{
//Pass through to other function
	video_text_putuintf(value, base, 0, '0');
}

void video_text_setcolour(int colour)
{
//Set colour
	video_text_currentcolour = colour;
}
