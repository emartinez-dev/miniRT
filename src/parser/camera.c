#include "parser.h"
#include "objects.h"

t_object	*parse_obj_camera(char *line)
{
	t_object	*obj;
	t_camera	*camera;
	char		**split;

	obj = ft_calloc(1, sizeof(t_object));
	obj->type = OBJ_CAMERA;
	obj->error = 0;
	split = ft_split(line, ' ');
	camera = ft_calloc(1, sizeof(t_camera));
	obj->ptr = camera;
	if (matrix_len(split) == 4)
	{
		get_xyz(split[1], &camera->p, obj);
		get_xyz(split[2], &camera->norm, obj);
		camera->fov = ft_atoi(split[3]);
	}
	else
		obj->error = 1;
	obj->error = errors_camera(camera, obj);
	free_matrix(split);
	return (obj);
}

int	errors_camera(t_camera *camera, t_object *obj)
{
	int	error;

	if (obj->error == 1)
	{
		ft_putstr_fd(ERR_MISSING_PARAMS, STDERR_FILENO);
		return (1);
	}
	error = 0;
	if (camera->norm.x > 1.0 || camera->norm.y > 1.0 || camera->norm.z > 1.0 \
		|| camera->norm.x < -1.0 || camera->norm.y < -1.0 || \
		camera->norm.z < -1.0 || camera->fov < 0 || camera->fov > 180)
		error = 2;
	if (error == 2)
		ft_putstr_fd(ERR_RANGE, STDERR_FILENO);
	return (error);
}
