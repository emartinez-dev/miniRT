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
		light->ratio = ft_atod(split[1]);
		get_color(split[2], &light->c);
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

	if (obj->error == 1)
	{
		ft_putstr_fd(ERR_MISSING_PARAMS, STDERR_FILENO);
		return (1);
	}
	error = 0;
	if (light->ratio < 0.0 || light->ratio > 1.0)
		error = 2;
	if (light->c.r > 255 || light->c.g > 255 || light->c.b > 255 || \
			light->c.r < 0 || light->c.g < 0 || light->c.b < 0)
		error = 2;
	if (error == 2)
		ft_putstr_fd(ERR_RANGE, STDERR_FILENO);
	return (error);
}
