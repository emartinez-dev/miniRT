#include "parser.h"
#include "objects.h"

t_object	*parse_obj_ambient_light(char *line)
{
	t_object	*obj;
	t_amb_light	*light;
	char		**split;

	obj = ft_calloc(1, sizeof(t_object));
	obj->type = OBJ_AMBIENT_LIGHT;
	obj->error = 0;
	split = ft_split(line, ' ');
	light = ft_calloc(1, sizeof(t_amb_light));
	obj->ptr = light;
	if (matrix_len(split) == 3)
	{
		light->ratio = ft_atod(split[1]);
		get_color(split[2], &light->c);
	}
	else
		obj->error = 1;
	free_matrix(split);
	return (obj);
}
