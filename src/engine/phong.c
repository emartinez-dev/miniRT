#include "objects.h"
#include "vec3.h"
#include "parser.h"
#include "engine.h"
#include <float.h>


t_color	phong_light(t_color color_obj, t_scene *scene, t_hit *hit);
t_color	apply_light(t_color color_obj, t_color color_light, double intensity);
int	is_in_shadow(t_scene *scene, t_hit *hit, t_ray *shadow);
int	is_at_back(t_hit *hit, double *dot, t_ray shadow);
t_color	color_sum(t_color color1, t_color color2);

t_color	phong_light(t_color color_obj, t_scene *scene, t_hit *hit)
{
	t_color	color;
	t_color	color_light;
	t_ray	shadow;
	double	dot;
	t_hit	sh_hit;
	
	shadow.direction = vec3_unit(vec3_sub(scene->light->p, hit->point));
	shadow.origin = hit->point;
	sh_hit.dist = DBL_MAX;
	sh_hit.object = NULL;
	color = apply_light(color_obj, scene->ambient_light->c, scene->ambient_light->ratio);
	if (hit_objects(shadow, &sh_hit, scene) && sh_hit.object != hit->object)
		return (color);
	dot = vec3_dot(shadow.direction, hit->normal);
	if (dot < 0)
		return (color);
	color_light = apply_light(color_obj, scene->light->c, scene->light->brightness * dot);
	color = color_sum(color, color_light);
	return (color);

/*	color = apply_light(color_obj, scene->ambient_light->c, scene->ambient_light->ratio);
	if (is_in_shadow(scene, hit, &shadow) || is_at_back(hit, &dot, shadow))
		return (color);
	color_light = apply_light(color_obj, scene->light->c, scene->light->brightness * dot);
	color = color_sum(color, color_light);
	return (color);*/
}

t_color	apply_light(t_color color_obj, t_color color_light, double intensity)
{
	t_color color;

	color.r = color_obj.r * color_light.r * intensity;
	color.g = color_obj.g * color_light.g * intensity;
	color.b = color_obj.b * color_light.b * intensity;
	color = clamp_colors(color);
	return (color);
}

int	is_in_shadow(t_scene *scene, t_hit *hit, t_ray *shadow)
{
	t_hit	sh_hit;

	shadow->direction = vec3_unit(vec3_sub(scene->light->p, hit->point));
	shadow->origin = hit->point;
	sh_hit.dist = DBL_MAX;
	sh_hit.object = NULL;
	if (hit_objects(*shadow, &sh_hit, scene) && sh_hit.object != hit->object)
		return 1;
	return 0;
}

int	is_at_back(t_hit *hit, double *dot, t_ray shadow)
{
	*dot = vec3_dot(shadow.direction, hit->normal);
	if (*dot < 0)
		return 1;
	return 0;
}

t_color	color_sum(t_color color1, t_color color2)
{
	t_color	color;

	color.r = color1.r + color2.r;
	color.g = color1.g + color2.g;
	color.b = color1.b + color2.b;
	color = clamp_colors(color);
	return (color);
}
