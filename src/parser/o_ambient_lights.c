/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o_ambient_lights.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 13:31:53 by franmart          #+#    #+#             */
/*   Updated: 2023/09/12 13:31:54 by franmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "objects.h"

t_object	*parse_obj_ambient_light(char *line)
{
	t_object	*obj;
	t_amb_light	*light;
	char		**split;

	obj = ft_calloc(1, sizeof(t_object));
	obj->type = OBJ_AMBIENT_LIGHT;
	obj->error = 0;
	split = ft_split(line, ' ');
	light = ft_calloc(1, sizeof(t_amb_light));
	obj->ptr = light;
	if (matrix_len(split) == 3)
	{
		light->ratio = ft_atof(split[1]);
		get_color(split[2], &light->c);
		color_to_vec(&light->c, &light->v_c);
	}
	else
		obj->error = 1;
	obj->error = errors_ambient_light(light, obj);
	free_matrix(split);
	return (obj);
}

/* only check for range errors, the other errors were handled with the matrix
split length */

int	errors_ambient_light(t_amb_light *light, t_object *obj)
{
	int	error;

	error = 0;
	if (obj->error == 1)
	{
		ft_printf("%s%s%s", ERROR_AMBIENT_L, ERROR_PARTIAL, \
			ERR_MISSING_PARAMS);
		return (1);
	}
	if (errors_colors(&light->c) || light->ratio > 1.0 || light->ratio < 0.0)
	{
		ft_printf("%s%s%s", ERROR_AMBIENT_L, ERROR_PARTIAL, \
			ERR_RANGE);
		error = 2;
	}
	return (error);
}
