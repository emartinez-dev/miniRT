/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o_camera.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 13:32:19 by franmart          #+#    #+#             */
/*   Updated: 2023/09/12 13:32:20 by franmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "objects.h"

t_object	*parse_obj_camera(char *line)
{
	t_object	*obj;
	t_camera	*camera;
	char		**split;

	obj = ft_calloc(1, sizeof(t_object));
	obj->type = OBJ_CAMERA;
	obj->error = 0;
	split = ft_split(line, ' ');
	camera = ft_calloc(1, sizeof(t_camera));
	obj->ptr = camera;
	if (matrix_len(split) == 4)
	{
		get_xyz(split[1], &camera->p, obj);
		get_xyz(split[2], &camera->norm, obj);
		camera->h_fov = ft_atoi(split[3]);
	}
	else
		obj->error = 1;
	obj->error = errors_camera(camera, obj);
	free_matrix(split);
	return (obj);
}

int	errors_camera(t_camera *camera, t_object *obj)
{
	int	error;

	error = 0;
	if (obj->error == 1)
	{
		ft_printf("%s%s%s", ERROR_CAMERA, ERROR_PARTIAL, \
			ERR_MISSING_PARAMS);
		return (1);
	}
	if (errors_normalized_vector(&camera->norm) || camera->h_fov < 0 || \
		camera->h_fov > 180)
	{
		ft_printf("%s%s%s", ERROR_CAMERA, ERROR_PARTIAL, \
			ERR_RANGE);
		error = 2;
	}
	return (error);
}

t_list	*remove_camera_from_list(t_list *head)
{
	t_list	*prev;
	t_list	*tmp;

	prev = NULL;
	tmp = head;
	while (tmp)
	{
		if (((t_object *)tmp->content)->type == OBJ_CAMERA)
		{
			if (prev == NULL)
			{
				prev = tmp->next;
				free(tmp->content);
				free(tmp);
				return (prev);
			}
			free(tmp->content);
			free(tmp);
			prev->next = tmp->next;
			return (head);
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (head);
}

t_camera	*get_camera(t_list *obj)
{
	t_object	*object;
	t_list		*tmp;

	tmp = obj;
	while (tmp)
	{
		object = tmp->content;
		if (object->type == OBJ_CAMERA)
			return (object->ptr);
		tmp = tmp->next;
	}
	return (NULL);
}
