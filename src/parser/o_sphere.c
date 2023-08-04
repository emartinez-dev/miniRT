#include "parser.h"
#include "engine.h"
#include "objects.h"
#include "vec3.h"
#include <float.h>

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
	if (vec3_dot(ray.direction, oc) > 0)
		return ;
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
		hit->color = sp->c;
	}
}

t_color	color_sphere(t_sphere *sp, t_scene *scene, t_hit *hit)
{
	double	lum;
	t_color	color;
	t_ray	shadow;
	t_hit	sh_hit;

	lum = scene->ambient_light->ratio;
	shadow.direction = vec3_unit(vec3_sub(scene->light->p, hit->point));
	lum += vec3_dot(shadow.direction, hit->normal) * scene->light->brightness;
	shadow.origin = hit->point;
	sh_hit.dist = DBL_MAX;
	sh_hit.object = NULL;
	if (hit_objects(shadow, &sh_hit, scene) && sh_hit.object != hit->object)
		lum = scene->ambient_light->ratio;
	color = (t_color){sp->c.r * lum, sp->c.g * lum, sp->c.b * lum};
	color = clamp_colors(color);
	return (color);
}
