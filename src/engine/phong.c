#include "objects.h"
#include "vec3.h"
#include "parser.h"
#include "engine.h"
#include <float.h>
#include <math.h>


t_color	apply_light(t_color color_obj, t_color color_light, double intensity);
int	is_in_shadow(t_scene *scene, t_hit *hit, t_ray *shadow);
int	is_at_back(t_hit *hit, double *dot, t_ray shadow);
t_color	color_sum(t_color color1, t_color color2);
t_color color_norm(t_color color1);
t_color	get_color_light(t_color color_l, double intensity);

t_color	phong_light(t_scene *scene, t_hit *hit)
{
//	t_color	color_specular;
	t_color	color_ambient;
	t_color	color_difusse;
	t_ray	shadow;
	t_color	color;
	double	dot;

	color_ambient = apply_light(hit->color, scene->ambient_light->c, scene->ambient_light->ratio);
	if (is_in_shadow(scene, hit, &shadow) || is_at_back(hit, &dot, shadow))
		return (color_ambient);
//	aply distance to light
//	color_difusse = apply_light(hit->color, scene->light->c, ((scene->light->brightness / vec3_len(vec3_sub(scene->light->p, hit->point))) * dot));
	color_difusse = apply_light(hit->color, scene->light->c, (scene->light->brightness  * dot));

//	color_specular =
	color = color_sum(color_ambient, color_difusse);
	return (color);
}

t_color	apply_light(t_color color_obj, t_color color_light, double intensity)
{
	t_color color;

	color.r = (color_obj.r + color_light.r) * intensity;
	color.g = (color_obj.g + color_light.g) * intensity;
	color.b = (color_obj.b + color_light.b) * intensity;
//	color = color_norm(color);
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

int	is_in_shadow(t_scene *scene, t_hit *hit, t_ray *shadow)
{
	t_hit	sh_hit;

	shadow->direction = vec3_unit(vec3_sub(scene->light->p, hit->point));
	shadow->origin = hit->point;
	sh_hit = hit_objects(shadow, scene);
	if (sh_hit.t > 0 && sh_hit.object && sh_hit.object != hit->object)
	{
		//printf("sombra here how: hit %p sh_hit %p\n", hit->object, sh_hit.object);
		return 1;
	}
	return 0;
}

int	is_at_back(t_hit *hit, double *dot, t_ray shadow)
{
	// debug the is_at_back
	//
	*dot = vec3_dot(hit->normal, shadow.direction);
	if (*dot <= 0)
		return 1;
	return 0;
}

t_color	color_sum(t_color color1, t_color color2)
{
	t_color	color;

	color.r = color1.r + color2.r;
	color.g = color1.g + color2.g;
	color.b = color1.b + color2.b;
//	color = color_norm(color);
	color = clamp_colors(color);
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
	if (max >= 0 && max <= 255)
		return (color1);
	color1.r /= max;
	color1.g /= max;
	color1.b /= max;
	color1.r *= 255;
	color1.g *= 255;
	color1.b *= 255;
	return (color1);
}
