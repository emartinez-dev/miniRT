#include "parser.h"
#include "engine.h"
#include "objects.h"
#include "vec3.h"

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
		sphere->diameter = ft_atod(split[2]);
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

int	hit_sphere(t_sphere *sp, t_ray ray)
{
	t_v3	oc;
	double	a;
	double	b;
	double	c;
	double	discriminant;

	oc = vec3_sub(ray.origin, sp->p);
	a = vec3_dot(ray.direction, ray.direction);
	b = 2.0 * vec3_dot(oc, ray.direction);
	c = vec3_dot(oc, oc) - sp->diameter * sp->diameter;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (0);
	return (1);
}
