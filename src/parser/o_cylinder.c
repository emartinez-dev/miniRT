#include "parser.h"
#include "objects.h"

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

void	hit_cylinder(t_cylinde *cyl, t_ray ray, t_object *obj)
{
	t_v3	oc;
	double	a;
	double	b;
	double	c;
	double	discriminant;

	if (vec3_distance(ray.origin, cyl->p) >= hiy->dist)
		return;
	oc = vec3_sub(ray.origin, cyl->p);
	a = 
}
