#include "objects.h"
#include "engine.h"

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

t_color	hex_to_rgb(int color)
{
	t_color	result;

	result.b = (color >> 16) & 0xff;
	result.g = (color >> 8) & 0xff;
	result.r = color & 0xff;
	result = clamp_colors(result);
	return (result);
}

t_color	clamp_colors(t_color color)
{
	color.r = min(color.r, 255);
	color.g = min(color.g, 255);
	color.b = min(color.b, 255);
	color.r = max(color.r, 0);
	color.g = max(color.g, 0);
	color.b = max(color.b, 0);
	return (color);
}

t_color	color_div(t_color color, int div)
{
	color.r = color.r / div;
	color.g = color.g / div;
	color.b = color.b / div;
	color = clamp_colors(color);
	return (color);
}

t_color	color_sum(t_color color1, t_color color2)
{
	t_color	color;

	color.r = color1.r + color2.r;
	color.g = color1.g + color2.g;
	color.b = color1.b + color2.b;
//	color = clamp_colors(color);
	return (color);
}
