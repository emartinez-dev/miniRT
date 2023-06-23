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
	t_camera	*cam;

	cam = scene->camera;
	cam_ray = camera_ray(cam, u, v);
	world_hit.dist = DBL_MAX;
	world_hit.object = NULL;
	hit_objects(cam_ray, &world_hit, scene);
	/* after hit_objects, world_hit.object is the closest object hit by the ray
	or NULL if no object was hit */
	cam_ray.color = raycolor(cam_ray, &world_hit, scene);
	return (cam_ray);
}

int	hit_objects(t_ray ray, t_hit *hit, t_scene *scene)
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
	if (hit->object)
		return (1);
	return (0);
}

/* this function returns the color of the object it hit or the "sky" color */
t_color	raycolor(t_ray ray, t_hit *hit, t_scene *scene)
{
	t_v3		unit_direction;
	t_v3		c;
	t_color		color;
	double		t;

	if (hit->object && hit->object->type == OBJ_SPHERE)
		return (color_sphere((t_sphere *)hit->object->ptr, scene, hit));
	// sky color part
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
