#include "parser.h"
#include "objects.h"
#include "engine.h"
#include "vec3.h"
#include <float.h>

t_hit hit_plane(t_plane *pl, t_ray ray, t_hit hit)
{
	t_hit	temp;
	t_v3	oc;
	double	d_point;
	double	norm_dist;
	double	norm_ray;

	norm_ray = vec3_dot(ray.direction, pl->norm);
	if (norm_ray >= 0)
		return (hit);
	oc = vec3_sub(pl->p, ray.origin);
	norm_dist = vec3_dot(oc, pl->norm);
	d_point = norm_dist / norm_ray;
	temp.t = d_point;
	if ((hit.t > temp.t || hit.t == -1.0) && temp.t > EPSILON)
	{
		temp.color = pl->c;
		temp.point = ray_at(&ray, temp.t);
		temp.normal = pl->norm;
		hit = temp;
	}
	return (hit);
}
