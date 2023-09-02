#include "objects.h"
#include "vec3.h"
#include "parser.h"
#include "engine.h"
#include <math.h>

t_color	apply_light(t_color color_obj, t_color color_light, double intensity);
int		is_at_back(t_hit *hit, double *dot, t_ray shadow);
t_color	get_color_light(t_color color_l, double intensity);
int		is_in_shadow(t_scene *scene, t_hit *hit, t_ray *shadow, t_light *light);

t_color	phong_light(t_scene *scene, t_hit *hit)
{
	t_ray	shadow_ray;
	t_color	color;
	double	dot;
	t_light	*lights;

	color = apply_light(hit->color, scene->ambient_light->c,
			scene->ambient_light->ratio);
	lights = scene->light;
	while (lights)
	{
		if (is_in_shadow(scene, hit, &shadow_ray, lights)
			|| is_at_back(hit, &dot, shadow_ray))
			;
		else
		{
			color = color_sum(color, apply_light(hit->color, lights->c,
						(lights->brightness * dot)));
		}
		lights = lights->next;
	}
	return (color);
}

int	is_in_shadow(t_scene *scene, t_hit *hit, t_ray *shadow, t_light *light)
{
	t_hit	sh_hit;

	shadow->direction = vec3_normalize(vec3_sub(light->p, hit->point));
	shadow->origin = hit->point;
	sh_hit = hit_objects(shadow, scene->objects);
	if (sh_hit.t > EPSILON && sh_hit.object && sh_hit.object != hit->object
		&& sh_hit.t < vec3_distance(light->p, hit->point))
		return (1);
	return (0);
}

int	is_at_back(t_hit *hit, double *dot, t_ray shadow)
{
	*dot = vec3_dot(hit->normal, shadow.direction);
	if (*dot <= 0)
		return (1);
	return (0);
}

t_color	apply_light(t_color color_obj, t_color color_light, double intensity)
{
	t_color	color;

	color.r = (color_obj.r + color_light.r) * intensity;
	color.g = (color_obj.g + color_light.g) * intensity;
	color.b = (color_obj.b + color_light.b) * intensity;
	color = clamp_colors(color);
	return (color);
}

t_color	get_color_light(t_color color_l, double intensity)
{
	t_color	color;

	color.r = color_l.r * intensity;
	color.g = color_l.g * intensity;
	color.b = color_l.b * intensity;
	return (color);
}
