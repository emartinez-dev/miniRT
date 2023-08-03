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
t_color color_norm(t_color color1);

t_color	phong_plane(t_plane *obj, t_scene *scene, t_hit *hit)
{
	return (phong_light(obj->c, scene, hit));
}

t_color	phong_sphere(t_sphere *obj, t_scene *scene, t_hit *hit)
{
	return (phong_light(obj->c, scene, hit));
}

t_color	phong_light(t_color color_obj, t_scene *scene, t_hit *hit)
{
	t_color	color;
	t_color	color_light;
	t_ray	shadow;
	double	dot;

	color = apply_light(color_obj, scene->ambient_light->c, scene->ambient_light->ratio);
//	if (is_in_shadow(scene, hit, &shadow) || is_at_back(hit, &dot, shadow))
	if (is_in_shadow(scene, hit, &shadow))
	{
//		color = apply_light(color_obj, scene->ambient_light->c, scene->ambient_light->ratio / 2);
		return (color);
	}
	dot = vec3_dot(shadow.direction, hit->normal);

	color_light = apply_light(color_obj, scene->light->c, (scene->light->brightness * dot / (vec3_len(shadow.direction) * vec3_len(vec3_negative(hit->normal)))));
	color = color_sum(color, color_light);
	return (color);
}

t_color	apply_light(t_color color_obj, t_color color_light, double intensity)
{
	t_color color;

	color.r = (color_obj.r + color_light.r) * intensity;
	color.g = (color_obj.g + color_light.g) * intensity;
	color.b = (color_obj.b + color_light.b) * intensity;
	color = color_norm(color);
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
	{
		printf("in shadows\n");
		return 1;
	}
	return 0;
}

int	is_at_back(t_hit *hit, double *dot, t_ray shadow)
{
	*dot = vec3_dot(shadow.direction, hit->normal);
	if (*dot <= 0)
	{
		printf("at back\n");
		return 1;
	}
	return 0;
}

t_color	color_sum(t_color color1, t_color color2)
{
	t_color	color;

	color.r = color1.r + color2.r;
	color.g = color1.g + color2.g;
	color.b = color1.b + color2.b;
	color = color_norm(color);
	return (color);
}

t_color color_norm(t_color color1)
{
	int	max;

	if (color1.r >= color1.g && color1.r >= color1.b)
		max = color1.r;
	else if (color1.g >= color1.r && color1.g >= color1.b)
		max = color1.g;
	else
		max = color1.b;
	if (max <= 0 || max <= 255)
		return (color1);
	color1.r /= max;
	color1.g /= max;
	color1.b /= max;
	color1.r *= 255;
	color1.g *= 255;
	color1.b *= 255;
	return (color1);
}
