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

void	hit_sphere(t_sphere *sp, t_ray ray, t_hit *hit, t_object *obj)
{
	t_v3	oc;
	double	a;
	double	half_b;
	double	c;
	double	discriminant;

	if (vec3_distance(ray.origin, sp->p) >= hit->dist)
		return ;
	oc = vec3_sub(ray.origin, sp->p);
	a = vec3_sqlen(ray.direction);
	half_b = vec3_dot(oc, ray.direction);
	c = vec3_sqlen(oc) - sp->diameter * sp->diameter;
	discriminant = half_b * half_b - a * c;
	if (discriminant > 0.0)
	{
		hit->t = (-half_b - sqrt(discriminant)) / a;
		hit->dist = vec3_distance(ray.origin, sp->p);
		hit->point = vec3_sum(ray.origin, vec3_multk(ray.direction, hit->t));
		hit->normal = vec3_divk(vec3_sub(hit->point, sp->p), sp->diameter);
		hit->object = obj;
	}
}

t_color	color_sphere(t_sphere *sp, t_ray *ray, t_hit *hit, double t)
{
	double	camHit;

	(void) t;
	camHit = vec3_dot(ray->direction, vec3_negative(hit->normal));
	if (camHit > 1.0)
		camHit = 1.0;
	return ((t_color){sp->c.r * camHit, sp->c.g * camHit, sp->c.b * camHit});
}
