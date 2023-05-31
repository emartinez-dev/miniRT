#include "parser.h"
#include <stdio.h>

void	ft_leaks(void)
{
	system("leaks -q miniRT");
}

int	main(int argc, char **argv)
{
	t_scene	scene;
	t_list	*list;
	t_object	*ptr;
	t_amb_light	*light;

	atexit(ft_leaks);
	if (params_error(argc, argv, &scene) < 0)
		return (1);
	read_scene(&scene);
	extract_objects(&scene);
	printf("scene lights main: %p\n", scene.lights);
	list = scene.lights;
	ptr = (t_object *)list->content;
	light = (t_amb_light *)ptr->ptr;
	ft_printf("ptr id: %d\n", ptr->type);
	ft_printf("light r: %d\n", light->c.r);
	free_scene(&scene);
	return (0);
}
