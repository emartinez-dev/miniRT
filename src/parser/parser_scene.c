/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 13:33:31 by franmart          #+#    #+#             */
/*   Updated: 2023/09/12 14:08:53 by juan-aga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include "parser.h"

void	read_scene(t_scene *scene)
{
	char	*buffer;
	char	*line;
	char	*tmp;

	buffer = ft_calloc(1, sizeof(char));
	if (!buffer)
	{
		ft_printf("Error\nFailed allocated memory.\n");
		exit(1);
	}
	buffer[0] = '\0';
	line = get_next_line(scene->fd);
	while (line)
	{
		tmp = ft_strjoin(buffer, line);
		free(buffer);
		free(line);
		buffer = tmp;
		line = get_next_line(scene->fd);
	}
	scene->scene_str = ft_split(buffer, '\n');
	free(buffer);
}

int	extract_objects(t_scene *scene)
{
	scene->errors = 0;
	scene->lights = NULL;
	scene->objects = NULL;
	scene->ambient_light = NULL;
	scene->lights = parse_all_lights(scene);
	scene->objects = parse_all_objects(scene);
	if (errors_in_objects(scene) || invalid_line(scene))
		scene->errors = 1;
	scene->camera = get_camera(scene->objects);
	scene->objects = remove_camera_from_list(scene->objects);
	get_lights(scene);
	if (scene->camera == NULL)
	{
		ft_printf("%s%s%s", ERROR_CAMERA, ERROR_PARTIAL, "No camera found\n");
		scene->errors = 1;
	}
	if (!scene->light || !scene->ambient_light)
	{
		ft_printf("%s%s%s", ERROR_LIGHT, ERROR_PARTIAL,
			"No light or ambient light found\n");
		scene->errors = 1;
	}
	return (scene->errors);
}

void	*parse_line(char *line, int lights)
{
	void	*ptr;

	ptr = NULL;
	if (ft_strnstr(line, "A ", 2) && lights)
		ptr = (void *)parse_obj_ambient_light(line);
	else if (ft_strnstr(line, "C ", 2) && !lights)
		ptr = (void *)parse_obj_camera(line);
	else if (ft_strnstr(line, "L ", 2) && lights)
		ptr = (void *)parse_obj_light(line);
	else if (ft_strnstr(line, "sp ", 3) && !lights)
		ptr = (void *)parse_obj_sphere(line);
	else if (ft_strnstr(line, "pl ", 3) && !lights)
		ptr = (void *)parse_obj_plane(line);
	else if (ft_strnstr(line, "cy ", 3) && !lights)
		ptr = (void *)parse_obj_cylinder(line);
	return (ptr);
}

t_list	*parse_all_lights(t_scene *scene)
{
	t_list	*new;
	void	*obj_ptr;
	int		i;

	i = -1;
	while (scene->scene_str[++i])
	{
		scene->scene_str[i] = replace_tabs(scene->scene_str[i]);
		obj_ptr = parse_line(scene->scene_str[i], 1);
		new = ft_lstnew(obj_ptr);
		if (obj_ptr && (((t_object *)obj_ptr)->type == OBJ_AMBIENT_LIGHT || \
			((t_object *)obj_ptr)->type == OBJ_LIGHT))
		{
			if (!scene->lights)
				scene->lights = new;
			else
				ft_lstadd_back(&scene->lights, new);
		}
		else
			ft_lstdelone(new, free_objects);
	}
	return (scene->lights);
}

t_list	*parse_all_objects(t_scene *scene)
{
	t_list	*new;
	void	*obj_ptr;
	int		i;

	i = -1;
	while (scene->scene_str[++i])
	{
		scene->scene_str[i] = replace_tabs(scene->scene_str[i]);
		obj_ptr = parse_line(scene->scene_str[i], 0);
		new = ft_lstnew(obj_ptr);
		if (obj_ptr && (((t_object *)obj_ptr)->type != OBJ_AMBIENT_LIGHT && \
			((t_object *)obj_ptr)->type != OBJ_LIGHT))
		{
			if (!scene->objects)
				scene->objects = new;
			else
				ft_lstadd_back(&scene->objects, new);
		}
		else
			ft_lstdelone(new, free_objects);
	}
	return (scene->objects);
}
