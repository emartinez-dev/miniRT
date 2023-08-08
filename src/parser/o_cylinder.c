#include "parser.h"
#include "objects.h"
#include "engine.h"
#include "vec3.h"
#include <float.h>

static int	inside_cylinder(t_cylinder *cyl, t_ray ray, t_hit *hit, double t);

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

void	hit_cylinder(t_cylinder *cyl, t_ray ray,t_hit *hit, t_object *obj)
{
	t_v3	oc;
	double	a;
	double	half_b;
	double	c;
	double	discriminant;

	if (vec3_distance(ray.origin, cyl->p) >= hit->dist)
		return ;
	oc = vec3_sub(ray.origin, cyl->p);
	if (vec3_dot(ray.direction, oc) > 0)
		return ;
	a = vec3_sqlen(ray.direction) - vec3_len(vec3_multv(ray.direction, cyl->norm));
	half_b = vec3_dot(oc, ray.direction) - vec3_dot(ray.direction, cyl->norm) * vec3_dot(oc, cyl->norm);
	c = vec3_sqlen(oc) - vec3_len(vec3_multv(oc, cyl->norm)) - cyl->diameter * cyl->diameter;
	discriminant = half_b * half_b - a * c;
	if (discriminant > 0.0)
	{
		if (inside_cylinder(cyl, ray, hit, (-half_b - sqrt(discriminant)) / a))
			hit->object = obj;
	}
}

static int	inside_cylinder(t_cylinder *cyl, t_ray ray, t_hit *hit, double t)
{
	t_v3	point;
	t_v3	intersection;
	double	projection;

	point = vec3_sum(ray.origin, vec3_multk(ray.direction, t));
	intersection = vec3_sub(point, cyl->p);
	projection = vec3_dot(intersection, cyl->norm);
	if (projection >= 0 && projection <= cyl->height)
	{
		hit->t = t;
		hit->dist = vec3_distance(ray.origin, cyl->p);
		hit->point = point;
		hit->normal = vec3_unit(vec3_sub(intersection, vec3_multk(cyl->norm, projection)));
		hit->color = cyl->c;
		return (1);
	}
	return (0);
}
