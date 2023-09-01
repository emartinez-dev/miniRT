#include "objects.h"
#include "vec3.h"
#include "parser.h"
#include "engine.h"
#include <math.h>

static void	apply_diffuse(t_phong *ph, t_object *lights, t_scene *scene);
static void	apply_ambient(t_phong *ph, t_object *lights);
static void	apply_specular(t_phong *ph);
static void	apply_light(t_phong *ph, double factor);

t_color	phong_light(t_scene *scene, t_hit *hit)
{
	t_phong	ph;
	t_list	*lights;

	ph.hit = hit;
	ph.color = (t_color){0, 0, 0};
	lights = scene->lights;
	while (lights)
	{
		if (((t_object *)lights->content)->type == OBJ_LIGHT)
			apply_diffuse(&ph, (t_object *)lights->content, scene);
		else if (((t_object *)lights->content)->type == OBJ_AMBIENT_LIGHT)
			apply_ambient(&ph, (t_object *)lights->content);
		lights = lights->next;
	}
	return (clamp_colors(ph.color));
}

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
static void	apply_light(t_phong *ph, double factor)
{
	ph->color.r += (ph->hit->color.r + ph->color_light.r / 2)
		* ph->intensity * factor;
	ph->color.g += (ph->hit->color.g + ph->color_light.g / 2)
		* ph->intensity * factor;
	ph->color.b += (ph->hit->color.b + ph->color_light.b / 2)
		* ph->intensity * factor;
	ph->color = clamp_colors(ph->color);
}

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
