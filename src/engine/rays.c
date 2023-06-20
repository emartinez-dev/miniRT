#include "engine.h"
#include "vec3.h"
#include "objects.h"
#include "parser.h"
#include <stdio.h>
#include <float.h>

t_ray	raycast(t_v3 origin, double u, double v, t_scene *scene)
{
	t_ray		ray;
	t_hit		hit;
	t_camera	*cam;

	cam = scene->camera;
	ray.origin = origin;
	ray.direction = vec3_sum(cam->lower_left_corner, vec3_sum(\
		vec3_multk(cam->horizontal, u), vec3_multk(cam->vertical, v)));
	ray.direction = vec3_sub(ray.direction, ray.origin);
	hit.dist = DBL_MAX;
	hit.object = NULL;
	hit_objects(ray, &hit, scene);
	ray.color = raycolor(ray, &hit, scene);
	return (ray);
}

void	hit_objects(t_ray ray, t_hit *hit, t_scene *scene)
{
	t_list		*objects;
	t_object	*o;

	objects = scene->objects;
	while (objects)
	{
		o = (t_object *)objects->content;
		if (o->type == OBJ_SPHERE)
			hit_sphere((t_sphere *)o->ptr, ray, hit, o);
		objects = objects->next;
	}
}

t_color	raycolor(t_ray ray, t_hit *hit, t_scene *scene)
{
	t_v3		unit_direction;
	t_v3		c;
	t_color		color;
	double		t;

	(void) scene;
	if (hit->object && hit->object->type == OBJ_SPHERE)
	{
		if (hit->t > 0.0)
			return (color_sphere((t_sphere *)hit->object->ptr, &ray, hit, hit->t));
	}
	unit_direction = vec3_unit(ray.direction);
	t = 0.5 * (unit_direction.y + 1.0);
	c = vec3_sum(vec3_multk((t_v3){1.0, 1.0, 1.0}, 1.0 - t), \
		vec3_multk((t_v3){0.5, 0.7, 1.0}, t));
	color = (t_color){c.x * 255.999, c.y * 255.999, c.z * 255.999};
	return (color);
}

t_v3	ray_at(t_ray *ray, double t)
{
	t_v3	r;

	r = vec3_sum(ray->origin, vec3_multk(ray->direction, t));
	return (r);
}
