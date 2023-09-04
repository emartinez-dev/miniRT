#include "objects.h"
#include "vec3.h"
#include "parser.h"
#include "engine.h"
#include <math.h>

static t_color	apply_light(t_color color_obj, t_color color_light,
					double intensity);
static int		is_at_back(t_hit *hit, double *dot, t_ray *shadow);
static int		is_in_shadow(t_scene *scene, t_hit *hit, t_ray *shadow,
					t_light *light);
static int		specular(t_hit *hit, double *dot, t_ray *shadow);

t_color	phong_light(t_scene *scene, t_hit *hit)
{
	t_ray	shadow_ray;
	t_color	color;
	double	dot;
	t_light	*lights;

	color = apply_light(hit->color, scene->ambient_light->c,
			scene->ambient_light->ratio * AMBIENT);
	lights = scene->light;
	while (lights)
	{
		if (!(is_in_shadow(scene, hit, &shadow_ray, lights)
				|| is_at_back(hit, &dot, &shadow_ray)))
		{
			color = color_sum(color, apply_light(hit->color, lights->c,
						(lights->brightness * dot * DIFFUSE)));
			if (specular(hit, &dot, &shadow_ray))
				color = color_sum(color, apply_light(hit->color, lights->c,
							(lights->brightness * dot * SPECULAR)));
		}
		lights = lights->next;
	}
	return (clamp_colors(color));
}

static int	specular(t_hit *hit, double *dot, t_ray *shadow)
{
	t_v3	reflection;
	t_v3	incident;

	incident = vec3_negative(shadow->direction);
	reflection = vec3_reflection(incident, hit->normal);
	*dot = vec3_dot(reflection, hit->view);
	if (*dot <= EPSILON)
		return (0);
	if (*dot > 1)
		printf("DOT BIGGER\n");
//	*dot = (double)pow(*dot, SHININESS);
	return (1);
}

static int	is_in_shadow(t_scene *scene, t_hit *hit, t_ray *shadow,
				t_light *light)
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

static int	is_at_back(t_hit *hit, double *dot, t_ray *shadow)
{
	*dot = vec3_dot(hit->normal, shadow->direction);
	if (*dot <= EPSILON)
		return (1);
	return (0);
}

static t_color	apply_light(t_color color_obj, t_color color_light,
					double intensity)
{
	t_color	color;

	color.r = (color_obj.r + color_light.r) / 2 * intensity;
	color.g = (color_obj.g + color_light.g) / 2 * intensity;
	color.b = (color_obj.b + color_light.b) / 2 * intensity;
	color = clamp_colors(color);
	return (color);
}
