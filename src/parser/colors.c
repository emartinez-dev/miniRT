/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 13:31:35 by franmart          #+#    #+#             */
/*   Updated: 2023/09/12 13:31:36 by franmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	get_color(char *str, t_color *color)
{
	char	**split;

	split = ft_split(str, ',');
	if (matrix_len(split) == 3)
	{
		color->r = ft_atoi(split[0]);
		color->g = ft_atoi(split[1]);
		color->b = ft_atoi(split[2]);
	}
	else
	{
		color->r = -1;
		color->g = -1;
		color->b = -1;
	}
	free_matrix(split);
}

void	color_to_vec(t_color *c, t_v3 *v_c)
{
	v_c->x = c->r;
	v_c->y = c->g;
	v_c->z = c->b;
}

t_color	vec_to_color(t_v3 v_c)
{
	t_color	c;

	c.r = v_c.x;
	c.g = v_c.y;
	c.b = v_c.z;
	return (c);
}
