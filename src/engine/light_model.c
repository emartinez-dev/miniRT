#include "objects.h"
#include "vec3.h"
#include "parser.h"
#include "engine.h"
#include <math.h>

static int		is_at_back(t_hit *hit, double *dot, t_ray *shadow,
					t_light *light);
static int		is_in_shadow(t_scene *scene, t_hit *hit, t_ray *shadow,
					t_light *light);
static int		specular(t_hit *hit, double *dot, t_ray *shadow,
					t_light *lights);

t_color	phong_light(t_scene *scene, t_hit *hit, t_color ambient)
{
	t_ray	shadow_ray;
	t_color	color;
	double	dot;
	t_light	*lights;
	double	dot_sp;

	color = ambient;
	lights = scene->light;
	while (lights)
	{
		is_at_back(hit, &dot, &shadow_ray, lights);
		if (is_in_shadow(scene, hit, &shadow_ray, lights))
			;
		else if (dot > 0)
		{
			color = color_sum(color, apply_light(hit->color, lights->v_c,
						(dot * DIFFUSE)));
			if (BONUS && specular(hit, &dot_sp, &shadow_ray, lights))
				color = color_sum(color, vec_to_color(vec3_multk(lights->v_c,
								dot_sp * 255)));
		}
		lights = lights->next;
	}
	return (color);
}

static int	specular(t_hit *hit, double *dot, t_ray *shadow, t_light *light)
{
	t_v3	reflection;
	t_v3	incident;

	(void) light;
	incident = vec3_negative(shadow->direction);
	reflection = vec3_reflection(incident, hit->normal);
	*dot = vec3_dot(reflection, hit->view);
	if (*dot > 0)
		return (0);
	*dot = (pow(*dot, SHININESS) * SPECULAR);
	return (1);
}

static int	is_in_shadow(t_scene *scene, t_hit *hit, t_ray *shadow,
				t_light *light)
{
	t_hit	sh_hit;

	shadow->direction = vec3_normalize(vec3_sub(light->p, hit->point));
	shadow->origin = hit->point;
	sh_hit = hit_objects(shadow, scene->objects);
	if (sh_hit.t > EPSILON && sh_hit.t < vec3_distance(light->p, hit->point))
		return (1);
	return (0);
}

static int	is_at_back(t_hit *hit, double *dot, t_ray *shadow, t_light *light)
{
	shadow->direction = vec3_normalize(vec3_sub(light->p, hit->point));
	*dot = vec3_dot(hit->normal, shadow->direction);
	if (*dot <= EPSILON)
		return (0);
	return (1);
}

t_color	apply_light(t_color color_obj, t_v3 color_light,
					double intensity)
{
	t_color	color;

	color.r = color_obj.r * color_light.x * intensity;
	color.g = color_obj.g * color_light.y * intensity;
	color.b = color_obj.b * color_light.z * intensity;
	color = clamp_colors(color);
	return (color);
}
