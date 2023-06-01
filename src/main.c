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
	if (extract_objects(&scene) != 0)
		ft_printf("Scene is not correct\n");
	else
		print_todo(&scene);
	free_scene(&scene);
	return (0);
}
