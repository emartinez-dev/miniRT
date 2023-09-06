#include "parser.h"
#include "objects.h"
#include "engine.h"
#include "vec3.h"

/*
void	hit_cylinder(t_cylinde *cyl, t_ray ray, t_object *obj)
{
	t_v3	oc;
	double	a;
	double	b;
	double	c;
	double	discriminant;
}*/

/* I need one more function because in cylinders you have to check from which side
 * they are intersected, I will update hit from here if needed
 * */
void	intersect_cylinder(t_cylinder *cyl, t_ray ray,t_hit *hit, t_object *obj, double a, double b, double discriminant)
{
	double	t;
	double	r;
	t_v3	oc;

	oc = vec3_sub(ray.origin, cyl->p);
	t = (-b - sqrt(discriminant) / (2 * a));
	if (t > (-b + sqrt(discriminant) / (2 * a)))
		t = -b + sqrt(discriminant) / (2 * a);
	r = cyl->p.y + t * ray.direction.y;	
	if (r >= oc.y && r <= oc.y + cyl->height)
	{
		hit->t = t;
		hit->point = vec3_sum(ray.origin, vec3_multk(ray.direction, hit->t));
		hit->normal = vec3_normalize(vec3_sub(hit->point, vec3_multk(cyl->norm, vec3_dot(hit->point, cyl->norm))));
		//printf("Cylinder hit normal: x:%f y:%f z:%f\n", hit->normal.x, hit->normal.y, hit->normal.z);
		hit->object = obj;
		hit->color = cyl->c;
	}
}

void	hit_cylinder(t_cylinder *cyl, t_ray ray,t_hit *hit, t_object *obj)
{
	t_v3	oc;
	double	a;
	double	b;
	double	c;
	double	discriminant;

	oc = vec3_sub(ray.origin, cyl->p);
	if (vec3_dot(ray.direction, oc) > 0)
		return ;
	a = (ray.direction.x * ray.direction.x) + (ray.direction.z * ray.direction.z);
	b = 2 * (ray.direction.x * oc.x + ray.direction.z * oc.z);
	c = oc.x * oc.x + oc.z * oc.z - cyl->diameter / 2 * cyl->diameter / 2;
	discriminant = b * b - 4 * (a * c);
	if (fabs(discriminant) < 0.001 || discriminant < 0.0)
		return ;
	else
		intersect_cylinder(cyl, ray, hit, obj, a, b, discriminant);
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
