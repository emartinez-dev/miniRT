#include "parser.h"
#include "objects.h"

t_object	*parse_obj_light(char *line)
{
	t_object	*obj;
	t_light		*light;
	char		**split;

	obj = ft_calloc(1, sizeof(t_object));
	obj->type = OBJ_LIGHT;
	obj->error = 0;
	split = ft_split(line, ' ');
	light = ft_calloc(1, sizeof(t_light));
	obj->ptr = light;
	if (matrix_len(split) == 4)
	{
		get_xyz(split[1], &light->p, obj);
		light->brightness = ft_atod(split[2]);
		get_color(split[3], &light->c);
	}
	else
		obj->error = 1;
	obj->error = errors_light(light, obj);
	free_matrix(split);
	return (obj);
}

int	errors_light(t_light *light, t_object *obj)
{
	int	error;

	error = 0;
	if (obj->error == 1)
	{
		ft_putstr_fd(ERR_MISSING_PARAMS, STDERR_FILENO);
		return (1);
	}
	if (errors_colors(&light->c) || light->brightness > 1.0 || \
		light->brightness < 0.0)
	{
		ft_putstr_fd(ERR_RANGE, STDERR_FILENO);
		error = 2;
	}
	return (error);
}
