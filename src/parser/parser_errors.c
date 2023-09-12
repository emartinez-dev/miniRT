#include "parser.h"
#include "vec3.h"

/* If ft_strlen(ft_strnstr(filename, rt)) returns other than 3, then the file is
not a valid ".rt" (3 chars) file */

int	params_error(int argc, char **argv, t_scene *scene)
{
	int	fd;

	if (argc != 2)
	{
		ft_putstr_fd(ERROR_ARGC, STDERR_FILENO);
		return (1);
	}
	if (!ft_strnstr(argv[1], ".rt", ft_strlen(argv[1])) || \
		ft_strlen(ft_strnstr(argv[1], ".rt", ft_strlen(argv[1]))) != 3)
	{
		ft_putstr_fd(ERROR_ARGC, STDERR_FILENO);
		return (1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd(ERROR_FILE, STDERR_FILENO);
		return (1);
	}
	scene->fd = fd;
	return (0);
}

int	errors_normalized_vector(t_v3 *norm)
{
	t_v3	p;

	p = *norm;
	p.x = round(norm->x);
	p.y = round(norm->y);
	p.z = round(norm->z);
	if (p.x > 1.0 || p.y > 1.0 || p.z > 1.0 || p.x < -1.0 || \
		p.y < -1.0 || p.z < -1.0)
		return (1);
	if (vec3_len(*norm) <= 0.99 || vec3_len(*norm) >= 1.01)
	{
		ft_printf("[DEBUG] normalized vector length should be 1.0. Value: %f\n", \
			vec3_len(*norm));
		return (1);
	}
	return (0);
}

int	errors_colors(t_color *color)
{
	if (color->r > 255 || color->g > 255 || color->b > 255 || \
			color->r < 0 || color->g < 0 || color->b < 0)
		return (1);
	return (0);
}

int	errors_in_objects(t_scene *scene)
{
	t_object	*obj;
	t_list		*tmp;

	tmp = scene->objects;
	while (tmp && tmp->content)
	{
		obj = tmp->content;
		if (obj->error)
			return (1);
		tmp = tmp->next;
	}
	tmp = scene->lights;
	while (tmp && tmp->content)
	{
		obj = tmp->content;
		if (obj->error)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	invalid_line(t_scene *scene)
{
	void	*obj;
	void	*light;
	int		i;

	i = -1;
	while (scene->scene_str[++i])
	{
		obj = parse_line(scene->scene_str[i], 0);
		light = parse_line(scene->scene_str[i], 1);
		if (!obj && !light && !ft_strnstr(scene->scene_str[i], "#", 1))
			return (1);
		free_objects(obj);
		free_objects(light);
	}
	return (0);
}
