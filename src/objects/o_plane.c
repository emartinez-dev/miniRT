#include "parser.h"
#include "objects.h"
#include "engine.h"
#include "vec3.h"
#include <float.h>

void hit_plane(t_plane *pl, t_ray ray, t_hit *hit, t_object *obj)
{
	t_v3	oc;
	double	d_point;
	double	norm_dist;
	double	norm_ray;

	norm_ray = vec3_dot(ray.direction, pl->norm);
	if (norm_ray >= 0)
		return ;
	oc = vec3_sub(pl->p, ray.origin);
	norm_dist = vec3_dot(oc, pl->norm);
	d_point = norm_dist / norm_ray;
//	if (d_point < 0)
//		return;
	hit->t = d_point;
	hit->point = vec3_sum(ray.origin, vec3_multk(ray.direction, hit->t));
//	hit->normal = vec3_sub(hit->point, pl->p);
	hit->normal = pl->norm;
	hit->color = pl->c;
	hit->object = obj;
}

