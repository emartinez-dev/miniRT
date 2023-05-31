#include "parser.h"

void	ft_leaks(void)
{
	system("leaks miniRT");
}

int	main(int argc, char **argv)
{
	t_scene	scene;

	atexit(ft_leaks);
	if (params_error(argc, argv, &scene) < 0)
		return (1);
	read_scene(&scene);
	free_scene(&scene);
}
