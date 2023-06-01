#include "parser.h"
#include "objects.h"

t_object	*parse_obj_plane(char *line)
{
	t_object	*obj;
	t_plane		*plane;
	char		**split;

	obj = ft_calloc(1, sizeof(t_object));
	obj->type = OBJ_PLANE;
	obj->error = 0;
	split = ft_split(line, ' ');
	plane = ft_calloc(1, sizeof(t_plane));
	obj->ptr = plane;
	if (matrix_len(split) == 4)
	{
		get_xyz(split[1], &plane->p, obj);
		get_xyz(split[2], &plane->norm, obj);
		get_color(split[3], &plane->c);
	}
	else
		obj->error = 1;
	obj->error = errors_plane(plane, obj);
	free_matrix(split);
	return (obj);
}

int	errors_plane(t_plane *plane, t_object *obj)
{
	int	error;

	error = 0;
	if (obj->error == 1)
	{
		ft_printf("%s%s%s", ERROR_PLANE, ERROR_PARTIAL, \
			ERR_MISSING_PARAMS);
		return (1);
	}
	if (errors_colors(&plane->c) || errors_normalized_vector(&plane->p))
	{
		ft_printf("%s%s%s", ERROR_PLANE, ERROR_PARTIAL, \
			ERR_RANGE);
		error = 2;
	}
	return (error);
}
