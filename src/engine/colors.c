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

t_color	clamp_colors(t_color color)
{
	if (color.r > 255)
		color.r = 255;
	if (color.r < 0)
		color.r = 0;
	if (color.g > 255)
		color.g = 255;
	if (color.g < 0)
		color.g = 0;
	if (color.b > 255)
		color.b = 255;
	if (color.b < 0)
		color.b = 0;
	return (color);
}