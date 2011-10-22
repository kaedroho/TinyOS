#ifndef _KAOS_VIDEO_H
#define _KAOS_VIDEO_H

struct video_framebuffer
{
	void* start;
	int xsize;
	int ysize;
	int bytesperpixel;
};

void video_putpixels(struct video_framebuffer* buffer, int x, int y, int count, const void* value);
void video_putpixels_repeat(struct video_framebuffer* buffer, int x, int y, int count, const void* value);
void video_putpixel(struct video_framebuffer* buffer, int x, int y, const void* value);
void video_cls(struct video_framebuffer* buffer, const void* value);

void video_text_puttext(const char* string);
void video_text_putchar(char character);
void video_text_scroll();
void video_text_newline();
void video_text_setcursorposition(int x, int y);
void video_text_cls();

#endif
