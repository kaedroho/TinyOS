#include <lib.h>

void memcpy(void* dest, const void* src, int bytes)
{
//Check that theres some data to copy
	if (bytes > 0){
	//Copy the data
		int i = 0;
		for (i = 0; i<bytes; i++)
			((char*)dest)[i] = ((char*)src)[i];
	}
}

void memset(void* dest, int val, int bytes)
{
//Check that theres some data set
	if (bytes > 0){
	//Set the data
		int i = 0;
		for (i = 0; i<bytes; i++)
			((char*)dest)[i] = val;
	}
}
