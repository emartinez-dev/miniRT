#include "engine.h"
#include "vec3.h"
#include "objects.h"
#include "parser.h"
#include <stdio.h>
#include <float.h>

t_ray	raycast(double u, double v, t_scene *scene)
{
	t_ray		cam_ray;
	t_hit		world_hit;

	cam_ray = camera_ray(scene->camera, u, v);
	world_hit = hit_objects(&cam_ray, scene);
	cam_ray.color = raycolor(cam_ray, &world_hit, scene);
	return (cam_ray);
}

t_hit hit_objects(t_ray *ray, t_scene *scene)
{
	t_list		*objects;
	t_object	*o;
	t_hit		world;

	objects = scene->objects;
	world.t = -1.0;
	while (objects)
	{
		o = (t_object *)objects->content;
		if (o->type == OBJ_SPHERE)
			world = hit_sphere((t_sphere *)o->ptr, *ray, world);
		if (o->type == OBJ_PLANE)
			world = hit_plane((t_plane *)o->ptr, *ray, world);
		objects = objects->next;
	}
	return (world);
}

/* this function returns the color of the object it hit or the "sky" color */
t_color	raycolor(t_ray ray, t_hit *hit, t_scene *scene)
{
	t_v3		unit_direction;
	t_v3		c;
	t_color		color;
	double		t;

	if (hit->t > EPSILON)
		return (phong_light(scene, hit));
	unit_direction = vec3_unit(ray.direction);
	t = 0.5 * (unit_direction.y + 1.0);
	c = vec3_sum(vec3_multk((t_v3){1.0, 1.0, 1.0}, 1.0 - t), \
		vec3_multk((t_v3){0.5, 0.7, 1.0}, t));
	c = vec3_multk(c, scene->ambient_light->ratio);
	color = (t_color){c.x * 255.999, c.y * 255.999, c.z * 255.999};
	return (color);
}

t_v3	ray_at(t_ray *ray, double t)
{
	t_v3	r;

	r = vec3_sum(ray->origin, vec3_multk(ray->direction, t));
	return (r);
}

