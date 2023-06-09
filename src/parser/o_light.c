#include "parser.h"
#include "objects.h"

t_object	*parse_obj_light(char *line)
{
	t_object	*obj;
	t_light		*light;
	char		**split;

	obj = ft_calloc(1, sizeof(t_object));
	obj->type = OBJ_LIGHT;
	obj->error = 0;
	split = ft_split(line, ' ');
	light = ft_calloc(1, sizeof(t_light));
	obj->ptr = light;
	if (matrix_len(split) == 4)
	{
		get_xyz(split[1], &light->p, obj);
		light->brightness = ft_atod(split[2]);
		get_color(split[3], &light->c);
	}
	else
		obj->error = 1;
	obj->error = errors_light(light, obj);
	free_matrix(split);
	return (obj);
}

int	errors_light(t_light *light, t_object *obj)
{
	int	error;

	error = 0;
	if (obj->error == 1)
	{
		ft_printf("%s%s%s", ERROR_LIGHT, ERROR_PARTIAL, \
			ERR_MISSING_PARAMS);
		return (1);
	}
	if (errors_colors(&light->c) || light->brightness > 1.0 || \
		light->brightness < 0.0)
	{
		ft_printf("%s%s%s", ERROR_LIGHT, ERROR_PARTIAL, \
			ERR_RANGE);
		error = 2;
	}
	return (error);
}

void	get_lights(t_scene *scene)
{
	t_list		*h;

	h = scene->lights;
	while (h)
	{
		if (((t_object *)h->content)->type == OBJ_LIGHT)
			scene->light = (t_light *)((t_object *)h->content)->ptr;
		else if (((t_object *)h->content)->type == OBJ_AMBIENT_LIGHT)
			scene->ambient_light = (t_amb_light *)((t_object *)h->content)->ptr;
		h = h->next;
	}
}
