/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o_cylinder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-aga <juan_aga@student.42malaga.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 14:48:31 by juan-aga          #+#    #+#             */
/*   Updated: 2023/09/12 14:48:33 by juan-aga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

double	intersect_cylinder_cap(t_ray *ray, t_cylinder *cyl);
double	intersect_cylinder(t_ray *ray, t_cylinder *cyl);
t_v3	cylinder_normal(t_cylinder *cyl, t_hit *hit);
int		radius_check(double t, t_v3 face, t_ray *ray, double diameter);

t_hit	hit_cylinder(t_cylinder *cyl, t_ray ray, t_hit hit)
{
	t_hit	temp;
	t_hit	temp_cap;

	temp.view = ray.direction;
	temp_cap.view = ray.direction;
	temp.t = intersect_cylinder(&ray, cyl);
	temp_cap.t = intersect_cylinder_cap(&ray, cyl);
	if ((hit.t > temp_cap.t || hit.t == -1.0) && temp_cap.t > EPSILON)
	{
		temp_cap.color = cyl->c;
		temp_cap.point = ray_at(&ray, temp_cap.t);
		temp_cap.normal = cyl->cap_norm;
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

t_v3	cylinder_normal(t_cylinder *cyl, t_hit *hit)
{
	t_v3	base_dist;
	double	projection_len;
	t_v3	surface_n;
	t_v3	body;

	base_dist = vec3_sub(hit->point, cyl->p);
	projection_len = vec3_dot(base_dist, cyl->norm);
	surface_n = vec3_sum(cyl->p, vec3_multk(cyl->norm, projection_len));
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

/* It's not necessary to rotate the cylinders in world coordinates, 
 * we just need to perform the calculations as if it was rotated. 
 * I have trying applying matrix multiplication to rotate the objects 
 * but its too costly */
double	intersect_cylinder(t_ray *ray, t_cylinder *cyl)
{
	t_quadratic	q;
	double		t;
	t_v3		o_cross;
	double		radius;

	q.oc = vec3_sub(ray->origin, cyl->p);
	q.a = vec3_dot(vec3_cross(cyl->norm, ray->direction),
			vec3_cross(cyl->norm, ray->direction));
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
	cyl->top.intersected = intersect_circle(ray, &cyl->top);
	cyl->bottom.intersected = intersect_circle(ray, &cyl->bottom);
	cyl->cap_norm = cyl->norm;
	if (cyl->top.intersected && !cyl->bottom.intersected)
		return (cyl->top.t);
	if (!cyl->top.intersected && cyl->bottom.intersected)
	{
		cyl->cap_norm = vec3_negative(cyl->norm);
		return (cyl->bottom.t);
	}
	if (cyl->top.intersected && cyl->bottom.intersected)
	{
		if (cyl->bottom.t < cyl->top.t)
			cyl->cap_norm = vec3_negative(cyl->norm);
		return (fmin(cyl->top.t, cyl->bottom.t));
	}
	return (-1.0);
}
