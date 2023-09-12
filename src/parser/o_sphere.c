#include "engine.h"

t_object	*parse_obj_sphere(char *line)
{
	t_object	*obj;
	t_sphere	*sphere;
	char		**split;

	obj = ft_calloc(1, sizeof(t_object));
	obj->type = OBJ_SPHERE;
	obj->error = 0;
	split = ft_split(line, ' ');
	sphere = ft_calloc(1, sizeof(t_sphere));
	obj->ptr = sphere;
	if (matrix_len(split) == 4)
	{
		get_xyz(split[1], &sphere->p, obj);
		sphere->diameter = ft_atof(split[2]);
		sphere->radius = sphere->diameter / 2.0;
		get_color(split[3], &sphere->c);
	}
	else
		obj->error = 1;
	obj->error = errors_sphere(sphere, obj);
	free_matrix(split);
	return (obj);
}

int	errors_sphere(t_sphere *sphere, t_object *obj)
{
	int	error;

	error = 0;
	if (obj->error == 1)
	{
		ft_printf("%s%s%s", ERROR_SPHERE, ERROR_PARTIAL, \
			ERR_MISSING_PARAMS);
		return (1);
	}
	if (errors_colors(&sphere->c))
	{
		ft_printf("%s%s%s", ERROR_SPHERE, ERROR_PARTIAL, \
			ERR_RANGE);
		error = 2;
	}
	return (error);
}
