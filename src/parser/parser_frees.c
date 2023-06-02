#include "parser.h"

void	free_objects(void *content)
{
	t_object	*obj;

	obj = content;
	if (obj && obj->ptr)
		free(obj->ptr);
	free(obj);
}

void	free_scene(t_scene *scene)
{
	free_matrix(scene->scene_str);
	ft_lstclear(&scene->lights, free_objects);
	ft_lstclear(&scene->objects, free_objects);
	free(scene->camera);
}
