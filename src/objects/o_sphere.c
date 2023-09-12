#include "engine.h"

double	intersect_sphere(t_ray *ray, t_sphere *sp);

t_hit	hit_sphere(t_sphere *sp, t_ray ray, t_hit hit)
{
	t_hit		temp;

	temp.view = ray.direction;
	temp.t = intersect_sphere(&ray, sp);
	if ((hit.t > temp.t || hit.t == -1.0) && temp.t > EPSILON)
	{
		temp.color = sp->c;
		temp.point = ray_at(&ray, temp.t);
		temp.normal = vec3_normalize(vec3_sub(temp.point, sp->p));
		hit = temp;
	}
	return (hit);
}

/* intersection formula: 
 https://www.scratchapixel.com/lessons/3d-basic-rendering/
 minimal-ray-tracer-rendering-simple-shapes/ray-sphere-intersection.html */

double	intersect_sphere(t_ray *ray, t_sphere *sp)
{
	t_quadratic	q;

	q.oc = vec3_sub(ray->origin, sp->p);
	q.a = vec3_dot(ray->direction, ray->direction);
	q.b = 2 * vec3_dot(ray->direction, q.oc);
	q.c = vec3_dot(q.oc, q.oc) - sp->radius * sp->radius;
	if (!solve_quadratic(&q))
		return (-1.0);
	if (q.t1 < 0 && q.t2 < 0)
		return (-1);
	if (q.t1 > q.t2 && q.t2 > 0)
		return (q.t2);
	return (q.t1);
}
