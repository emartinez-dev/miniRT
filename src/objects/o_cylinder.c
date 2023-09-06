#include "parser.h"
#include "objects.h"
#include "engine.h"
#include "vec3.h"
#include <math.h>

/*
void	hit_cylinder(t_cylinde *cyl, t_ray ray, t_object *obj)
{
	t_v3	oc;
	double	a;
	double	b;
	double	c;
	double	discriminant;
}*/


t_v3	pick_cylinder_normal(t_cylinder *cyl, t_hit *hit)
{
	t_v3	surface_n;
	t_v3	body;
	double	half_h;
	double	projection;

	half_h = cyl->height / 2;
	projection = vec3_dot(vec3_sub(hit->point, cyl->p), cyl->norm);
	surface_n = vec3_sum(cyl->p, vec3_multv(cyl->norm, hit->point));
	body = vec3_normalize(vec3_sub(hit->point, surface_n));
	return (body);
}

double	pick_cylinder_t(t_ray *ray, t_cylinder *cyl, t_quadratic *q)
{
	t_v3	hit1;
	t_v3	hit2;
	double	half_h;

	half_h = cyl->height / 2;
	hit1 = ray_at(ray, q->t1);
	hit2 = ray_at(ray, q->t2);
	q->y0 = vec3_dot(vec3_sub(hit1, cyl->p), cyl->norm);
	q->y1 = vec3_dot(vec3_sub(hit2, cyl->p), cyl->norm);
	if (q->y0 >= -half_h && q->y0 <= half_h && q->y1 >= -half_h && q->y1 <= half_h)
	{
		if (q->t1 < q->t2)
			return (q->t1);
		return (q->t2);
	}
	if (q->y0 >= -half_h && q->y0 <= half_h)
		return (q->t1);
	if (q->y1 >= -half_h && q->y1 <= half_h)
		return (q->t2);
    return (-1.0);
}

double	intersect_caps(t_ray *ray, t_v3 *point, t_v3 *norm)
{
	t_hit	temp;
	double	norm_dist;
	double	norm_ray;

	norm_ray = vec3_dot(ray->direction, *norm);
	if (norm_ray >= 0)
		return (0);
	norm_dist = vec3_dot(vec3_sub(*point, ray->origin), *norm);
	temp.t = norm_dist / norm_ray;
	return (temp.t);
}

/* It's not necessary to rotate the cylinders in world coordinates, we just need to perform
 * the calculations as if it was rotated. I have trying applying matrix multiplication to
 * rotate the objects but its too costly */
double	intersect_cylinder(t_ray *ray, t_cylinder *cyl)
{
	t_quadratic	q;
	double		t;
	t_v3		o_cross;
	double		radius;

	q.oc = vec3_sub(ray->origin, cyl->p);
	q.a = vec3_dot(vec3_cross(cyl->norm, ray->direction), vec3_cross(cyl->norm, ray->direction));
	o_cross = vec3_cross(cyl->norm, q.oc);
	radius = cyl->diameter / 2;
	q.b = 2 * (vec3_dot(o_cross, vec3_cross(cyl->norm, ray->direction)));
	q.c = vec3_dot(o_cross, o_cross) - (radius * radius);
	if (!solve_quadratic(&q))
		return (-1.0);
	t = pick_cylinder_t(ray, cyl, &q);
	return (t);
}

t_hit	hit_cylinder(t_cylinder *cyl, t_ray ray, t_hit hit)
{
	t_hit temp;

	temp.view = ray.direction;
	temp.t = intersect_cylinder(&ray, cyl);
	if ((hit.t > temp.t || hit.t == -1.0) && temp.t > EPSILON)
	{
		temp.color = cyl->c;
		temp.point = ray_at(&ray, temp.t);
		temp.normal = pick_cylinder_normal(cyl, &temp);
		hit = temp;
	}
	return (hit);
}

/*
static int	inside_cylinder(t_cylinder *cyl, t_ray ray, t_hit *hit, double t)
{
	t_v3	point;
	t_v3	intersection;
	double	projection;

//	point = vec3_sum(ray.origin, vec3_multk(ray.direction, t));
	point.x = ray.origin.x + ray.direction.x * t;
	point.y = ray.origin.y + ray.direction.y * t;
	point.z = 0;
	intersection = vec3_sub(point, cyl->p);
	intersection.x = point.x - cyl->p.x;
	intersection.y = point.y - cyl->p.y;
	intersection.z = 0;
	projection = vec3_dot(intersection, cyl->norm);
	if (projection >= 0)// && projection <= cyl->height)
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
*/
