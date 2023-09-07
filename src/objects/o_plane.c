#include "parser.h"
#include "objects.h"
#include "engine.h"
#include "vec3.h"

t_hit	hit_plane(t_plane *pl, t_ray ray, t_hit hit)
{
	t_hit	temp;

	temp.t = intersect_plane(ray, pl->norm, pl->p);
	temp.view = ray.direction;
	if ((hit.t > temp.t || hit.t == -1.0) && temp.t > EPSILON)
	{
		temp.color = pl->c;
		temp.point = ray_at(&ray, temp.t);
		temp.normal = pl->norm;
		hit = temp;
	}
	return (hit);
}

double	intersect_plane(t_ray ray, t_v3 norm, t_v3 p)
{
	double	norm_dist;
	double	norm_ray;
	t_v3	oc;

	norm_ray = vec3_dot(ray.direction, norm);
	if (norm_ray == 0)
		return (-1.0);
	oc = vec3_sub(p, ray.origin);
	norm_dist = vec3_dot(oc, norm);
	return ((double)(norm_dist / norm_ray));
}
