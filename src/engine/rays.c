#include "engine.h"
#include "vec3.h"
#include "objects.h"
#include <stdio.h>

t_ray	raycast(t_v3 origin, t_camera *cam, double u, double v)
{
	t_ray	ray;

	ray.origin = origin;
	ray.direction = vec3_sum(cam->lower_left_corner, vec3_sum(\
		vec3_multk(cam->horizontal, u), vec3_multk(cam->vertical, v)));
	ray.direction = vec3_sub(ray.direction, ray.origin);
	ray.color = raycolor(ray);
	return (ray);
}

t_color	raycolor(t_ray ray)
{
	t_v3	unit_direction;
	t_v3	c;
	t_color	color;
	double	t;

	unit_direction = vec3_unit(ray.direction);
	t = 0.5 * (unit_direction.y + 1.0);
	c = vec3_sum(vec3_multk((t_v3){1.0, 1.0, 1.0}, 1.0 - t), \
		vec3_multk((t_v3){0.5, 0.7, 1.0}, t));
	color = (t_color){c.x * 255.999, c.y * 255.999, c.z * 255.999};
	return (color);
}
