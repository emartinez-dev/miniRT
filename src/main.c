#include "parser.h"
#include <stdio.h>

void	ft_leaks(void)
{
	system("leaks -q miniRT");
}

int	main(int argc, char **argv)
{
	t_scene	scene;

	atexit(ft_leaks);
	if (params_error(argc, argv, &scene))
		return (1);
	read_scene(&scene);
	extract_objects(&scene);
	free_scene(&scene);
	return (0);
}
