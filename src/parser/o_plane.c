#include "parser.h"
#include "objects.h"
#include "engine.h"
#include "vec3.h"

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
	oc = vec3_sub(ray.origin, pl->p);
	norm_dist = vec3_dot(oc, pl->norm);
	d_point = norm_dist / norm_ray;	
	hit->t = d_point;
	hit->dist = vec3_distance(ray.origin, pl->p);
	hit->point = vec3_sum(ray.origin, vec3_multk(ray.direction, hit->t));
	hit->normal = vec3_sub(hit->point, pl->p);
	hit->object = obj;
}

t_color color_plane(t_plane *pl, t_scene *scene, t_hit *hit)
{
	double	lum;
	double	dot_sh;
	t_ray	shadow;
	t_color	color;

	lum = scene->ambient_light->ratio;
	shadow.direction = vec3_unit(vec3_sub(scene->light->p, hit->point));
	dot_sh = vec3_dot(shadow.direction, hit->normal);
	if (dot_sh < 0)
		dot_sh *= -1;
	lum += dot_sh * scene->light->brightness;
	color = (t_color){pl->c.r * lum, pl->c.g * lum, pl->c.b * lum};
	color = clamp_colors(color);
	return (color);
}
