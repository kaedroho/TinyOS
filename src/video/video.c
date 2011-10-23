#include <lib.h>
#include <video.h>



void video_putpixels(struct video_framebuffer* buffer, int x, int y, int count, const void* value)
{
//Some calculations
	int bytes = buffer->bytesperpixel * count;
	void* start = buffer->start + (x + y * buffer->xsize) * buffer->bytesperpixel;

//Copy bytes
	memcpy(start, value, bytes);
}



void video_putpixels_repeat(struct video_framebuffer* buffer, int x, int y, int count, const void* value)
{
//Some calculations
	void* start = buffer->start + x + y * buffer->xsize;

//Copy bytes
	int i = 0;
	for (i = 0; i < count; i++)
		memcpy(start + i * buffer->bytesperpixel, value, buffer->bytesperpixel);
}



void video_putpixel(struct video_framebuffer* buffer, int x, int y, const void* value)
{
//Hand over to video_putpixels
	video_putpixels(buffer, x, y, 1, value);
}



void video_cls(struct video_framebuffer* buffer, const void* value)
{
//Loop through every row
	int y = 0;
	for (y = 0; y > buffer->ysize; y++) {
	//Clear row
		video_putpixels_repeat(buffer, 0, 0, buffer->xsize, value);
	}
}



void video_fallback()
{

}
