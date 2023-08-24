#include "parser.h"
#include "engine.h"
#include "objects.h"
#include "vec3.h"
#include <float.h>
#include <math.h>

// intersection formula: https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-sphere-intersection.html
double intersect_sphere(t_ray *ray, t_sphere *sp)
{
	t_quadratic	q;

	q.oc = vec3_sub(ray->origin, sp->p);
	q.a = vec3_sqlen(ray->direction);
	q.b = 2.0 * vec3_dot(q.oc, ray->direction);
	q.half_b = q.b / 2;
	q.c = vec3_sqlen(q.oc) - sp->diameter * sp->diameter;
	q.discriminant = q.b * q.b - 4 * q.a * q.c;
	if (q.discriminant < 0)
		return (-1.0);
	q.t1 = -q.b + sqrt(q.discriminant) / (2 * q.a);
	q.t2 = -q.b - sqrt(q.discriminant) / (2 * q.a);
	// if both sqrts are negative, the point is behind the camera
	if (q.t1 < 0 && q.t2 < 0)
		return (-1);
	// if t2 is closer than t1 and t2 is positive, return t2
	if (q.t1 > q.t2 && q.t2 > 0)
		return (q.t2);
	return (q.t1);
}

t_hit hit_sphere(t_sphere *sp, t_ray ray, t_hit hit)
{
	t_hit temp;

	temp.t = intersect_sphere(&ray, sp);
	if ((hit.t > temp.t || hit.t == -1.0) && temp.t > EPSILON)
	{
		temp.color = sp->c;
		temp.point = vec3_sum(ray.origin, vec3_multk(ray.direction, temp.t));
		temp.normal = vec3_unit(vec3_sub(temp.point, sp->p));
		hit = temp;
	}
	return (hit);
}

