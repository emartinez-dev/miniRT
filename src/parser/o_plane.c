#include "parser.h"
#include "objects.h"
#include "engine.h"
#include "vec3.h"
#include <float.h>

t_object	*parse_obj_plane(char *line)
{
	t_object	*obj;
	t_plane		*plane;
	char		**split;

	obj = ft_calloc(1, sizeof(t_object));
	obj->type = OBJ_PLANE;
	obj->error = 0;
	split = ft_split(line, ' ');
	plane = ft_calloc(1, sizeof(t_plane));
	obj->ptr = plane;
	if (matrix_len(split) == 4)
	{
		get_xyz(split[1], &plane->p, obj);
		get_xyz(split[2], &plane->norm, obj);
		get_color(split[3], &plane->c);
	}
	else
		obj->error = 1;
	obj->error = errors_plane(plane, obj);
	free_matrix(split);
	return (obj);
}

int	errors_plane(t_plane *plane, t_object *obj)
{
	int	error;

	error = 0;
	if (obj->error == 1)
	{
		ft_printf("%s%s%s", ERROR_PLANE, ERROR_PARTIAL, \
			ERR_MISSING_PARAMS);
		return (1);
	}
	if (errors_colors(&plane->c) || errors_normalized_vector(&plane->norm))
	{
		ft_printf("%s%s%s", ERROR_PLANE, ERROR_PARTIAL, \
			ERR_RANGE);
		error = 2;
	}
	return (error);
}

void hit_plane(t_plane *pl, t_ray ray, t_hit *hit, t_object *obj)
{
	t_v3	oc;
	double	d_point;
	double	norm_dist;
	double	norm_ray;

	if (vec3_distance(ray.origin, pl->p) >= hit->dist)
		return ;
	norm_ray = vec3_dot(ray.direction, pl->norm);
	if (norm_ray >= 0)
		return ;
	oc = vec3_sub(pl->p, ray.origin);
	norm_dist = vec3_dot(oc, pl->norm);
	d_point = norm_dist / norm_ray;
//	if (d_point < 0)
//		return;
	hit->t = d_point;
	hit->dist = vec3_distance(ray.origin, pl->p);
	hit->point = vec3_sum(ray.origin, vec3_multk(ray.direction, hit->t));
//	hit->normal = vec3_sub(hit->point, pl->p);
	hit->normal = pl->norm;
	hit->color = pl->c;
	hit->object = obj;
}

t_color color_plane(t_plane *pl, t_scene *scene, t_hit *hit)
{
	double	lum;
	double	dot_sh;
	t_ray	shadow;
	t_color	color;
	t_hit	sh_hit;
	t_color	light;

	shadow.direction = vec3_unit(vec3_sub(scene->light->p, hit->point));
	shadow.origin = hit->point;
	sh_hit.dist = DBL_MAX;
	sh_hit.object = NULL;
	color = pl->c;
	//aply light ambiental.
	lum = scene->ambient_light->ratio;
	light = scene->ambient_light->c;
	color = (t_color){(color.r * (1 - lum) + light.r * lum) * lum, (color.g * (1 - lum) + light.g * lum) * lum, (color.b *(1 - lum) + light.b * lum) * lum};

	//aply other light
	if (!hit_objects(shadow, &sh_hit, scene) && (sh_hit.object != hit->object))
	{
		lum = scene->light->brightness;
		dot_sh = vec3_dot(shadow.direction, hit->normal);
		if (dot_sh < 0)
		{
//			printf("dot_sh es : %f\n", dot_sh);
			dot_sh = 0;
		}
		else
			printf("dot_sh es : %f\n", dot_sh);

		lum = dot_sh * scene->light->brightness;
		if (lum < 0)
			lum = 0;
		light = scene->light->c;
/*	}
	else
		lum = scene->light->brightness / 2;
		color = (t_color){(color.r * lum + light.r * (1 - lum)) * lum, (color.g * (lum) + light.g * (1 - lum)) * lum, (color.b *(lum) + light.b * (1 - lum)) * lum};
*/		color = (t_color){(color.r * (1 - lum) + light.r * lum), (color.g * (1 - lum) + light.g * lum), (color.b *(1 - lum) + light.b * lum)};

	}
	else
//		printf("shadows plane\n");
	{
		lum = scene->light->brightness;

		color = (t_color){(color.r * (1 - lum) + light.r * lum) * lum / 2, (color.g * (1 - lum) + light.g * lum) * lum / 2, (color.b *(1 - lum) + light.b * lum) * lum / 2};
	}
//	color = (t_color){(pl->c.r * (1 - lum) + light.r * lum) * lum, (pl->c.g * (1 - lum) + light.g * lum) * lum, (pl->c.b *(1 -  lum) + light.b * lum) * lum};

	color = clamp_colors(color);
	return (color);
}
