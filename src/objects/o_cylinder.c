#include "parser.h"
#include "objects.h"
#include "engine.h"
#include "vec3.h"
#include <math.h>

double	intersect_cylinder_cap(t_ray *ray, t_cylinder *cyl);
double	intersect_cylinder(t_ray *ray, t_cylinder *cyl);
t_v3	cylinder_normal(t_cylinder *cyl, t_hit *hit);

t_hit	hit_cylinder(t_cylinder *cyl, t_ray ray, t_hit hit)
{
	t_hit temp;
	t_hit temp_cap;

	temp.view = ray.direction;
	temp.t = intersect_cylinder(&ray, cyl);
	temp_cap.t = intersect_cylinder_cap(&ray, cyl);
	if ((hit.t > temp_cap.t || hit.t == -1.0) && temp_cap.t > EPSILON)
	{
		temp_cap.color = cyl->c;
		temp_cap.point = ray_at(&ray, temp_cap.t);
		temp_cap.normal = cyl->norm;
		hit = temp_cap;
	}
	if ((hit.t > temp.t || hit.t == -1.0) && temp.t > EPSILON)
	{
		temp.color = cyl->c;
		temp.point = ray_at(&ray, temp.t);
		temp.normal = cylinder_normal(cyl, &temp);
		hit = temp;
	}
	return (hit);
}


t_v3  cylinder_normal(t_cylinder *cyl, t_hit *hit)
{
	t_v3	surface_n;
	t_v3	body;

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
	if (q->y0 >= -half_h && q->y0 <= half_h && q->y1 >= -half_h 
		&& q->y1 <= half_h)
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

double	intersect_cylinder_cap(t_ray *ray, t_cylinder *cyl)
{
	t_hit	temp;
	double	norm_dist;
	double	norm_ray;
	t_v3	oc;
	double	distance_to_center;

	norm_ray = vec3_dot(ray->direction, cyl->norm);
	oc = vec3_sub(cyl->p, ray->origin);
	norm_dist = vec3_dot(oc, cyl->norm);
	temp.t = norm_dist / norm_ray;
	temp.point = ray_at(ray, temp.t);
	distance_to_center = vec3_len(vec3_sub(temp.point, cyl->p));
	if (distance_to_center > cyl->diameter / 2)
		return (-1.0);
	return (temp.t);
}

