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

t_color	color_sum(t_color color1, t_color color2)
{
	t_color	color;

	color.r = color1.r + color2.r;
	color.g = color1.g + color2.g;
	color.b = color1.b + color2.b;
	color = clamp_colors(color);
	return (color);
}

t_color color_norm(t_color color1)
{
	int	max;

	if (color1.r >= color1.g && color1.r >= color1.b)
		max = color1.r;
	else if (color1.g >= color1.r && color1.g >= color1.b)
		max = color1.g;
	else
		max = color1.b;
	if (max >= 0 && max <= 255)
		return (color1);
	color1.r /= max;
	color1.g /= max;
	color1.b /= max;
	color1.r *= 255;
	color1.g *= 255;
	color1.b *= 255;
	return (color1);
}

