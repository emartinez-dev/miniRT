#include "parser.h"
#include "objects.h"
#include "engine.h"
#include "vec3.h"
#include <float.h>

static void	init_caps(t_cylinder *cyl);

t_object	*parse_obj_cylinder(char *line)
{
	t_object	*obj;
	t_cylinder	*cylinder;
	char		**split;

	obj = ft_calloc(1, sizeof(t_object));
	obj->type = OBJ_CYLINDER;
	obj->error = 0;
	split = ft_split(line, ' ');
	cylinder = ft_calloc(1, sizeof(t_cylinder));
	obj->ptr = cylinder;
	if (matrix_len(split) == 6)
	{
		get_xyz(split[1], &cylinder->p, obj);
		get_xyz(split[2], &cylinder->norm, obj);
		cylinder->diameter = ft_atof(split[3]);
		cylinder->height = ft_atof(split[4]);
		get_color(split[5], &cylinder->c);
		init_caps(cylinder);
	}
	else
		obj->error = 1;
	obj->error = errors_cylinder(cylinder, obj);
	free_matrix(split);
	return (obj);
}

int	errors_cylinder(t_cylinder *cylinder, t_object *obj)
{
	int	error;

	error = 0;
	if (obj->error == 1)
	{
		ft_printf("%s%s%s", ERROR_CYLINDER, ERROR_PARTIAL, \
			ERR_MISSING_PARAMS);
		return (1);
	}
	if (errors_colors(&cylinder->c) || \
		errors_normalized_vector(&cylinder->norm))
	{
		ft_printf("%s%s%s", ERROR_CYLINDER, ERROR_PARTIAL, \
			ERR_RANGE);
		error = 2;
	}
	return (error);
}

static void	init_caps(t_cylinder *cyl)
{
	cyl->top.norm = cyl->norm;
	cyl->bottom.norm = cyl->norm;
	cyl->top.diameter = cyl->diameter;
	cyl->bottom.diameter = cyl->diameter;
	cyl->top.p = vec3_sum(cyl->p, vec3_multk(cyl->norm, cyl->height / 2));
	cyl->bottom.p = vec3_sum(cyl->p, vec3_multk(cyl->norm, -cyl->height / 2));
}
