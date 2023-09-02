#include "objects.h"
#include "vec3.h"
#include "parser.h"
#include "engine.h"
#include <math.h>

//static void	apply_diffuse(t_phong *ph, t_object *lights, t_scene *scene);
//static void	apply_ambient(t_phong *ph, t_object *lights);
//static void	apply_specular(t_phong *ph);
static t_color	apply_specular(t_hit *hit, t_ray shadow, t_color light);
//static void	apply_light(t_phong *ph, double factor);
static t_color	apply_light(t_color suface, t_color light, double factor);

t_color	phong_light(t_scene *scene, t_hit *hit)
{
	t_light	*lights;
	t_color	color;
	t_ray	shadow_ray;
	double	dot;

	color = (t_color){0, 0, 0};
	color = color_sum(apply_light(hit->color, scene->ambient_light->c, scene->ambient_light->ratio * AMBIENT), color);
	lights = scene->light;
	while (lights)
	{
		if (is_in_shadow(scene, hit, &shadow_ray, lights)
			|| is_at_back(hit, &dot, shadow_ray))
			;
		else
		{
			color = color_sum(apply_light(hit->color, lights->c, dot * lights->brightness * DIFFUSE), color);
			color = color_sum(apply_specular(hit, shadow_ray, lights->c), color);
		}
		lights = lights->next;
	}
	return (clamp_colors(color));
}
/*
static void	apply_diffuse(t_phong *ph, t_object *lights, t_scene *scene)
{
	ph->color_light = ((t_light *)lights->ptr)->c;
	ph->intensity = ((t_light *)lights->ptr)->brightness;
	ph->p = ((t_light *)lights->ptr)->p;
	if (!is_in_shadow(scene, ph)
		&& !is_at_back(ph))
	{
		apply_light(ph, ph->dot * DIFFUSE);
		apply_specular(ph);
	}
}

static void	apply_ambient(t_phong *ph, t_object *lights)
{
	ph->color_light = ((t_amb_light *)lights->ptr)->c;
	ph->intensity = ((t_amb_light *)lights->ptr)->ratio;
	apply_light(ph, AMBIENT);
}
*/
// Don't affect color 0 //
/*
void	apply_light(t_phong *ph, double factor)
{
	ph->color.r += (ph->hit->color.r * ph->color_light.r / 255)
		* ph->intensity * factor;
	ph->color.g += (ph->hit->color.g * ph->color_light.g / 255)
		* ph->intensity * factor;
	ph->color.b += (ph->hit->color.b * ph->color_light.b / 255)
		* ph->intensity * factor;
	ph->color = clamp_colors(ph->color);
}*/

// Afect all chanels BEST APPROACH//
/*static void	apply_light(t_phong *ph, double factor)
{
	ph->color.r += (ph->hit->color.r + ph->color_light.r / 2)
		* ph->intensity * factor;
	ph->color.g += (ph->hit->color.g + ph->color_light.g / 2)
		* ph->intensity * factor;
	ph->color.b += (ph->hit->color.b + ph->color_light.b / 2)
		* ph->intensity * factor;
	ph->color = clamp_colors(ph->color);
}
*/
static t_color	apply_light(t_color surface, t_color light, double factor)
{
	t_color	color;

	color.r = (surface.r + light.r) / 2 * factor;
	color.g = (surface.g + light.g) / 2 * factor;
	color.b = (surface.b + light.b) / 2 * factor;
	color = clamp_colors(color);
	return (color);
}

/*
static void	apply_specular(t_phong *ph)
{
	t_v3	reflection;
	t_v3	incident;
	double	dot;
	double	factor;

	incident = vec3_negative(ph->shadow.direction);
	reflection = vec3_reflection(incident, ph->hit->normal);
	dot = vec3_dot(reflection, ph->hit->view);
	if (dot <= EPSILON)
		return ;
	else
	factor = pow(dot, SHININESS);
	apply_light(ph, factor * SPECULAR);
}
*/
static t_color	apply_specular(t_hit *hit, t_ray shadow, t_color light)
{
	t_color	color;
	t_v3	reflection;
	t_v3	incident;
	double	dot;
	double	factor;

	color = (t_color){0, 0, 0,};
	incident = vec3_negative(shadow.direction);
	reflection = vec3_reflection(incident, hit->normal);
	dot = vec3_dot(reflection, hit->view);
	if (dot <= EPSILON)
		return (color);
	factor = pow(dot, SHININESS);
	color = apply_light(hit->color, light, factor * SPECULAR);
	return (color);
}
