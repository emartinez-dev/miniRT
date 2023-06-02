#include "objects.h"

unsigned int	rgb_to_hex(t_color color)
{
	unsigned int	result;

	result = 0;
	result |= ((unsigned char)color.r << 24);
	result |= ((unsigned char)color.g << 16);
	result |= ((unsigned char)color.b << 8);
	result |= 0x000000FF;
	return (result);
}
