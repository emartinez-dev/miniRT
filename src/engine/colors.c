/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-aga <juan_aga@student.42malaga.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 14:47:14 by juan-aga          #+#    #+#             */
/*   Updated: 2023/09/12 14:47:15 by juan-aga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

t_color	color_sum(t_color color1, t_color color2)
{
	t_color	color;

	color.r = color1.r + color2.r;
	color.g = color1.g + color2.g;
	color.b = color1.b + color2.b;
	color = clamp_colors(color);
	return (color);
}

t_color	color_norm(t_color color)
{
	int	max_color;

	max_color = max(color.r, color.g);
	max_color = max(max_color, color.b);
	if (max_color >= 0 && max_color <= 255)
		return (color);
	color.r /= max_color;
	color.g /= max_color;
	color.b /= max_color;
	color.r *= 255;
	color.g *= 255;
	color.b *= 255;
	return (color);
}
