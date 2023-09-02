#include "parser.h"
#include "engine.h"

void	normalize_intensity(t_list *lights)
{
	double	total;
	t_list	*tmp;

	tmp = lights;
	total = 0;
	while (tmp)
	{
		if (((t_object *)tmp->content)->type == OBJ_LIGHT)
			total += ((t_light *)((t_object *)tmp->content)->ptr)->brightness;
		else if (((t_object *)tmp->content)->type == OBJ_AMBIENT_LIGHT)
			total += ((t_amb_light *)((t_object *)tmp->content)->ptr)->ratio;
		tmp = tmp->next;
	}
	if (total <= 1)
		return ;
	tmp = lights;
	while (tmp)
	{
		if (((t_object *)tmp->content)->type == OBJ_LIGHT)
			((t_light *)((t_object *)tmp->content)->ptr)->brightness /= total;
		else if (((t_object *)tmp->content)->type == OBJ_AMBIENT_LIGHT)
			((t_amb_light *)((t_object *)tmp->content)->ptr)->ratio /= total;
		tmp = tmp->next;
	}
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
	if (*dot <= 0.0)
		return (1);
	return (0);
}
