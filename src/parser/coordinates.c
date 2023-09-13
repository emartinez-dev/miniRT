/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coordinates.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 13:31:39 by franmart          #+#    #+#             */
/*   Updated: 2023/09/12 13:31:44 by franmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	get_xyz(char *str, t_v3 *point, t_object *obj)
{
	char	**split;

	split = ft_split(str, ',');
	if (matrix_len(split) == 3)
	{
		point->x = ft_atof(split[0]);
		point->y = ft_atof(split[1]);
		point->z = ft_atof(split[2]);
	}
	else
	{
		obj->error = 1;
		point->x = 0;
		point->y = 0;
		point->z = 0;
	}
	free_matrix(split);
}
